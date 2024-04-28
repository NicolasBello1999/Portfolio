import threading, time
from pynput.mouse import Button, Controller
from pynput.keyboard import Listener, KeyCode

class AutoClicker(threading.Thread):
    def __init__(self, delay, button):
        super().__init__()
        self.delay = delay
        self.button = button
        self.running = False

    def start_clicking(self):
        self.running = True

    def stop_clicking(self):
        self.running = False

    def run(self):
        while True:
            while self.running:
                mouse.click(self.button)
                time.sleep(self.delay)
            time.sleep(0.1)

class KeyListener:
    def __init__(self, start_stop_key, stop_key, click_thread):
        self.start_stop_key = start_stop_key
        self.stop_key = stop_key
        self.click_thread = click_thread
        self.listener = None

    def on_press(self, key):
        if key == self.start_stop_key:
            if self.click_thread.running:
                self.click_thread.stop_clicking()
            else:
                self.click_thread.start_clicking()
        elif key == self.stop_key:
            self.click_thread.stop_clicking()
            if self.listener:
                self.listener.stop()

def main() -> None:
    delay = 0.001
    button = Button.left
    start_stop_key = KeyCode(char='a')
    stop_key = KeyCode(char='b')

    global mouse
    mouse = Controller()
    click_thread = AutoClicker(delay, button)
    click_thread.start()

    key_listener = KeyListener(start_stop_key, stop_key, click_thread)

    with Listener(on_press=key_listener.on_press) as listener:
        key_listener.listener = listener  # Assign the listener object to the KeyListener instance
        listener.join()

if __name__ == "__main__":
    main()

# Keep console open until user presses Enter
input("Press Enter to exit...")