import tkinter as tk

class GUI:
    font_text: str = "Arial"
    font_size: int = 18
    font_format = (font_text, font_size)

    def __init__(self) -> None:
        self.root = tk.Tk()

        self.root.geometry("400x500") # width x height in pixels
        self.root.title("AutoClicker")

        self.label = tk.Label(self.root, text="This is a test...", font=self.font_format)
        self.label.pack()

        self.button = tk.Button(self.root, text="Save", font=self.font_format)
        self.button.pack(padx=10, pady=10)

        self.root.mainloop()

    def save_key_inputs(self) -> None:
        print("test")

GUI()