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
from adafruit_mcp230xx.mcp23017 import MCP23017

import supervisor

from digitalio import Direction, Pull

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
displayio.release_displays()
mediacontrol = ConsumerControl(usb_hid.devices)

keyboard = Keyboard(usb_hid.devices)
layout = KeyboardLayoutUS(keyboard)
gp = Gamepad(usb_hid.devices)
verbose = 1

#Create a collection of GPIO pins that represent the buttons.
#This includes the digital pins for the Directional Pad
#They can be used as regular buttons if using the analog inputs instead
#gamepad buttons and their functions()by index for example, 0th element is D25

#board pin indexes in the gamepad_x array shown below
button_pins = (

board.D24,board.D25,    #D24 = 0,  D25 = 1       X    O
board.SCK,board.MOSI,   #SCK = 2,  MOSI = 3      SQR  TRI
board.D6,board.MISO,    #D6 = 4,   MISO = 5      L1   R1    
board.D4,      #D4 = 6,   TX = 7        L2   R2
board.D5,      #RX = 8,   D5 = 9        SEL  STRT
board.D10,
board.A2,     #D9 = 10,  A2 = 11       L3   R3 dont rlly matter for now
board.D9,
board.D11,     #D12 = 12, D11 = 13      UP   DOWN 
board.D12,              #D10 = 14,               LFT  RGT
board.D13               #D11 = 15
)

def update_oled(mode,joystickmode, size = "big"):
    if (size == "big"):

        splash = displayio.Group()
        display.show(splash)

        # Draw a label

        text = "Mode : " + str(mode)
        text_area = label.Label(
        terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=10
        )
        
        splash.append(text_area)

    else:
    
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

def parse_remap_string(input_string):
    
        if (len(input_string.split()) < 3 or len(input_string.split()) > 3):
            return -69,-69
        blank, x, y = input_string.split()
        
        try:
            y = (int(y))
            
        except:
            y = y




        if (type(y) == type(1)):
            try:
            #if its an int, parse int stuff
                x = int(x)
                y = int(y)
                if 0 <= x <= 15:
                    x = x
                elif 0 <= y <= 15:
                    y = y
            except ValueError:
                x= -1
                y= -1
        elif (type(y) == type("mystring")): #if its given in string form, parse stringly
            
            try:
                x = int(x)
            except ValueError:
                x = -1
            
            if 0 <= x <= 15:
                    x = int(x)
                    x = x+ 0
            else:
                    x = -1

            print("Y IS:\"",y,"\"")
            if y in gamepad_buttons_map: #if the string is in the dict, return the num associated.
                    y = gamepad_buttons_map[y]
            
        return x,y


def serial_read():
    if supervisor.runtime.serial_bytes_available:
        value = input().strip()
        print("value:", value,".")
        try:
          return int(value)
        except:
            #print("Value cant be turned into an int")
            return value


def range_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

# Map the buttons to button numbers on the Gamepad
# gamepad_buttons[i] will send that button number when buttons[i]
# x's mean i dont have 
# is pushed.                        #x  x 
gamepad_buttons_rogueLegacy =       (2, 3, 1,4, 7, 8, 5,6, 9, 10, 11, 12, 13, 14, 15,16)

gamepad_buttons0 =                  (2, 4, 3, 1, 6, 7, 13, 16, 13, 15, 8, 9, 10, 9, 8,2)
gamepad_buttons_enum =              {0 : 1,1:2,2:3,3:4,4:5,5:6,6:7,7:8,8:9,9:10,10:11,11:12,12:13,13:14,14:15}#L3 is left stick click
gamepad_buttons_map =        {"X" : 0,"O":1,"Square":2,"Triangle":3,
                                    "L1":4,"R1":5,"L2":6,"R2":7,
                                    "Select":8,"Start":9,"L3":10,"R3":11,
                                    "D_UP":12,"D_DOWN":13,"D_LEFT":14,"D_RIGHT":15}


gamepad_buttons_for_demo =          (2, 3, 3, 3, 6, 7, 13, 16, 13, 15, 14, 5, 14, 15, 8)
gamepad_buttons_layout_default =    (1, 2, 3, 4, 5, 8, 13,9, 7,10,12, 6, 9, 11, 14, 15)
gamepad_buttons_layout2 =           (10, 9, 6, 5, 1, 2, 3, 4, 7, 8, 11, 12, 13, 14, 15)


#Keyboard Mode Button Definitions
keyboard_buttons = {0 : Keycode.UP_ARROW, 1 : Keycode.LEFT_ARROW, 2 : Keycode.DOWN_ARROW, 3 : Keycode.RIGHT_ARROW,
                  4 : Keycode.LEFT_CONTROL, 5 : Keycode.SPACE, 6 : Keycode.W, 7 : Keycode.ENTER, 8 : Keycode.LEFT_ALT
                    , 9 : Keycode.Q, 10 : Keycode.W, 11 : Keycode.E, 12 : Keycode.R, 13 : Keycode.T
                    , 14 : Keycode.Y, 15 : Keycode.U}

#FPS Mode Button Definitions
fps_buttons = {0 : Keycode.D, 1 : Keycode.S, 2 : Keycode.A, 3 : Keycode.W,
                  4 : Keycode.LEFT_CONTROL, 5 : Keycode.SPACE, 6 : Keycode.LEFT_ALT, 7 : Keycode.ENTER,
               8 : Keycode.ENTER, 9 : Keycode.ENTER, 10 : Keycode.ENTER, 11 : Keycode.ENTER, 12 : Keycode.ENTER
               , 13 : Keycode.ENTER, 14 : Keycode.ENTER, 15 : Keycode.ENTER}

#List of defind mode names
mode_names = {1 : 'Gamepad', 2 : 'Keyboard', 3 : 'FPS', 4 : "Mouse", 5 : "Multimedia"}

#Set Default Mode To 1
mode = 1
#Define OLED Parameters
WIDTH = 128
HEIGHT = 64
BORDER = 5
teeny = 1


i2c1 = busio.I2C(board.SCL, board.SDA) # DISPLAY OLEDS

i2c0 = busio.I2C(board.RX, board.TX) # MCPS
#board.D11.deinit()
#board.D10.deinit()


mcp1 = MCP23017(i2c1, address=0x21)
mcp0 = MCP23017(i2c0, address=0x20)
display_bus = displayio.I2CDisplay(i2c1, device_address=0x3C)
buttons = [digitalio.DigitalInOut(pin) for pin in button_pins]

pins  = []
pins0 = []
pins1 = []
for pin in range(0, 16):
    pins0.append(mcp0.get_pin(pin))
    pins1.append(mcp1.get_pin(pin))
    
for pin in pins0:
    pin.direction = Direction.INPUT
    pin.pull = Pull.UP
for pin in pins1:    
    pin.direction = Direction.INPUT
    pin.pull = Pull.UP
    
for pin in pins0:
    buttons.append(pin)
for pin in pins1:
    buttons.append(pin)
    
#create button maps of on or off values



gamepad_buttons_inorder = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
for pin in range(0,len(buttons)-15):
    gamepad_buttons_inorder.append((pin%15) + 1)

#modeChangeButton = digitalio.DigitalInOut(board.RX)
#modeChangeButton.direction = digitalio.Direction.INPUT
#modeChangeButton.pull = digitalio.Pull.UP

#layoutChangeButton = digitalio.DigitalInOut(board.TX)
#layoutChangeButton.direction = digitalio.Direction.INPUT
#layoutChangeButton.pull = digitalio.Pull.UP

#JoystickChangeButton = digitalio.DigitalInOut(board.MISO)
#JoystickChangeButton.direction = digitalio.Direction.INPUT
#JoystickChangeButton.pull = digitalio.Pull.UP

#Initialize The Buttons
for button in buttons:
    button.direction = digitalio.Direction.INPUT
    button.pull = digitalio.Pull.UP
    
# Setup for Analog Joystick as X and Y
ax = analogio.AnalogIn(board.A1)
ay = analogio.AnalogIn(board.A0)

#displayio.release_displays()


# Use for I2C for display


#Equivalent of Arduino's map() function
def range_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min
  
if (teeny == 1):
    display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=128, height=32)

else:
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
    sleep(5)

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

update_oled(mode,joystickmode)

print("Hello! Universal Gaming Controller Now Active.")
print("Joystick Mode: ",joystickmode, ". Button Layout: Default.")


while True:
    oldmode = mode
    #check to see if layout switch putton is pressed.
    
    if supervisor.runtime.serial_bytes_available: #if user typed a command and pressed enter...
        serialRead = serial_read()
        if type(serialRead) == type(2):
            if mode >= 1 and mode <= 5:
                mode = serialRead
                if mode != oldmode or joystickmode != oldJoystickMode:
                    update_oled(mode,joystickmode)
                    #print(mode,joystickmode)
            else:
                mode = mode
        elif type(serialRead) == type("string") and serialRead != "": #if serial stuff is not a number:.
            
            if serialRead == "Print Mode":
                print(mode_names[mode])
            elif serialRead == "toggle":
                print("got switch analog mode")
                if joystickmode == "analog":
                    joystickmode = "digital"
                else:
                    joystickmode = "analog"
                debounce()
                print("joystick mode is now:", joystickmode)
                oldJoystickMode = joystickmode
                update_oled(mode,joystickmode)
                #print(mode,joystickmode)
            elif serialRead.split()[0] == "remap":
                x,y = parse_remap_string(serialRead)
                if (x == -1  or y == -1):
                    print("please enter value integer values from 0 and to 15")
                else:
                    gamepad_buttons[x] = y+1
                print("gamepad button"[x], "is now ",y,"here are the buttons:",[thingy-1 for thingy in gamepad_buttons])
            elif serialRead.split()[0] == "default":
                gamepad_buttons = list(gamepad_buttons_inorder)
                print("here are the buttons:",[thingy-1 for thingy in gamepad_buttons])
            elif serialRead == "rogue":
                gamepad_buttons = list(gamepad_buttons_rogueLegacy)
                print("here are the buttons:",[thingy-1 for thingy in gamepad_buttons])
        
    #if (count >= 1000):
    #    count = 0
        #print("heartbeat")
    #count = count +1
    
    """
    if mode == 1: #when in gamepad mode...
        gp.move_joysticks(
        x =range_map(ax.value, 0, 65535, -127, 127),
        y =range_map(ay.value, 0, 65535, 127, -127),
        )
        pressed_buttons = []
        released_buttons = []
        button_states = [1] * 16
        
        for i, button in enumerate(buttons):
            gamepad_button_num = gamepad_buttons[i]
            button_states[gamepad_button_num] |= button.value

        #print(button_states)
        gp.press_buttons(button_states)

        gp.release_buttons(released_buttons)
    """
    if mode == 1: #when in gamepad mode...
        gp.move_joysticks(
        x =range_map(ax.value, 0, 65535, -127, 127),
        y =range_map(ay.value, 0, 65535, 127, -127),
        )
        pressed_buttons = []
        released_buttons = []
        for i, button in enumerate(buttons):
            gamepad_button_num = gamepad_buttons[i]
            if button.value:
                released_buttons.append(gamepad_button_num)
            else:
                print("button",i,"=",button.value, "was pressed")
                pressed_buttons.append(gamepad_button_num)

        gp.press_buttons(pressed_buttons)
        gp.release_buttons(released_buttons)
    
    elif mode == 2: # Keyboard Mode      
        for i, button in enumerate(buttons):
            #print("button",i,"=",button.value) #optional print to show which game buttons are pushed.
            if button.value:
                keyboard.release(keyboard_buttons[i])
            else:
                keyboard.press(keyboard_buttons[i]) 
    #FPS Mode
    elif mode == 3:
        for i, button in enumerate(buttons):
            gamepad_button_num = gamepad_buttons[i]
            if button.value:
                keyboard.release(fps_buttons[i])
            else:
                keyboard.press(fps_buttons[i])
    #Mouse mode            
    elif mode == 4:
        if not buttons[15].value:
            mouse.move(x=4)
        if not buttons[12].value:
            mouse.move(y=-4)
        if not buttons[13].value:
            mouse.move(y=4)
        if not buttons[14].value:
            mouse.move(x=-4)
        if not buttons[4].value:
            mouse.click(Mouse.LEFT_BUTTON)
            debounce()
        if not buttons[5].value:
            mouse.click(Mouse.RIGHT_BUTTON)
            debounce()

    elif mode == 5: #replaced 5 bc i dont want it to be 5 rn. dont have enough buttos assigned for 5
        if not buttons[0].value:
            mediacontrol.send(ConsumerControlCode.VOLUME_DECREMENT)
            debounce()
        if not buttons[3].value:
            mediacontrol.send(ConsumerControlCode.VOLUME_INCREMENT)
            debounce()
        if not buttons[1].value:
            mediacontrol.send(ConsumerControlCode.SCAN_PREVIOUS_TRACK)
            debounce()
        if not buttons[2].value:
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