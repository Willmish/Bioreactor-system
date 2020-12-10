import tkinter
import serial

# Create a GUI that interfaces with SimAVR

class View:
    def __init__(self):
        self.root = tkinter.Tk(className="Bioreactor control system")
        self.controller = None

    def register_controller(self, controller):
        self.controller = controller

    def mainloop(self):
        self.root.mainloop()


if __name__ == "__main__":
    g = View()
    g.mainloop()
