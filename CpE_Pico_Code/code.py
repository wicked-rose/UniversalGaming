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

#Create a collection of GPIO pins that represent the buttons
#This includes the digital pins for the Directional Pad.
#They can be used as regular buttons if using the analog inputs instead
button_pins = (board.D12,board.D13,board.A1,board.D6,board.D5,board.D24,board.D25,board.D9,board.D10,board.D4)

def update_oled(mode):
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
        terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=23
    )
    splash.append(text_area)

def simple_serial_read():
    if supervisor.runtime.serial_bytes_available:
        value = input().strip()
        print("value", value)
        # Sometimes Windows sends an extra (or missing) newline - ignore them
        return value


def serial_read():
    if supervisor.runtime.serial_bytes_available:
        value = input().strip()
        print("value", value)
        try:
          return int(value)
        except:
            print("Value cant be turned into an int")
            return value


"""
def serial_read():
    if supervisor.runtime.serial_bytes_available:
        value = input().strip()
        print("value", value)
        # Sometimes Windows sends an extra (or missing) newline - ignore them
        if type(value) == type(3): #aka is an int
            if value >= 1 and value <= 5:
                return value
        elif type(value) == type("hello"):
            if int(value) >= 1 and int(value) <= 5:
                return int(value)
        else:
            return -1
"""
def range_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

# Map the buttons to button numbers on the Gamepad
# gamepad_buttons[i] will send that button number when buttons[i]
# is pushed.
"""1:
"""
gamepad_buttons = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
gamepad_buttons_layout_default = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
gamepad_buttons_layout2 = ( 5, 6, 7, 8, 1, 2, 3, 4, 9, 10, 11, 12, 13, 14, 15, 16)

#Keyboard Mode Button Definitions
keyboard_buttons = {0 : Keycode.UP_ARROW, 1 : Keycode.LEFT_ARROW, 2 : Keycode.DOWN_ARROW, 3 : Keycode.RIGHT_ARROW,
                  4 : Keycode.LEFT_CONTROL, 5 : Keycode.SPACE, 6 : Keycode.W, 7 : Keycode.ENTER, 8 : Keycode.LEFT_ALT
                    , 9 : Keycode.ENTER, 10 : Keycode.ENTER, 11 : Keycode.ENTER, 12 : Keycode.ENTER, 13 : Keycode.ENTER
                    , 14 : Keycode.ENTER, 15 : Keycode.ENTER}

#FPS Mode Button Definitions
fps_buttons = {0 : Keycode.W, 1 : Keycode.A, 2 : Keycode.S, 3 : Keycode.D,
                  4 : Keycode.LEFT_CONTROL, 5 : Keycode.SPACE, 6 : Keycode.LEFT_ALT, 7 : Keycode.ENTER,
               8 : Keycode.ENTER, 9 : Keycode.ENTER, 10 : Keycode.ENTER, 11 : Keycode.ENTER, 12 : Keycode.ENTER
               , 13 : Keycode.ENTER, 14 : Keycode.ENTER, 15 : Keycode.ENTER}

#List of defind mode names
mode_names = {1 : 'Gamepad', 2 : 'Keyboard', 3 : 'FPS', 4 : "Mouse", 5 : "Multimedia"}

#Set Default Mode To 1
mode = 2
#Define OLED Parameters
WIDTH = 128
HEIGHT = 64
BORDER = 5

buttons = [digitalio.DigitalInOut(pin) for pin in button_pins]

modeChangeButton = digitalio.DigitalInOut(board.A0)
modeChangeButton.direction = digitalio.Direction.INPUT
modeChangeButton.pull = digitalio.Pull.UP

#Initialize The Buttons
for button in buttons:
    button.direction = digitalio.Direction.INPUT
    button.pull = digitalio.Pull.UP
    
# Setup for Analog Joystick as X and Y
ax = analogio.AnalogIn(board.A3)
ay = analogio.AnalogIn(board.A2)

displayio.release_displays()


# Use for I2C for display
i2c = busio.I2C(board.SCL, board.SDA)
display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)

#Equivalent of Arduino's map() function
def range_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min
  

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
mode = 1
update_oled(mode)
count = 0
tempMode = 1
tempMode2 = 0
oldmode = 6
while True:

    #if supervisor.runtime.serial_bytes_available: #only read serial when bytes are available
    oldmode = mode
    
        
    if supervisor.runtime.serial_bytes_available:
        tempMode = serial_read()
        if type(tempMode) == type(2):
            mode = tempMode
            if mode != oldmode:
                print ("old mode is type ",type(oldmode) , "for oldmode:",oldmode)
                print ("serial read gives type",type(tempMode) , "for typing this:",tempMode)
    
    #Check to see if the mode change button is pressed.
    if  modeChangeButton.value == False:
        print("mode should be incremented")
        mode = mode + 1
        sleep(0.1)
        if mode > 5:
            mode = 1
            
    if int(mode) >=1 and int(mode) <= 5:
        if mode != oldmode:
            update_oled(mode)
    
    if (count >= 10):
        count = 0
        
        #print ("mode =", mode)
        #print ("mode ==1: ", mode ==str(1))
        #print ("mode ==2: ", mode ==str(2))
        #print ("mode ==3: ", mode ==str(3))
        #print ("mode ==4: ", mode ==str(4))
    count = count +1
    
    
    
    
    
    if mode == str(1):
        # Check value of up, down, left and right buttons
        # and set the joystick values appropriately.
        # can be replaced with values from analog stick instead
        #Not keyboard presses for directional
        #So check them seperately first
        #Set Joystick movements
        layout = serial_read()
        
        
        gp.move_joysticks(
            gp.move_joysticks(
        x=range_map(ax.value, 0, 65535, -127, 127),
        y=range_map(ay.value, 0, 65535, 127, -127),
    )
        )
        
        # Go through all the button definitions, and
        # press or release as appropriate
        for i, button in enumerate(buttons):
            if i > 3: #Skip the first 4, since they're the directionals
                gamepad_button_num = gamepad_buttons[i - 4] # Minus 4 to ignore directionals
                if button.value:
                    gp.release_buttons(gamepad_button_num)
                else:
                    gp.press_buttons(gamepad_button_num)
        
    if mode == str(2): # Keyboard Mode
            
        for i, button in enumerate(buttons):
            print("button",i,"=",button.value)
            if button.value:
                keyboard.release(keyboard_buttons[i])
            else:
                keyboard.press(keyboard_buttons[i]) 
    
    #FPS Mode
    if mode == str(3):
        for i, button in enumerate(buttons):
            gamepad_button_num = gamepad_buttons[i]
            if button.value:
                keyboard.release(fps_buttons[i])
            else:
                keyboard.press(fps_buttons[i])
                
    if mode == str(4):
        if not buttons[0].value:
            mouse.move(y=-4)
        if not buttons[2].value:
            mouse.move(y=4)
        if not buttons[1].value:
            mouse.move(x=-4)
        if not buttons[3].value:
            mouse.move(x=4)
        if not buttons[4].value:
            mouse.click(Mouse.LEFT_BUTTON)
            sleep(0.2)
        if not buttons[5].value:
            mouse.click(Mouse.RIGHT_BUTTON)
            sleep(0.2)

    if mode == str(8): #replaced 5 bc i dont want it to be 5 rn. dont have enough buttos assigned for 5
        if not buttons[0].value:
            mediacontrol.send(ConsumerControlCode.VOLUME_INCREMENT)
            debounce()
        if not buttons[2].value:
            mediacontrol.send(ConsumerControlCode.VOLUME_DECREMENT)
            debounce()
        if not buttons[1].value:
            mediacontrol.send(ConsumerControlCode.SCAN_PREVIOUS_TRACK)
            debounce()
        if not buttons[3].value:
            mediacontrol.send(ConsumerControlCode.SCAN_NEXT_TRACK)
            debounce()
        if not buttons[4].value:
            mediacontrol.send(ConsumerControlCode.PLAY_PAUSE)
            debounce()
        if not buttons[5].value:
            mediacontrol.send(ConsumerControlCode.STOP)
            debounce()
        if not buttons[9].value:
            mediacontrol.send(ConsumerControlCode.MUTE)
            debounce()