from typing import Final
from dotenv import load_dotenv
from discord import Intents, Client, Message, Member
from discord.ext import commands
import nlp, os, signal, discord, server_data_manager as sdm

load_dotenv()
TOKEN: Final[str] = os.getenv('DISCORD_TOKEN')

# setting up the bot's intents in-order to read bot/user messages
intents: Intents = Intents.default() # potentially might have to change it to .all()
intents.message_content = True
intents.members = True
bot: Client = Client(intents=intents)
bot = commands.Bot(command_prefix=">>", intents=intents) # set prefix for command calls which will be '>>'

previous_word_dict: Message = {} # retain a dictionary of previous messages respective to their servers
unique_words_used: str = [] # retain all unique words to assign points later on
white_check_mark = "\U00002705" # ✅

# command to check for user's current point balance within their respective server or another user's points
@bot.command()
async def points(ctx, user: discord.Member = None) -> None:
    if not user:
        embed = discord.Embed(
            description=f"{ctx.author.display_name} has {sdm.get_points(ctx.guild.id, ctx.author)} point(s).",
            color = discord.Color.dark_blue()
        )
        await ctx.send(embed=embed)
    else:
        embed = discord.Embed(
            description=f"{user.display_name} has {sdm.get_points(ctx.guild.id, user.name)} point(s).",
            color = discord.Color.dark_blue()
        )
        await ctx.send(embed=embed)
    return

# @points.error
# async def points_error(ctx, error):
#     if isinstance(error, commands.MissingRequiredArgument):
#         embed  = discord.Embed(
#             title="ERROR!",
#             description="Invalid user, please put `@User` next to `>>points`.",
#             color = discord.Color.dark_blue()
#         )
#         await ctx.send(embed=embed)

@bot.command()
async def this(ctx) -> None:
    channel_id: int = ctx.channel.id
    server_id: int = ctx.guild.id

    try:
        if sdm.add_channel_to_server(server_id, channel_id):
            print(f"Added {channel_id} to server id {server_id}")
    except Exception as e:
        print(f"Encountered error! [{e}]")

@bot.command()
async def wipe(ctx) -> None:
    await ctx.channel.purge(limit=100)

@bot.command()
async def freeze(ctx, user: discord.Member, length: int) -> None:
    await ctx.send(f"Freezing {user.display_name} for the next {length} turns!")

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
    #if previous_word_dict[int(message.guild.id)] != None:
    if message.guild.id in previous_word_dict.keys():
        if previous_word_dict[int(message.guild.id)].author == message.author:
            await message.delete()
            return
    
    message_content: str = message.content.strip()

    # if the word isn't part of the English dictionary then delete the word
    if nlp.is_valid_word(message_content) == False:
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
        previous_word_dict[int(message.guild.id)] = message
        sdm.give_points(message.guild.id, message.author, points=1)
        unique_words_used.append(message_content)

    # delete the duplicate message sent by the same user
    # if previous_word_dict != None:
    #     if previous_word_dict.author == message.author:
    #         await message.delete()
    #         return

    # user_message: str = message.content.strip()

    # if previous_word_dict == None:
    #     if nlp.is_valid_word(user_message):
    #         await message.add_reaction(white_check_mark)
    #         accepted_word = True
    # else:
    #     if (nlp.is_valid_word(user_message)):
    #         if (nlp.check_letters(previous_word_dict.content.strip(), user_message)):
    #             await message.add_reaction(white_check_mark)
    #             accepted_word = True
    #         else:
    #             await message.delete()
    #     else:
    #         await message.delete()

    # if accepted_word:
    #     # previous_word_dict[int(message.guild.id)] = message
    #     previous_word_dict = message # update the previous word to be the new
    #     sdm.earned_points(message.guild.id , message.author, points=1)
    #     unique_words_used.append(user_message)

# on bot start up
@bot.event
async def on_ready() -> None:
    print(f"{bot.user} is now running!") # notify the bot is running properly
    sdm.on_startup_JSON() # open JSON file upon bot startup

    for server in bot.guilds: # loop through each server that the bot has access to
        print(f"Connected to server : {server.name} = {server.id}")
        sdm.create_data_table(server.id, server.members)

# add member to the list when they join the server
@bot.event
async def on_member_join() -> None:
    return
    
# stop the bot gracefully on SIGINT (Ctrl + C) keys
def handle_sigint(signum, frame):
    print("Stopping the bot gracefully")
    sdm.save_server_channels()
    bot.close()

# main program to run our bot and all helper scripts
def main() -> None:
    try:
        signal.signal(signal.SIGINT, handle_sigint)
        bot.run(TOKEN) # run our bot
    except Exception as e:
        print(e)
    finally:
        sdm.save_server_channels() # as backup in case we crash for some reason

__name__ = "__main__"
main()