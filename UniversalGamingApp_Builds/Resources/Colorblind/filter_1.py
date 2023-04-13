'''
Goal: Transform an image into a more colorblind-friendly palette

This will just focus on editing one image as a proof of concept. If we can alter one image to
be color-blind friendly, theoretically we could apply this as a filter that would affect the
appearance of the user's screen
'''
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as im

# select color blind mode for filter
error = True
while(error == True):
    print("Select which color blind mode you would like to apply:")
    print("1. Deuteranopia\n2. Protanopia\n3. Tritanopia")
    color_blind_mode = input()

    try:
        mode = int(color_blind_mode)
        if mode > 3 or mode < 1:
            raise Exception()
        error = False
    except:
        print("Invalid input. Please enter integer with value 1-3.")



# start reading file
file_name = input("Enter file name of image to apply filter: ")
image = im.imread(file_name)
#image = im.imread("sample.jpg")

# extract rgb channels
X_arr = image.astype(np.float64) # convert array to float64
X_arr = (X_arr - np.min(X_arr))/(np.max(X_arr)-np.min(X_arr)) # re-scaling array to be [0,1]
red = X_arr[:, :, 0]
green = X_arr[:, :, 1]
blue = X_arr[:, :, 2]

row, col = red.shape

# start filtering depending on mode
if mode == 1 or mode == 2:
    # Deuteranopia (red-green) - weak green
    for i in range(row):
        for j in range(col):
            # check for grey values
            if abs(red[i][j] - green[i][j]) < 0.1 and abs(blue[i][j] - green[i][j]) < 1 and abs(
                    red[i][j] - blue[i][j]) < 0.1:
                continue
            if red[i][j] > green[i][j]:
                # make red appear more yellow
                red[i][j] *= 0.85
                green[i][j] = red[i][j]
            elif green[i][j] > blue[i][j]:
                # make green appear more blue
                blue[i][j] = green[i][j] * 0.8
                green[i][j] /= 2
                if red[i][j] > green[i][j]:
                    red[i][j] /= 2
            elif blue[i][j] > green[i][j]:
                # emphasize blue to contrast from green
                blue[i][j] *= 1.1
                if blue[i][j] > 1:
                    blue[i][j] = 1
                green[i][j] *= 0.2
                red[i][j] /= 2

elif mode == 3:
    # Tritanopia (blue-yellow)
    # we want yellow to instead look red or blue (depending on hue) and bring out more blue
    # yellow = red + green
    for i in range(row):
        for j in range(col):
            # check for grey values
            if abs(red[i][j] - green[i][j]) < 0.1 and abs(blue[i][j] - green[i][j]) < 0.1 and abs(red[i][j] - blue[i][j]) < 0.1:
                continue

            if abs(red[i][j] - green[i][j]) < 0.3:
                # change appearance of yellow-ish colors
                if red[i][j] > green[i][j]:
                    green[i][j] *= 0.5
                    red[i][j] *= 1.5
                    if red[i][j] > 1:
                        red[i][j] = 1
            else:
                green[i][j] *= 0
                blue[i][j] *= 1.5
                if blue[i][j] > 1:
                    blue[i][j] = 1

# combine channels to recreate image
M, N, D = image.shape

new_image = np.zeros([M, N, D])
new_image[:, :, 0] += red
new_image[:, :, 1] += green
new_image[:, :, 2] += blue


#display image
plt.imshow(new_image)
plt.axis(False)
plt.show()
