from gui import View
from model import Model

class Controller:
    def __init__(self):
        self._view = View() 
        self._model = Model() 
        self._view.register_controller(self)
        self._model.register_controller(self)

    def run(self):
        # Start listening on simduino Serial port, start the gui
        #self._model.serial_connect("/tmp/simavr-uart0")
        #self._model.mainloop() # TODO uncomment when snooping working
        self._view.create_gui()
        self._view.mainloop()

if __name__ == "__main__":
    controller = Controller()
    controller.run()
