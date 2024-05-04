from typing import Final
from dotenv import load_dotenv
from discord import Intents, Client, Message
from discord.ext import commands
import nlp, os, signal, discord, server_data_manager as sdm
from collections import defaultdict

load_dotenv()
TOKEN: Final[str] = os.getenv('DISCORD_TOKEN')

# setting up the bot's intents in-order to read bot/user messages
intents: Intents = Intents.default() # potentially might have to change it to .all()
intents.message_content = True
intents.members = True
bot: Client = Client(intents=intents)
bot = commands.Bot(command_prefix=">>", intents=intents) # set prefix for command calls which will be '>>'
bot.remove_command('help')

# ongoing checks and operations
previous_word_dict: Message = {} # retain a dictionary of previous messages respective to their servers
unique_words_used: str = [] # retain all unique words to assign points later on
current_frozen_players = defaultdict(list)

# final variables
white_check_mark = "\U00002705" # ✅

@bot.command()
async def check(ctx, user: discord.Member):
    server = current_frozen_players.get(ctx.guild.id)

    if server:
        for player in server:
            if player["player"] == user:
                await ctx.send(f"{user.display_name} is still frozen for the next {player['turns_frozen']} turns.")
                return
        await ctx.send(f"{user.display_name} is not frozen.")
    else:
        await ctx.send("No players are currently frozen.")

@bot.command()
async def help(ctx):
    embed = discord.Embed(
        title="List of Commands:",
        description="freeze - stop a player from completing a word for the next x amount of turns.\npoints - check a user's current balance.\n",
        color=discord.Color.dark_blue()
    )
    await ctx.send(embed=embed)
    return

# command to check for user's current point balance within their respective server or another user's points
@bot.command()
async def points(ctx, user: discord.Member = None) -> None:
    if not user:
        embed = discord.Embed(
            description=f"{ctx.author.display_name} has {sdm.get_points(ctx.guild.id, ctx.author)} point(s).",
            color=discord.Color.dark_blue()
        )
        await ctx.send(embed=embed)
    else:
        embed = discord.Embed(
            description=f"{user.display_name} has {sdm.get_points(ctx.guild.id, user.name)} point(s).",
            color=discord.Color.dark_blue()
        )
        await ctx.send(embed=embed)
    return

@bot.command()
async def this(ctx) -> None:
    try:
        if sdm.add_channel_to_server(ctx.guild.id, ctx.channel.id):
            print(f"Added {ctx.channel.id} to server id {ctx.guild.id}")
    except Exception as e:
        print(f"Encountered error! [{e}]")

@bot.command()
async def wipe(ctx) -> None:
    await ctx.channel.purge(limit=100)

@bot.command()
async def freeze(ctx, user: discord.Member, length: int=1) -> None:
    user_points: int = sdm.get_points(ctx.guild.id, ctx.author)
    if user_points >= length * 10:
        sdm.deduct_points(ctx.guild.id, ctx.author, length * 10)
        
        if int(ctx.guild.id) in current_frozen_players.keys():
            current_frozen_players[ctx.guild.id].append({"player": user, "turns_frozen": length})
        else:
            current_frozen_players[ctx.guild.id] = [{"player": user, "turns_frozen": length}]

        print(f"Player {user.display_name} has been frozen for {length} turns.")

        embed = discord.Embed(
            description=f"Freezing {user.display_name} for the next {length} turns!",
            color=discord.Color.dark_blue()
        )
        await ctx.send(embed=embed)
    else:
        embed = discord.Embed(
            description=f"Not enough points, you need {length * 10} while you have {user_points} point(s).",
            color=discord.Color.dark_blue()
        )
        await ctx.send(embed=embed)

@bot.command()
@commands.is_owner()
async def force_points(ctx, user: discord.Member, points: int=100):
    """Forces a certain amount of points to be given to a player."""
    sdm.give_points(ctx.guild.id, user.name, points)
    embed = discord.Embed(
            title="God's Gift?!?",
            description=f"Gave {points} points to {user.display_name}.",
            color=discord.Color.dark_blue()
        )
    await ctx.send(embed=embed)
    return

# handle incoming user messages
@bot.event
async def on_message(message: Message) -> None:
    # process commands first before checking if the message is relevant to this cog
    await bot.process_commands(message)

    # just in case if a command isn't awaited properly to prevent deletion
    if message.content.startswith(">>"): return

    # have the bot ignore its own message
    if message.author == bot.user: return

    # only check if messages are sent to a specific text channel named "better-snake" or if the channel was added by command
    if (message.channel.name != "better-snake") and (message.channel.id not in sdm.server_data.get(str(message.guild.id), [])):
        return
    
    global previous_word_dict
    accepted_word: bool = False

    # delete the message sent by the same user if it's twice in a row (within their respective server)
    if any(player["player"] == message.author for player in current_frozen_players.get(message.guild.id, [])):
        await message.delete()

        # remove player from current_frozen_players if they are no longer frozen
        current_frozen_players[message.guild.id] = [player for player in current_frozen_players.get(message.guild.id, []) if player["turns_frozen"] > 1]
        return
    
    message_content: str = message.content.strip()

    # if the word isn't part of the English dictionary then delete the word
    if nlp.is_valid_word(message_content) == False:
        await message.delete()
        return
    
    # check if the player is currently frozen, if they are then prevent them from typing
    if any(player["player"] == message.author for player in current_frozen_players.get(message.guild.id, [])):
        await message.delete()
        return
    
    # check if there's a already a previous word within the message's server, if not, we make the message the previous word 
    if message.guild.id not in previous_word_dict.keys():
        accepted_word = True
    else: # there exists a previous word within the server so we check if its a "snake" word (banana => apple is true)
        if nlp.check_letters(previous_word_dict[int(message.guild.id)].content.strip(), message_content):
            accepted_word = True
        else: # the word isn't a "snake" word
            await message.delete()
            return
    
    if accepted_word:
        await message.add_reaction(white_check_mark)

        if message_content in unique_words_used: # give 1 point if the word isn't unique since its in the list
            sdm.give_points(message.guild.id, message.author, points=1)
        else: # if the word isn't in the list, then the word was unique and should be added to the list, user gets 2 points
            sdm.give_points(message.guild.id, message.author, points=2)
            unique_words_used.append(message_content)

        previous_word_dict[int(message.guild.id)] = message
        for player_frozen in current_frozen_players.get(message.guild.id, []):
            if player_frozen["turns_frozen"] > 0:
                player_frozen["turns_frozen"] -= 1

# on bot start up
@bot.event
async def on_ready() -> None:
    print(f"{bot.user} is now running!") # notify the bot is running properly
    sdm.on_startup_JSON() # open JSON file upon bot startup

    for server in bot.guilds: # loop through each server that the bot has access to
        print(f"Connected to server : {server.name} = {server.id}")
        sdm.create_data_table(server.id, server.members)

# when the bot joins a new server
@bot.event
async def on_guild_join(guild: discord.Guild) -> None:
    # create a new table within the JSON file for newly joined servers
    sdm.create_data_table(guild.id, guild.members)

# when a new member joins a server that the bot is apart of
@bot.event
async def on_member_join(member: discord.Member) -> None:
    # add member to the list when they join the server
    sdm.add_user(member.guild.id, member.author)
    
# stop the bot gracefully on SIGINT (Ctrl + C) keys
def handle_sigint(signum, frame):
    print("Stopping the bot gracefully")
    sdm.save_server_data()
    bot.close()
    exit()

# main program to run the bot and all helper scripts
def main() -> None:
    try:
        signal.signal(signal.SIGINT, handle_sigint)
        bot.run(TOKEN) # run the bot
    except Exception as e:
        print(e)
    finally:
        sdm.save_server_data() # as backup in case we crash for some reason

__name__ = "__main__"
main()