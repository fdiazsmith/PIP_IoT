
# from perlin import PerlinNoiseFactory

import math
import time
from Color import Color
'''
This class only updates an arbitrary array of pixels
it assumes that the LED are in a STRIP as the name implies
it could be use for APA102 or WS2812B or any other LED strip or pixeldata

most of the methods only try to update the pixels when it is necessary

'''

# define PI
PI = 3.14159265358979323846264338327

#create a class to add two numbers
class LED_STRIP:
	#define the constructor with arguments: led_count
	def __init__(self, dotstar):
		self.led_count = len(dotstar)-1
		self.dotstar = dotstar
		self.color = Color(255, 0, 0) # red
		self.COLOR_OFF = (0, 0, 0)
		self.time = 0
		self.dotstar.brightness = 0.1
		self.p = 0

	def fill(self, color):
		self.dotstar.fill(color)
	
	def tick(self, tick,  offset = 0):
		# TODO: there is something broken about this timer thing. fix it. it does not add positions to the self.p
		t = 0
		# if t is greater than tick, then reset t to 0
		if time.ticks_ms() - self.time  > tick:
			# print('tick', time.ticks_ms() - self.time)
			self.p += 1
			self.time = time.ticks_ms()

			# if self.pis greater than the number of leds, then reset self.pto 0
		if self.p> self.led_count-1:
			self.p = 0
		# print('tick', self.p)
		return (self.p/self.led_count)+offset

	def timedMover(self, pos , length = 3):
		# don't do anything if the position has not changed
		if self.p == pos:
			return
		
		section = self.shape(length)
		mid = math.floor(length/2)
		
		# todo: this works in one direction it does not erase the previouse loop 
		for i in range(length):
			ledIndex = int(math.floor(pos * self.led_count ))
			# print(i, ledIndex, section[i])
			try:
				self.dotstar[ledIndex + (i )] = section[i]

			except:
				self.dotstar[(ledIndex - self.led_count) + (i )] = section[i]
				pass
		try:
			self.dotstar[ledIndex + length] = self.COLOR_OFF
		except:
			# self.dotstar[(ledIndex - self.led_count) + (mid )] = self.color
			pass
		self.p = pos
	
		return 
		
	def shape(self, length = 3):
		# describe the shape of the section
		section = [(0,0,0)]*length
		for i in range(length):
			n = i/length
			col = Color(200,20,255)
			section[i]  =  col.dim( ((1-math.cos(2*n*PI))*.5)  )
			# section[i]  =  ( int(((1-math.cos(2*n*PI))*.5)*255) ,0,0)
			# section[i]  =  ( 255,0,0)
		return section
	
	def normalizedHandler(self, npos):
		for i in range(self.led_count):
			n = i/self.led_count
			self.dotstar[i] = n
		
		return self.dotstar

	def sinewave(self, phase, freq=4, amp=1, offset=0):
		for i in range(self.led_count):
			n = i/self.led_count
			self.dotstar[i] = ( int((math.sin(phase+(n*freq)) * amp )+ offset)*255,0	,0)
		
		return self.dotstar

	def rainbow(self, speed=1):
		# print('rb')
		t = time.ticks_ms()* speed
		for i in range(self.led_count):
			n = i/self.led_count
			rb = Color(255,0,0)
			# rb.h = (((math.sin((n*PI)+(t))*.5)+.5)*360)
			rb.h = ((t)+n*360)%360
			# print(rb.h)
			rb.dim(.3)
			self.dotstar[i] = rb.hsv_to_rgb()

		return self.dotstar
