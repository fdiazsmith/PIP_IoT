from micropython_dotstar import DotStar
from machine import SoftSPI, Pin
import math

led_count = 240

def color_gen(i=0):
    while True:
        i += 1
        red = (1 + math.sin(i * 0.1)) * 127 + 1
        green = (1 + math.sin(i * 0.1324)) * 127 + 1
        blue = (1 + math.sin(i * 0.1654)) * 127 + 1

        total = red + green + blue
        red = int(red / total * 255)
        green = int(green / total * 255)
        blue = int(blue / total * 255)

        yield red, green, blue

colors = color_gen()

def animation_1(led_count):
    data = [(0, 0, 0) for i in range(led_count)]
    step = 0
    while True:
        data[step % led_count] = next(colors)
        yield data
        step += 1
        
def animation_2(led_count, offset=3, length=1):
    data = [(0, 0, 0) for i in range(led_count)]
    offsets = range(0, led_count, offset)
    step = 0
    while True:
        pos = step % led_count
        rgb = next(colors)
        for off in offsets:
            data[pos - off] = rgb
            data[pos - off - length] = (0, 0, 0)
        yield data
        step += 1


def animation_3(led_count, offset=10):
    data = [(0, 0, 0) for i in range(led_count)]
    offsets = range(0, led_count, offset)
    step = 0
    while True:
        pos = step % led_count
        rgb = next(colors)
        for off in offsets:
            data[pos - off] = rgb
        yield data
        step += 1

spi = SoftSPI(sck=Pin(18), mosi=Pin(23), miso=Pin(19)) # Configure SPI - see note below
dotstar = DotStar(spi, led_count) # 2nd arg = number of leds
        
while True:
    anim_1 = animation_3(led_count)
    for i in range(led_count):
        value = next(anim_1)
        print('i',i)

        for j in range(led_count):
            print('value',value[j])
            dotstar[j] = value[j]
