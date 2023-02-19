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

#Create a collection of GPIO pins that represent the buttons.
#This includes the digital pins for the Directional Pad
#They can be used as regular buttons if using the analog inputs instead
#koeyboard(x,x,x,x,x,x,up,x,x,x
button_pins = (board.A1,board.A0,board.D25,board.D24,
board.MOSI,board.D12,board.D13,board.D11,
board.SCK,board.RX,board.D4,
board.D6,board.D10,board.D9,board.D5
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
        terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=23
    )
    
    splash.append(text_area)
    text = joystickmode
    text_area = label.Label(
        terminalio.FONT, text=text, color=0xFFFFFF, x=3, y=43
    )
    splash.append(text_area)



def serial_read():
    if supervisor.runtime.serial_bytes_available:
        value = input().strip()
        print("value", value)
        try:
          return int(value)
        except:
            print("Value cant be turned into an int")
            return value


def range_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

# Map the buttons to button numbers on the Gamepad
# gamepad_buttons[i] will send that button number when buttons[i]
# is pushed.
gamepad_buttons1 =                   (1, 2, 3, 4, 5, 6, 7, 8, 10, 9, 11, 12, 13, 14, 15)
gamepad_buttons_layout_default =    (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
gamepad_buttons_layout2 =           (10, 9, 6, 5, 1, 2, 3, 4, 7, 8, 11, 12, 13, 14, 15)

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
mode = 1
#Define OLED Parameters
WIDTH = 128
HEIGHT = 64
BORDER = 5

buttons = [digitalio.DigitalInOut(pin) for pin in button_pins]

#modeChangeButton = digitalio.DigitalInOut(board.RX)
#modeChangeButton.direction = digitalio.Direction.INPUT
#modeChangeButton.pull = digitalio.Pull.UP

layoutChangeButton = digitalio.DigitalInOut(board.TX)
layoutChangeButton.direction = digitalio.Direction.INPUT
layoutChangeButton.pull = digitalio.Pull.UP

JoystickChangeButton = digitalio.DigitalInOut(board.MISO)
JoystickChangeButton.direction = digitalio.Direction.INPUT
JoystickChangeButton.pull = digitalio.Pull.UP

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

#defaults
mode = 1
count = 0
serialRead = 1
oldmode = 6
oldLayoutButtonValue = True
layout_num = 1
joystickmode = "analog"
oldJoystickMode = "analog"
gamepad_buttons = gamepad_buttons1

update_oled(mode,joystickmode)
while True:
    oldmode = mode
    #read uart if bytes are available
    
    
    
   
    #Check to see if the mode change button is pressed.
#    if  modeChangeButton.value == False:
#        print("mode should be incremented")
#        mode = mode + 1
#        sleep(0.2)
#        if mode > 5:
#            mode = 1
    #check to see if layout switch putton is pressed.
    if layoutChangeButton.value == False and layoutChangeButton != oldLayoutButtonValue:
        
        layout_num = layout_num +1
        if layout_num >2:
            layout_num = 1
        
        if layout_num == 1:
            gamepad_buttons = gamepad_buttons1 
        elif layout_num == 2:
            gamepad_buttons = gamepad_buttons_layout_default 
        debounce()
        print(" top button pressed... now:", gamepad_buttons)
        print("layout num is:", layout_num)
        oldLayoutButtonValue = True
        update_oled(mode,joystickmode)
        
        
        
    if JoystickChangeButton.value == False and layoutChangeButton != oldLayoutButtonValue:
        
        if joystickmode == "analog":
            joystickmode = "digital"
        else:
            joystickmode = "analog"
        debounce()
        print("joystick mode is now:", joystickmode)
        oldJoystickMode = joystickmode
        update_oled(mode,joystickmode)
    
    if (count >= 1000):
        count = 0
        #print("heartbeat")
    count = count +1
    
    if supervisor.runtime.serial_bytes_available:
        serialRead = serial_read()
        if type(serialRead) == type(2):
            mode = serialRead
            if mode != oldmode:
                print ("layourchangebutton value: ",layoutChangeButton.value)
        elif type(serialRead) == type("hi"): #if serial stuff is not a number:
            if serialRead == "Print Mode":
                print(mode_names[mode])
            if serialRead == "layout2":
                gamepad_buttons = gamepad_buttons_layout3
                print("2gamepad buttons changed via uart... now they are:", gamepad_buttons)
            if serialRead == "layout_default":
                gamepad_buttons = gamepad_buttons_layout_default
                print("2 gamepad buttons changed via uart... now they are:", gamepad_buttons)
    
    if int(mode) >=1 and int(mode) <= 5:
        if mode != oldmode or joystickmode != oldJoystickMode:
            update_oled(mode,joystickmode)
    
    if mode == 1:

        
        if joystickmode == "digital":
            setx = 0
            sety = 0
            #Not keyboard presses for directional
            #So check them seperately first
            if not buttons[11].value:
                sety = -127
            if not buttons[12].value:
                sety = 127
            if not buttons[13].value:
                setx = -127
            if not buttons[14].value:
                setx = 127
            #Set Joystick movements
            gp.move_joysticks(
                x=setx,
                y=sety,
            )
            
            # Go through all the button definitions, and
            # press or release as appropriate
            for i, button in enumerate(buttons):
                if i < 12: #Skip the last 4, since they're the directionals
                    gamepad_button_num = gamepad_buttons[i] # Minus 4 to ignore directionals
                    if button.value:
                        gp.release_buttons(gamepad_button_num)
                    else:
                        print("button",i,"=",button.value, "was pressed")
                        gp.press_buttons(gamepad_button_num)
        
        else:
            gp.move_joysticks(
                gp.move_joysticks(
            x=range_map(ax.value, 0, 65535, -127, 127),
            y=range_map(ay.value, 0, 65535, 127, -127),
        )
            )
            
            for i, button in enumerate(buttons):
                gamepad_button_num = gamepad_buttons[i]
                if button.value:
                    
                    gp.release_buttons(gamepad_button_num)
                else:
                    print("button",i,"=",button.value, "was pressed")
                    gp.press_buttons(gamepad_button_num)
        
    if mode == 2: # Keyboard Mode
            
        for i, button in enumerate(buttons):
            #print("button",i,"=",button.value) #optional print to show which game buttons are pushed
            if button.value:
                keyboard.release(keyboard_buttons[i])
            else:
                keyboard.press(keyboard_buttons[i]) 
    #FPS Mode
    if mode == 3:
        for i, button in enumerate(buttons):
            gamepad_button_num = gamepad_buttons[i]
            if button.value:
                keyboard.release(fps_buttons[i])
            else:
                keyboard.press(fps_buttons[i])
    #Mouse mode            
    if mode == 4:
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
            debounce()
        if not buttons[5].value:
            mouse.click(Mouse.RIGHT_BUTTON)
            debounce()

    if mode == 8: #replaced 5 bc i dont want it to be 5 rn. dont have enough buttos assigned for 5
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