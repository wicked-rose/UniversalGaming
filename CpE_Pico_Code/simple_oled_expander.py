#this is a simple file to use both oled and expander
#import board support libraries, including HID.
#test
import board
import digitalio
import analogio
import usb_hid
#test
#Libraries for the OLED Display
from adafruit_display_text import label
import adafruit_displayio_ssd1306
import terminalio
import displayio
import busio

import supervisor

import functions

from time import sleep

#Libraries for communicating as a Keyboard device.
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.keycode import Keycode

#library for communicating as a gamepad
from hid_gamepad import Gamepad

from adafruit_hid.mouse import Mouse
mouse = Mouse(usb_hid.devices)

from adafruit_hid.consumer_control_code import ConsumerControlCode
from adafruit_hid.consumer_control import ConsumerControl

mediacontrol = ConsumerControl(usb_hid.devices)

keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayoutUS(keyboard)
gp = Gamepad(usb_hid.devices)
verbose = 1

button_pins = (
board.D24,board.D25
)

def update_oled(mode,joystickmode):
    splash = displayio.Group()
    display.show(splash)

    # Draw a label

    text = "Mode : " + str(mode)
    text_area = label.Label(
    terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=3
    )
    splash.append(text_area)
    text = mode_names[int(mode)]
    text_area = label.Label(
        terminalio.FONT, text=text, color=0xFFFF0F, x=3, y=23
    )
    
    splash.append(text_area)
    text = joystickmode
    text_area = label.Label(
        terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=43
    )
    splash.append(text_area)

 
gamepad_buttons_inorder =           (1, 2)
gamepad_buttons_rogueLegacy =       (2, 3, 1,4, 7, 8, 5,6, 9, 10, 11, 12, 13, 14, 15,16)



mode = 1
#Define OLED Parameters
WIDTH = 128
HEIGHT = 64
BORDER = 5

buttons = [digitalio.DigitalInOut(pin) for pin in button_pins]


#Initialize The Buttons
for button in buttons:
    button.direction = digitalio.Direction.INPUT
    button.pull = digitalio.Pull.UP


# Use for I2C for display
i2c = busio.I2C(board.D9, board.D6)
display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)
#display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=WIDTH, height=HEIGHT)
"""
i2c0 = busio.I2C(board.D13, board.D12)


mcp1 = MCP23017(i2c0, address=0x21)
mcp0 = MCP23017(i2c0, address=0x20)
buttons = [digitalio.DigitalInOut(pin) for pin in button_pins]

pins  = []
pins0 = []
for pin in range(0, 16):
    pins0.append(mcp0.get_pin(pin))
    
for pin in pins0:
    pin.direction = Direction.INPUT
    pin.pull = Pull.UP
    
for pin in pins0:
    buttons.append(pin)
    
gamepad_buttons_inorder = [1, 2]


display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=WIDTH, height=HEIGHT)

#Make the display context.
splash = displayio.Group()
display.show(splash)

# Draw a label

text = "Mode : " + str(mode)
text_area = label.Label(
terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=3
)
splash.append(text_area)
text = mode_names[mode]
text_area = label.Label(
    terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=23
)
splash.append(text_area)

def debounce():
    sleep(0.2)
"""


#defaults
mode = 1
count = 0
serialRead = 1
oldmode = 6
oldLayoutButtonValue = True
layout_num = 1
joystickmode = "analog"
oldJoystickMode = "analog"
gamepad_buttons = list(gamepad_buttons_inorder)

#update_oled(mode,joystickmode)

print("Hello! Universal Gaming Controller Now Active.")
print("Joystick Mode: ",joystickmode, ". Button Layout: Default.")


while True:
            
            #update_oled("hello","world")
            
            for i, button in enumerate(buttons):
                    gamepad_button_num = gamepad_buttons[i] # Minus 4 to ignore directionals
                    if button.value:
                        displayword  = "pressed"
                        gp.release_buttons_ptr(gamepad_button_num)
                    else:
                        displayword  = "NotPressed"
                        print("button",i,"=",button.value, "was pressed")#grab gpio value from list of buttons
                        gp.press_buttons_ptr(gamepad_button_num)