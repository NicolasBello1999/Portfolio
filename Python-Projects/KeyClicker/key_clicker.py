import time
from pynput import keyboard

# Initialize the keyboard controller
keyboard_controller = keyboard.Controller()

# Global variable to control the running state of the auto-clicker
running = False

# Function to press the "F" key
def press_f_key(interval_ms):
    global running
    while running:
        keyboard_controller.press('f')
        keyboard_controller.release('f')
        time.sleep(interval_ms / 1000.0)  # Convert milliseconds to seconds

# Function to handle key presses
def on_press(key):
    global running
    try:
        if key.char == 's':  # Start pressing "F" when 's' is pressed
            if not running:
                running = True
                print("Started pressing 'F'")
                press_f_key(interval_ms)
        elif key.char == 'e':  # Stop pressing "F" when 'e' is pressed
            if running:
                running = False
                print("Stopped pressing 'F'")
    except AttributeError:
        # Handle special keys (e.g., arrow keys, function keys) if needed
        pass

# Set the interval (in milliseconds)
interval_ms = 1  # For example, press "F" every 10 milliseconds

# Create a listener for key press events
with keyboard.Listener(on_press=on_press) as listener:
    listener.join()
