import serial

class Model:
    def __init__(self):
        self.arduino_serial: serial.Serial = None
        self.controller: Controller = None

    def serial_connect(self, address: str):
        self.arduino_serial: serial.Serial = serial.Serial(address, 9600, timeout=1)

    def mainloop(self):
        while True:
            data = self.arduino_serial.readline()[:-1] # Cut out the Endline char
            if data:
                print(data)


    def register_controller(self, controller):
        self.controller = controller
