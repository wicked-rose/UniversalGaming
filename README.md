# UniversalGaming


# Controller
## Physical Setup
* Joystick 1: x, y -> A2, A3
* Joystick SW: D4
* The rest of the pins (except for Rst, 3.3v, GND, Bat, En, USB, and 13)
* are used as button inputs. Connect the pin to one side of the button and ground on the other.

board.A0: "A button"
board.A1: "X button"
board.D25:"B button"
board.D24:"Y button"
board.MOSI: Anything Button
board.MISO: Joystick Change button
board.RX: Layout_Change button
board.TX,
board.D4,
board.D13: Anything button
board.D12: Anything button
board.D11: Anything button 
board.D10: Dpad Down
board.D9: Dpad Left
board.D6:Dpad Up
board.SCL: OLED SCL
board.SDA: OLED SCA
)


## Usage
* [Install CircuitPython on the Feather](https://learn.adafruit.com/welcome-to-circuitpython/installing-circuitpython)
* Copy the contents of "CpE_Controller" to the CIRCUITPY drive
* Unplug and replug the Feather
### Windows
* Open "Set up USB game controllers"
* Select the controller
* Click "Properties" to see the joystick movement and button presses
### Linux
* Install "jstest-gtk" to see joystick movement and button presses
