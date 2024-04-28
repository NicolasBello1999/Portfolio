from typing import Final
from dotenv import load_dotenv
from discord import Intents, Client, Message, Member
from discord.ext import commands
import nlp, os, signal, server_data_manager as sdm

load_dotenv()
TOKEN: Final[str] = os.getenv('DISCORD_TOKEN')

# setting up the bot's intents in-order to read client/user messages
intents: Intents = Intents.default() # potentially might have to change it to .all()
intents.message_content = True
intents.members = True
client: Client = Client(intents=intents)
client = commands.Bot(command_prefix=">>", intents=intents) # set prefix for command calls which will be '>>'

previous_word: Message = None # retain previous message as a global variable
unique_words_used: str = [] # retain all unique words to assign points later on
white_check_mark = "\U00002705" # ✅

# command to check for user's current point balance within their respective server
@client.command()
async def points(ctx) -> None:
    await ctx.send("Your broke asf boi!")

@client.command()
async def this(ctx) -> None:
    channel_id: int = ctx.channel.id
    server_id: int = ctx.guild.id

    try:
        if sdm.add_channel_to_server(server_id, channel_id):
            print(f"Added {channel_id} to server id {server_id}")
    except Exception as e:
        print(f"Encountered error! [{e}]")

# handle incoming user messages and start doing game commands
@client.event
async def on_message(message: Message) -> None:
    # process commands first before checking if the message is relevant to this cog
    await client.process_commands(message)

    global previous_word
    accepted_word: bool = False

    # have the bot ignore its own message
    if message.author == client.user: return

    # only check if messages are sent to a specific text channel named "better-snake" or if the channel id was added by command
    if (message.channel.name != "better-snake") or (message.channel.id not in sdm.server_data.get(str(message.guild.id), [])):
        return

    # delete the duplicate message sent by the same user
    if  previous_word != None:
        if previous_word.author == message.author:
            await message.delete()
            return

    user_message: str = message.content.strip()

    if previous_word == None:
        if nlp.is_valid_word(user_message):
            await message.add_reaction(white_check_mark)
            accepted_word = True
    else:
        if (nlp.is_valid_word(user_message)):
            if (nlp.check_letters(previous_word.content.strip(), user_message)):
                await message.add_reaction(white_check_mark)
                accepted_word = True
            else:
                await message.delete()
        else:
            await message.delete()

    if accepted_word:
        previous_word = message # update the previous word to be the new
        unique_words_used.append(user_message)

# on bot start up
@client.event
async def on_ready() -> None:
    print(f"{client.user} is now running!") # notify the bot is running properly
    sdm.on_startup_JSON() # open JSON file upon bot startup

    for server in client.guilds: # loop through each server that the bot has access to
        print(f"Connected to server : {server.name} = {server.id}")
        sdm.create_data_table(server.id, server.members)

# add member to the list when they join the server
@client.event
async def on_member_join() -> None:
    return
    
# stop the bot gracefully on SIGINT (Ctrl + C) keys
def handle_sigint(signum, frame):
    print("Stopping the bot gracefully")
    sdm.save_server_channels()
    client.close()

# main program to run our bot and all helper scripts
def main() -> None:
    try:
        signal.signal(signal.SIGINT, handle_sigint)
        client.run(TOKEN) # run our bot
    except Exception as e:
        print(e)
    finally:
        sdm.save_server_channels() # as backup in case we crash for some reason

__name__ = "__main__"
main()