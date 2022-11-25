#include <Arduino.h>
// create a Strip calss
class Strip {
public:

    Strip(rgb_color dotstar) {
        // set an internal varaiable to the length of the dotstar
        length = dotstar.length();
      
    }
    // set an internal varaiable to the length of the dotstar
    uint16_t length;
    rgb_color dotstar;
    
    // create a public function to fill the strip with a color
    void fillStrip(Color color) {
      for (int i = 0; i < NUMPIXELS; i++) {
        dotstar[i], color.red, color.green, color.blue);
      }
      strip.show();
    }
    

};