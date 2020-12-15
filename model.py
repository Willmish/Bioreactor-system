import serial
from time import sleep

class Model:
    def __init__(self):
        self.arduino_serial: serial.Serial = None
        self.controller: Controller = None

    def serial_connect(self, address: str):
        print(f"Trying to connect to {address}...")
        self.arduino_serial: serial.Serial = serial.Serial(address, 9600, timeout=1)
        sleep(0.5)
        print("Connected succesfully!")

    def mainloop(self):
        while True:
            self.get_current()
            sleep(0.2) # Wait for data to be sent by arduino
            self.send_target()
            sleep(0.2) # Wait for data to be read by arduino

    def send_target(self):
        self.controller.send_target()

    def set_target(self,target_temperature: float, target_rpm: float, target_ph: float):
        print("Sending target..")
        message = str(target_temperature) + ' ' + str(target_rpm) + ' ' + str(target_ph) + '\n'
        print(message) 
        self.arduino_serial.write(bytes(message, 'ascii'))
    
    def get_current(self):
        #while (self.arduino_serial.in_waiting):
        #    data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
        #    print(data)
        self.arduino_serial.write(bytes("get current\n", 'ascii'))
        print("Getting current..")
        sleep(0.2) # Wait for an answer from arduino
        #while (self.arduino_serial.in_waiting):
        #    data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
        #    print(data)
        data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
        if(str(data, encoding="ascii") == "Something got sent!"):
            print(data)
            data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
            print(data)
            data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
        if(str(data, encoding="ascii") == "Current requested!"):
            print(data)
            data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
        if data:
            data = str(data, encoding="ascii")
            current_vals = data.split()
            print(current_vals)
            self.controller.display_data(float(current_vals[0]), float(current_vals[1]), float(current_vals[2]))
            self.arduino_serial.reset_output_buffer()

    def register_controller(self, controller):
        self.controller = controller
