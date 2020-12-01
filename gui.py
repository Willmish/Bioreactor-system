import tkinter
import tkinter.font as font

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
        self.title_font = font.Font(family="Verdana", size=15, weight="bold")
        self.title = tkinter.Label(self.root, text="Bioreactor app control", height=2, font=self.title_font)
      
        # Temperature subsystem
        self.temperature_title = tkinter.Label(self.root, text="Temperature subsystem:", height=1)
        self.temperature_target_title = tkinter.Label(self.root, text="Target value: ") 
        self.temperature_target_value = tkinter.Label(self.root, text="0.0") 
        self.temperature_current_title = tkinter.Label(self.root, text="Current value: ") 
        self.temperature_current_value = tkinter.Label(self.root, text="0.0") 
        
        # Stiring subsystem
        self.stiring_title = tkinter.Label(self.root, text="Stiring subsystem:", height=1)
        self.stiring_target_title = tkinter.Label(self.root, text="Target value: ") 
        self.stiring_target_value = tkinter.Label(self.root, text="0.0") 
        self.stiring_current_title = tkinter.Label(self.root, text="Current value: ") 
        self.stiring_current_value = tkinter.Label(self.root, text="0.0") 

        # PH subsystem
        self.ph_title = tkinter.Label(self.root, text="PH subsystem:", height=1)
        self.ph_target_title = tkinter.Label(self.root, text="Target value: ") 
        self.ph_target_value = tkinter.Label(self.root, text="0.0") 
        self.ph_current_title = tkinter.Label(self.root, text="Current value: ") 
        self.ph_current_value = tkinter.Label(self.root, text="0.0") 
        

        # Pack the widgets at the end
        self.pack_gui()

    def pack_gui(self):
        self.title.pack()
        self.temperature_title.pack(side=tkinter.TOP, anchor=tkinter.NW)
        self.temperature_target_value.pack(side=tkinter.TOP, anchor=tkinter.NW)
        self.temperature_current_value.pack(side=tkinter.TOP, anchor=tkinter.NW)

        self.stiring_title.pack(side=tkinter.TOP, anchor=tkinter.NW)
        self.stiring_target_value.pack(side=tkinter.TOP, anchor=tkinter.NW)
        self.stiring_current_value.pack(side=tkinter.TOP, anchor=tkinter.NW)

        self.ph_title.pack(side=tkinter.TOP, anchor=tkinter.NW)
        self.ph_target_value.pack(side=tkinter.TOP, anchor=tkinter.NW)
        self.ph_current_value.pack(side=tkinter.TOP, anchor=tkinter.NW)

    def register_controller(self, controller):
        self.controller = controller

    def mainloop(self):
        self.root.mainloop()


if __name__ == "__main__":
    g = View()
    g.mainloop()
