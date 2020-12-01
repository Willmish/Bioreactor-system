import tkinter

# Create a GUI that interfaces with SimAVR
class MainFrame(tkinter.Frame):
    def __init__(self, master=None):
        pass

class View:
    def __init__(self):
        self.root: tkinter.Tk = tkinter.Tk(className="Bioreactor control system")
        self.root.geometry("800x500")
        self.root.resizable(False, False)
        self.controller = None

    def create_gui(self):
        self.title = tkinter.Label(self.root, text="Bioreactor app control")
        
        self.temperature_title = tkinter.Label(self.root, text="Temperature subsystem:")

        # Pack the widgets at the end
        self.pack_gui()

    def pack_gui(self):
        self.title.pack()

    def register_controller(self, controller):
        self.controller = controller

    def mainloop(self):
        self.root.mainloop()


if __name__ == "__main__":
    g = View()
    g.mainloop()
