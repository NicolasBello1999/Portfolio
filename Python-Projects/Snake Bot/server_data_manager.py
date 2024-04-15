import json, os

server_data = {}

# get the directory of the current script
script_dir = os.path.dirname(os.path.abspath(__file__))

# construct the file path for the JSON file
json_file_path = os.path.join(script_dir, 'server_channels.json')

# load server_channels.json at the start
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

def add_server_channels(server_id: int, channel_id: int) -> None:
    if str(server_id) in server_data:
        if channel_id not in server_data[str(server_id)]:
            server_data[str(server_id)].append(channel_id)
            with open("server_channels.json", "w") as file:
                json.dump(server_data, file, indent=4)
            print(f"Channel ID [{channel_id}] has been added to the list for Server ID [{server_id}]...")
    else:
        server_data[str(server_id)] = [channel_id]
        with open("server_channels.json", "w") as file:
            json.dump(server_data, file, indent=4)
        print(f"Server ID [{server_id}] and Channel ID [{channel_id}] has been added to the list...")

def create_data_table(server_id: int, channel_id: int, users: list) -> None:
    if server_id in server_data:
        return
    else:
        server_data[server_id] = [{
            "channel_id" : channel_id,
            "server_users" : users
        }]

    with open("server_data.json", "w") as file:
        json.dump(server_data, file, indent=4)

def update_points(server_id: int, user_id: int, points: int) -> None:
    return