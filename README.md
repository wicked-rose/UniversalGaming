# UniversalGaming


# Controller
## Physical Setup
Joystick 1: x, y -> A0, A1
Joystick 2: x, y -> A2, A3
The rest of the pins (except for Rst, 3.3v, GND, Bat, En, USB, and 13)
are used as button inputs. Connect the pin to one side of the button and ground on the other.

## Usage
[Install CircuitPython on the Feather](https://learn.adafruit.com/welcome-to-circuitpython/installing-circuitpython)
Copy the contents of "CpE_Controller" to the CIRCUITPY drive
Unplug and replug the Feather
### Windows
Open "Set up USB game controllers"
Select the controller
Click "Properties" to see the joystick movement and button presses
### Linux
Install "jstest-gtk" to see joystick movement and button presses
