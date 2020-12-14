import serial

class Model:
    def __init__(self):
        self.arduino_serial: serial.Serial = None
        self.controller: Controller = None

    def serial_connect(self, address: str):
        print(f"Trying to connect to {address}...")
        self.arduino_serial: serial.Serial = serial.Serial(address, 9600, timeout=1)
        print("Connected succesfully!")

    def mainloop(self):
        while True:
            data = self.arduino_serial.readline()[:-1] # Cut out the Endline char
            if data:
                current_vals = data.split(" ")
                self.controller.display_data(float(current_vals[0]), float(current_vals[1]), float(current_vals[2]))

    def set_target(self,target_temperature: float, target_rpm: float, target_ph: float):
        self.arduino_serial.write(str(target_temperature) + ' ' + str(target_rpm) +\
                                 ' ' + str(target_ph))

    def register_controller(self, controller):
        self.controller = controller
