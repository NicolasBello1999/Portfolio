previous_word_dict = {}
something = {}

class card:
    def __init__(self, name: str, data: int):
        self.name = name
        self.data = data

    def getName(self): return self.name
    def getData(self): return self.data

def check_message(message: str, server_id: int) -> None:
    if (not previous_word_dict) or (server_id not in previous_word_dict): # check if the dictionary is empty
        previous_word_dict[server_id] = message
    else:
        if message[0] != previous_word_dict[server_id][-1]:
            print("Warning! Message does not start with the last word of the previous one.")
        else:
            print(f"{previous_word_dict[server_id]} => {message}")
            previous_word_dict[server_id] = message
    return

def test1() -> None:
    check_message("penis", 32947)
    check_message("super", 32947)
    check_message("retard", 23485)
    check_message("lock", 23485)
    check_message("dick", 23485)
    print(previous_word_dict)

test1()
c1 = card("Mark", 5)
c2 = card("Nicolas", 17)
c3 = card("Amaya", 94)

something[0] = c1
something[1] = c2
something[2] = c3

if (something[1].getName() != something[2].getName()):
    print("Names do not match")

for x in range(len(something)):
    print(f"something[{x}] : ({something[x].name}, {something[x].getData()})")