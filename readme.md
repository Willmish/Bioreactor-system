# Bioreactor-system
University coursework for ENGF0001 group 64
SimAVR simulation of a bioreactor system for vaccine transport. It simulates an Arduino along with a PH sensor and acid/alkaline pumps, motor encoder and dc motor for stiring, a heating element and a thermometer.

The emulated Arduino interfaces with a Python application via a serial connection. Below is a GIF of the application running and controlling the system: ![gui_working](https://user-images.githubusercontent.com/26546660/116811972-7f81a880-ab4c-11eb-810c-e201a4780853.gif)

Stiring subsytem is controlled by a simple P (Proportional) RPM selection, while the temperature and PH subsystem utilise PID control.

Repository architecture:
- Master branch contains the GUI along with integrated subsystems.
- Branches heating-subsystem, ph-subsystem, stiring-subsystem contain modfied sketch.ino files with only those subsystems implemented.
