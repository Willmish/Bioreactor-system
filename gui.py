from enum import Enum
from typing import List
import tkinter
import tkinter.font as font
#Matplotlib
from matplotlib.backends.backend_tkagg import (
    FigureCanvasTkAgg, NavigationToolbar2Tk)
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import numpy as np


MAIN_COLOUR = "#AEADF0"
TEXT_COLOUR = "#2E5266"
FRAME_COLOUR = "#FFEAD0"
HIGHLIGHT_COLOUR = "#93032E"
GRAPH_COLOUR = "#47E5BC"
DEBUGGING = True

class Subsystem_Label(Enum):
    TITLE = 0
    TARGET_TITLE = 1
    TARGET_VALUE = 2
    CURRENT_TITLE = 3
    CURRENT_VALUE = 4
    TARGET_DECREMENT = 5
    TARGET_INCREMENT = 6

class Subsystem_Graph(tkinter.Frame):
    def __init__(self, master, data_arr, data_fetch_func, y_lims, animation_interval = 500, *args, **kwargs):
        super().__init__()
        self.master = master
        # data
        self.data_fetch_func = data_fetch_func
        self.data_arr = data_arr 
        self.time_arr = []
        self.time = 0
        self.lowy, self.highy = y_lims

        # tk/matplotlib specific
        self.fig = None
        self.plot = None
        self.canvas = None
        self.widget = None
        self.animation = None
        self.animation_interval = animation_interval

    def create_graph(self):
        self.fig = plt.figure(figsize=(4,2), dpi=100,tight_layout=True, facecolor=FRAME_COLOUR, edgecolor=GRAPH_COLOUR)
        self.axs = plt.axes(xlim=(0,20), ylim=(self.lowy, self.highy))
        self.plot, = self.axs.plot(self.time_arr, self.data_arr)
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.master)  # A tk.DrawingArea.
        self.canvas.draw()
        self.widget = self.canvas.get_tk_widget()
        # set limits
        # Animate it
        self.animation = FuncAnimation(self.fig, self.animate, interval=self.animation_interval)
        
        self.fig.tight_layout()

    def animate(self, i):
        # Read data from label
        # Add data
        self.data_arr.append(self.data_fetch_func())
        self.time_arr.append(self.time/self.animation_interval)
        self.time += self.animation_interval
        self.plot.set_data(self.time_arr, self.data_arr)
        xmin, xmax =plt.xlim()
        if(self.time/self.animation_interval>xmax):
           xmin += 5
           xmax += 5
           self.axs.set_xlim(xmin, xmax)
        self.canvas.draw()


    def update_data(self):
        pass
    
    def pack_widget(self, *args, **kwargs):
        self.widget.pack(*args, **kwargs)

# Create a GUI that interfaces with SimAVR
class MainFrame(tkinter.Frame):
    def __init__(self, master=None):
        pass

class View:
    def __init__(self):
        self.root: tkinter.Tk = tkinter.Tk(className="Bioreactor control system")
        self.root.geometry("800x700")
        self.root.resizable(False, False)
        self.controller = None

        # Images
        self.increment_icon = None
        self.decrement_icon = None

        # subsystem boundries
        self.subsystem_increments = {"Temperature": 0.5, "Stiring": 10.0, "PH": 0.5}
        self.lower_bounds = {"Temperature": 25.0, "Stiring": 500.0, "PH": 3.0}
        self.upper_bounds = {"Temperature": 35.0, "Stiring": 1500.0, "PH": 7.0}
        self.default_values = {"Temperature": 30.0, "Stiring": 1000.0, "PH": 5.0} 
        
        # Matplotlib data
        self.temperature_values = []
        self.rpm_values = []
        self.ph_values = []

    def set_colours(self):
        self.root.tk_setPalette(background=MAIN_COLOUR, foreground=TEXT_COLOUR, activeBackground=HIGHLIGHT_COLOUR, activeForeground=HIGHLIGHT_COLOUR, highlightBackground=GRAPH_COLOUR)

        self.temperature_frame["bg"] = FRAME_COLOUR
        for el in self.temperature_labels:
            #if isinstance(el, tkinter.label):
            el["bg"] = FRAME_COLOUR 
            
        self.stiring_frame["bg"] = FRAME_COLOUR
        for el in self.stiring_labels:
            #if isinstance(el, tkinter.label):
            el["bg"] = FRAME_COLOUR

        self.ph_frame["bg"] = FRAME_COLOUR
        for el in self.ph_labels:
            #if isinstance(el, tkinter.label):
            el["bg"] = FRAME_COLOUR

    def create_gui(self):
        # save images:
        self.increment_icon = tkinter.PhotoImage(file="./images/plus-sign.png")
        self.decrement_icon = tkinter.PhotoImage(file="./images/minus.png")
        self.title_font = font.Font(family="Verdana", size=15, weight="bold")
        self.title = tkinter.Label(self.root, text="Bioreactor app control", height=2, font=self.title_font)

        # Main frames
        self.control_frame = tkinter.Frame(self.root, highlightthickness=4) 
        self.graph_frame=tkinter.Frame(self.root, highlightthickness=4, padx=10, pady=10)
        # Temperature subsystem
        self.temperature_frame = tkinter.Frame(self.control_frame, highlightthickness=4) # TODO potentially add borderwidth?
        self.temperature_labels = self.create_subsystem_labels("Temperature", self.temperature_frame)

        self.graph_temp_frame = Subsystem_Graph(self.graph_frame, self.temperature_values, self.get_new_temp_data,(0,50), highlightthickness=4)
        self.graph_temp_frame.create_graph()
        # Stiring subsystem
        self.stiring_frame = tkinter.Frame(self.control_frame, highlightthickness=4) # TODO potentially add borderwidth?
        self.stiring_labels = self.create_subsystem_labels("Stiring", self.stiring_frame)

        self.graph_stiring_frame = Subsystem_Graph(self.graph_frame, self.rpm_values, self.get_new_rpm_data, (0,1500),highlightthickness=4)
        self.graph_stiring_frame.create_graph()

        # PH subsystem
        self.ph_frame = tkinter.Frame(self.control_frame, highlightthickness=4) # TODO potentially add borderwidth?
        self.ph_labels = self.create_subsystem_labels("PH", self.ph_frame)

        self.graph_ph_frame = Subsystem_Graph(self.graph_frame, self.ph_values, self.get_new_ph_data, (0,7),highlightthickness=4)
        self.graph_ph_frame.create_graph()
        

        # Colour and Pack the widgets at the end
        self.set_colours()
        self.pack_gui()

    def get_new_temp_data(self):
        return float(self.temperature_labels[Subsystem_Label.CURRENT_VALUE.value]["text"])

    def get_new_rpm_data(self):
        return float(self.stiring_labels[Subsystem_Label.CURRENT_VALUE.value]["text"])

    def get_new_ph_data(self):
        return float(self.ph_labels[Subsystem_Label.CURRENT_VALUE.value]["text"])

    
    def create_subsystem_labels(self, subsystem: str, root) -> List[tkinter.Label]:
        # Create labels for each subsystem based on the indices specified by the Subsystem_Label ENUM
        labels = [None for i in Subsystem_Label]
        labels[Subsystem_Label.TITLE.value] = tkinter.Label(root, text=subsystem+" subsystem:", height=1)
        labels[Subsystem_Label.TARGET_TITLE.value] = self.stiring_target_title = tkinter.Label(root, text="Target value: ")
        labels[Subsystem_Label.TARGET_VALUE.value] = tkinter.Label(root, text=self.default_values[subsystem])
        labels[Subsystem_Label.CURRENT_TITLE.value] = tkinter.Label(root, text="Current value: ")
        labels[Subsystem_Label.CURRENT_VALUE.value] = tkinter.Label(root, text="0.0")
        # Create buttons for incrementing/decrementing target values
        labels[Subsystem_Label.TARGET_DECREMENT.value] = tkinter.Button(root, name="decrement_"+subsystem, image=self.decrement_icon, command= lambda: self.decrement_target_value(subsystem))
        labels[Subsystem_Label.TARGET_INCREMENT.value] = tkinter.Button(root, name="increment_"+subsystem, image=self.increment_icon, command= lambda: self.increment_target_value(subsystem))
        return labels


    def pack_gui(self):
        self.title.pack()
        self.control_frame.pack(side=tkinter.LEFT, fill=tkinter.X, expand=True)
        self.graph_frame.pack(side=tkinter.RIGHT, fill=tkinter.X, expand=True)
        self.temperature_frame.pack(fill=tkinter.X, side=tkinter.TOP, expand=True)
        self.stiring_frame.pack(fill=tkinter.X, side=tkinter.TOP, expand=True)
        self.ph_frame.pack(fill=tkinter.X, side=tkinter.TOP, expand=True)
        self.pack_subsystem_labels() 
        
        # Graphs
        self.graph_temp_frame.pack(side=tkinter.RIGHT, fill=tkinter.X, expand=True)
        self.graph_temp_frame.pack_widget(fill=tkinter.X, expand=True) 
        
        self.graph_stiring_frame.pack(side=tkinter.RIGHT, fill=tkinter.X, expand=True)
        self.graph_stiring_frame.pack_widget(fill=tkinter.X, expand=True) 

        self.graph_ph_frame.pack(side=tkinter.RIGHT, fill=tkinter.X, expand=True)
        self.graph_ph_frame.pack_widget(fill=tkinter.X, expand=True) 

    def pack_subsystem_labels(self):
        # Pack all subsystem labels and buttons
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
                elif j == Subsystem_Label.TARGET_DECREMENT.value:
                    to_pack[j].grid(row=j,column=1)
                elif j == Subsystem_Label.TARGET_INCREMENT.value:
                    to_pack[j].grid(row=j-1, column=2)
                else:
                    to_pack[j].grid(row=j, column=1)

    def decrement_target_value(self, subsystem: str):
        print(f"{subsystem}'s decrement button pressed!")
        modified = None
        decrement = self.subsystem_increments[subsystem]
        if subsystem == "Temperature":
            modified = self.temperature_labels
        elif subsystem == "Stiring":
            modified = self.stiring_labels
        elif subsystem == "PH":
            modified = self.ph_labels
        else:
            raise Exception("Error when decrementing target val of subsystem GUI with name: " + subsystem)
        
        target_label = modified[Subsystem_Label.TARGET_VALUE.value]
        # DEBUGGING
        if DEBUGGING:
            target_label = modified[Subsystem_Label.CURRENT_VALUE.value]
        # -----
        current_value = float(target_label["text"]) 
        current_value -= decrement
        if current_value < self.lower_bounds[subsystem]:
            current_value = self.lower_bounds[subsystem]

        target_label["text"] = current_value
        # TODO send msg to controller to decrement the value 

    def increment_target_value(self, subsystem: str):
        print(f"{subsystem}'s increment button pressed!")
        modified = None
        increment = self.subsystem_increments[subsystem]
        if subsystem == "Temperature":
            modified = self.temperature_labels
        elif subsystem == "Stiring":
            modified = self.stiring_labels
        elif subsystem == "PH":
            modified = self.ph_labels
        else:
            raise Exception("Error when incrementing target val of subsystem GUI with name: " + subsystem)

        target_label = modified[Subsystem_Label.TARGET_VALUE.value]
        # DEBUGGING
        if DEBUGGING:
            target_label = modified[Subsystem_Label.CURRENT_VALUE.value]
        # -----
        current_value = float(target_label["text"]) 
        current_value += increment
        if current_value > self.upper_bounds[subsystem]:
            current_value = self.upper_bounds[subsystem]

        target_label["text"] = current_value

    def register_controller(self, controller):
        self.controller = controller

    def mainloop(self):
        self.root.mainloop()


if __name__ == "__main__":
    g = View()
    g.mainloop()