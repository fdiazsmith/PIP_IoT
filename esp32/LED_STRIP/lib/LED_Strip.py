from micropython_dotstar import DotStar
# from perlin import PerlinNoiseFactory
from machine import SoftSPI, Pin
import math
import time


# define PI
PI = 3.14159265358979323846264338327

#create a class to add two numbers
class LED_STRIP:
	#define the constructor with arguments: led_count
	def __init__(self, led_count):
		self.led_count = led_count
		# self.noise = perlin.PerlinNoiseFactory(1, octaves=4, tile=(0, 0, 0))
		self.spi = SoftSPI(sck=Pin(18), mosi=Pin(23), miso=Pin(19)) # Configure SPI - see note below
		self.dotstar = DotStar(self.spi, led_count) # 2nd arg = number of leds
		self.color = (255, 0, 0) # red
		self.COLOR_OFF = (0, 0, 0)
		self.time = 0
		self.dotstar.brightness = 0.1
		self.p = 0

	def fill(self, color):
		self.dotstar.fill(color)
	
	def tick(self, tick):
		t = 0
		# if t is greater than tick, then reset t to 0
		if time.time() - self.time  > tick:
			self.p += 1
			self.time = time.time()

		# if p is greater than the number of leds, then reset p to 0
		if self.p > self.led_count-1:
			self.p = 0
		return self.p/self.led_count

	def timedMover(self, pos , length = 3):
		# subtract 1 from self.p and turn dotstar off if self.p is greater than 0
		# if self.p - length > 0:
		# 	self.dotstar[self.p - length] = self.colorOff

		# describe the shape of the section
		section = [0]*length
		for i in range(length):
			n = i/length
			# section[i]  =  ( int((math.cos( (PI)+(n*2*PI)) * .5 )+ .5)*255,0,0)
			section[i]  =  ( 255,0,0)
		mid = math.floor(length/2)
		# todo: this works in one direction it does not erase the previouse loop 
		for i in range(length):
			try:
				self.dotstar[math.floor(pos * self.led_count )+ i - mid] = section[i]
			except:
				self.dotstar[(math.floor(pos * self.led_count ) - self.led_count) + i - mid] = section[i]
				pass
	
		self.dotstar.show()
		print(pos)

		return 
	
	def normalizedHandler(self, npos):
		for i in range(self.led_count):
			n = i/self.led_count
			self.dotstar[i] = n
		self.dotstar.show()
		return

	def sinewave(self, phase, freq=4, amp=1, offset=0):
		for i in range(self.led_count):
			n = i/self.led_count
			self.dotstar[i] = ( int((math.sin(phase+(n*freq)) * amp )+ offset)*255,0	,0)
		self.dotstar.show()
		return
