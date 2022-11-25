#Color class to convert from RGB to HSV
class Color:
	
	def __init__(self, r, g, b):
		self.r = r
		self.g = g
		self.b = b
		self.h = 0
		self.s = 0
		self.v = 0
		self.rgb_to_hsv()

	def rgb_to_hsv(self):
		r = self.r / 255
		g = self.g / 255
		b = self.b / 255
		cmax = max(r, g, b)
		cmin = min(r, g, b)
		diff = cmax-cmin

		if cmax == cmin:
			self.h = 0
		elif cmax == r:
			self.h = (60 * ((g-b)/diff) + 360) % 360
		elif cmax == g:
			self.h = (60 * ((b-r)/diff) + 120) % 360
		elif cmax == b:
			self.h = (60 * ((r-g)/diff) + 240) % 360

		if cmax == 0:
			self.s = 0
		else:
			self.s = (diff/cmax) * 100

		self.v = cmax * 100
		return (self.h, self.s, self.v)

	def hsv_to_rgb(self):
		h = self.h
		s = self.s / 100
		v = self.v / 100
		c = v * s
		x = c * (1 - abs((h/60) % 2 - 1))
		m = v - c
		r, g, b = 0, 0, 0

		if 0 <= h < 60:
			r, g, b = c, x, 0
		elif 60 <= h < 120:
			r, g, b = x, c, 0
		elif 120 <= h < 180:
			r, g, b = 0, c, x
		elif 180 <= h < 240:
			r, g, b = 0, x, c
		elif 240 <= h < 300:
			r, g, b = x, 0, c
		elif 300 <= h < 360:
			r, g, b = c, 0, x

		r, g, b = (r+m)*255, (g+m)*255, (b+m)*255

		return (int(r), int(g), int(b))

	# decrease the brightness of the color
	def dim(self, amount):
		self.v = self.v * amount
		return self.hsv_to_rgb()