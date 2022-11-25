#ifndef Strip_h
#define Strip_h

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
    
    

};

#endif