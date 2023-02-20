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
            #print("Value cant be turned into an int")
            return value