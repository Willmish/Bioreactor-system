from gui import View
from model import Model

class Controller:
    def __init__(self):
        self.view = View() 
        self.model = Model() 
        self.view.register_controller(self)
        self.model.register_controller(self)

    def run(self):
        # Start listening on simduino Serial port, start the gui
        self.model.mainloop() # TODO uncomment when snooping working
        self.view.mainloop()

if __name__ == "__main__":
    controller = Controller()
    controller.run()
