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
            data = self.arduino_serial.readline()[:-2] # Cut out the Endline char
            print(data)
            if data:
                data = str(data, encoding="ascii")
                current_vals = data.split()
                print(current_vals)
                self.controller.display_data(float(current_vals[0]), float(current_vals[1]), float(current_vals[2]))
                self.arduino_serial.reset_input_buffer()

    def set_target(self,target_temperature: float, target_rpm: float, target_ph: float):
        self.arduino_serial.reset_output_buffer()
        message = str(target_temperature) + ' ' + str(target_rpm) +\
                                 ' ' + str(target_ph)
        
        self.arduino_serial.write(bytes(message, 'ascii'))
    
    def get_current(self):
        self.arduino_serial.write(bytes("get current", 'ascii'))

    def register_controller(self, controller):
        self.controller = controller
