from gui import View
from model import Model
import threading

class Controller:
    def __init__(self):
        self._view = View() 
        self._model = Model() 
        self._view.register_controller(self)
        self._model.register_controller(self)

    def run(self):
        # Start listening on simduino Serial port, start the gui
        self._model.serial_connect("/tmp/simavr-uart0")
        self._view.create_gui()
        thread1 = threading.Thread(target=self._model.mainloop) # TODO uncomment when snooping working
        thread1.start()


        self._view.mainloop()


    def display_data(self,current_temperature: float, current_rpm: float, current_ph: float):
        self._view.set_data(current_temperature, current_rpm, current_ph);

    def set_target(self,target_temperature: float, target_rpm: float, target_ph: float):
        self._model.set_target(target_temperature, target_rpm, target_ph);

if __name__ == "__main__":
    controller = Controller()
    controller.run()
