from LED_Strip import LED_STRIP
from micropython_dotstar import DotStar
import time
from machine import SoftSPI, Pin


"""TODO: port or find itertools for micropython"""
# self.noise = perlin.PerlinNoiseFactory(1, octaves=4, tile=(0, 0, 0))
spi = SoftSPI(sck=Pin(18), mosi=Pin(23), miso=Pin(19)) # Configure SPI - see note below
dotstar = DotStar(spi, 170) # 2nd arg = number of leds
dotstar.auto_write = False
dotstar.brighness = 0.1
strip = LED_STRIP(dotstar)
strip.fill((0,0,0))

pos = 0
tt = time.ticks_ms()
def main():
    while True:
        global pos, tt
        # indx = strip.tick(100)
        # pos += .5
        # strip.timedMover((pos%60)/60, 5)
        # strip.timedMover(((40+pos)%60)/60, 15)
        strip.rainbow(.075)
        
		
        dotstar.show()
        # print time in miliseconds
        # print(time.ticks_ms()-tt)
        tt = time.ticks_ms()
        # print(time.time())



if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        dotstar.deinit()
        pass

