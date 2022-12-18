#ifndef Dash_h
#define Dash_h

#include <Arduino.h>
#include <FastLED.h>

class Dash{
    public:
        Dash(int num_leds);
        void fill();
        void setup(int length_, CRGB mainColor_, int delay_ms_, bool wrapindex_);
        void setup(int length_, CRGB mainColor_, int delay_ms_, bool wrapindex_, bool bounce_, int direction_, float domainStart_, float domainEnd_, float life_);
        void fadeall();

        void tick_ms();

        void mover();
        void turnOff();


        int pos;
        int len;
        bool wrap;
        bool bounce;
        int direction;
        float domainStart;
        float domainEnd;
        float life = 9999; 
        bool kill = false;
        
        CRGB color;
        int delay_ms;
        CRGB *leds;
        float age = 0.0;

    private:
        int _num_leds;
        unsigned long _lastMillis;
        int _cumulativeTicks = 0.0;
        int _mainBrightness = 255;
};


#endif
