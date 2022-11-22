from LED_Strip import LED_STRIP
import time
strip = LED_STRIP(20)
strip.fill((0,0,0))

while True:
  
    strip.timedMover(strip.tick(.010), 5)
    #strip.sinewave((time.time()), 4, .5, .5)
    

"""

TODO: 

"""