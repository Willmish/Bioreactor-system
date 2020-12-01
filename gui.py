from enum import Enum
from typing import List
import tkinter
import tkinter.font as font

class Subsystem_Label(Enum):
    TITLE = 0
    TARGET_TITLE = 1
    TARGET_VALUE = 2
    CURRENT_TITLE = 3
    CURRENT_VALUE = 4

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
        self.temperature_frame = tkinter.Frame(self.root, relief=tkinter.FLAT) # TODO potentially add borderwidth?
        self.temperature_labels = self.create_subsystem_labels("Temperature", self.temperature_frame)
        
        # Stiring subsystem
        self.stiring_frame = tkinter.Frame(self.root, relief=tkinter.FLAT) # TODO potentially add borderwidth?
        self.stiring_labels = self.create_subsystem_labels("Stiring", self.stiring_frame)

        # PH subsystem
        self.ph_frame = tkinter.Frame(self.root, relief=tkinter.FLAT) # TODO potentially add borderwidth?
        self.ph_labels = self.create_subsystem_labels("PH", self.ph_frame)
        

        # Pack the widgets at the end
        self.pack_gui()
    
    def create_subsystem_labels(self, subsystem: str, root) -> List[tkinter.Label]:
        # Create labels for each subsystem based on the indices specified by the Subsystem_Label ENUM
        labels = [None for i in Subsystem_Label]
        labels[Subsystem_Label.TITLE.value] = tkinter.Label(root, text=subsystem+" subsystem:", height=1)
        labels[Subsystem_Label.TARGET_TITLE.value] = self.stiring_target_title = tkinter.Label(root, text="Target value: ")
        labels[Subsystem_Label.TARGET_VALUE.value] = tkinter.Label(root, text="0.0")
        labels[Subsystem_Label.CURRENT_TITLE.value] = tkinter.Label(root, text="Current value: ")
        labels[Subsystem_Label.CURRENT_VALUE.value] = tkinter.Label(root, text="0.0")
        return labels


    def pack_gui(self):
        self.title.pack()
        self.temperature_frame.pack(fill=tkinter.X, side=tkinter.TOP, expand=True)
        self.stiring_frame.pack(fill=tkinter.X, side=tkinter.TOP, expand=True)
        self.ph_frame.pack(fill=tkinter.X, side=tkinter.TOP, expand=True)
        self.pack_subsystem_labels() 
    
    def pack_subsystem_labels(self):
        for i in range(len((self.temperature_labels, self.stiring_labels, self.ph_labels))):
            # create tuple to avoid magic numbers
            to_pack = None
            if i == 0:
                to_pack = self.temperature_labels
            elif i == 1:
                to_pack = self.stiring_labels
            elif i == 2:
                to_pack = self.ph_labels
            else:
                raise Exception("Error when packing subsystem GUI with index: " + str(i))
            
            for j in range(len(to_pack)):
                if j == Subsystem_Label.TARGET_VALUE.value or j == Subsystem_Label.CURRENT_VALUE.value:
                    to_pack[j].grid(row=j-1, column=2)
                else:
                    to_pack[j].grid(row=j, column=1)

    def register_controller(self, controller):
        self.controller = controller

    def mainloop(self):
        self.root.mainloop()


if __name__ == "__main__":
    g = View()
    g.mainloop()
