import json, os

server_data = {}

# get the directory of the current script
script_dir = os.path.dirname(os.path.abspath(__file__))

# construct the file path for the JSON file
json_file_path = os.path.join(script_dir, 'server_data.json')

def get_server_list() -> list:
    return server_data

# load server_data.json at the start
def on_startup_JSON() -> None:
    try:
        with open(json_file_path, 'r') as file:
            server_channels = json.load(file)
    except FileNotFoundError:
        server_channels = {}

        # Write the empty dictionary to the JSON file
        with open(json_file_path, 'w') as file:
            json.dump(server_channels, file)
    except Exception as e:
        print(e)

def save_server_channels() -> None:
    with open(json_file_path, 'w') as file:
        json.dump(server_data, file, indent=4)

# when a user does the ">>this" command, it will check if the current channel has been added to the server's list of acceptable channels to play the game
def add_channel_to_server(server_id: int, channel_id: int) -> bool:
    if channel_id not in server_data[str(server_id)]["channel_ids"]:
        server_data[str(server_id)]["channel_ids"].append(channel_id)
        return True
    else:
        return False

def create_data_table(server_id: int, users: list) -> None:
    if str(server_id) not in server_data:
        print(f"Creating data table for {server_id}...")
        # If not, create a new entry for it
        server_data[str(server_id)] = {
            "channel_ids": [],
            "users": {}
        }

    # Add users to the server
    for user in users:
        # Initialize points only if the user doesn't exist
        if str(user) not in server_data[str(server_id)]["users"]:
            server_data[str(server_id)]["users"][str(user)] = {"points": 0}

    # Save the updated data
    with open(json_file_path, "w") as fp:
        json.dump(server_data, fp, indent=4)

def update_points(server_id: int, user_id: int, points: int) -> None:
    return