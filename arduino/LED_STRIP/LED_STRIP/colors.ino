#include <Arduino.h>
// create a color class to hold the RGB values
class Color {
  public:
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
    Color(uint8_t r, uint8_t g, uint8_t b) {
      red = r;
      green = g;
      blue = b;
    }
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    // convert rgb to hsv
    void rgbToHsv() {
      float r = red / 255.0;
      float g = green / 255.0;
      float b = blue / 255.0;
      float max = r;
      if (g > max) max = g;
      if (b > max) max = b;
      float min = r;
      if (g < min) min = g;
      if (b < min) min = b;
      float h = 0;
      float s = 0;
      float v = max;
      float d = max - min;
      s = max == 0 ? 0 : d / max;
      if (max == min) {
        h = 0; // achromatic
      } else {
        if (max == r) {
          h = (g - b) / d + (g < b ? 6 : 0);
        } else if (max == g) {
          h = (b - r) / d + 2;
        } else if (max == b) {
          h = (r - g) / d + 4;
        }
        h /= 6;
      }
      red = h * 255;
      green = s * 255;
      blue = v * 255;
    }
    // convert hsv to rgb
    void hsvToRgb() {
      float h = red / 255.0;
      float s = green / 255.0;
      float v = blue / 255.0;
      float r, g, b;
      int i = int(h * 6);
      float f = h * 6 - i;
      float p = v * (1 - s);
      float q = v * (1 - f * s);
      float t = v * (1 - (1 - f) * s);
      switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
      }
      red = r * 255;
      green = g * 255;
      blue = b * 255;
    }
};