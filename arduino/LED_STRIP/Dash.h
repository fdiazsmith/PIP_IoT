#ifndef Dash_h
#define Dash_h

#include <Arduino.h>
#include <FastLED.h>

class Dash {
    public:
        Dash(int _numLeds, int _length, bool _startsLeftToRight, int _startPosition, int _maxIterations, bool _bounces, int _stepSize, CRGB _color);

        int numLeds;
        int length;
        bool directionLeftToRight;
        int position;
        int numIterations;
        int maxIterations;
        // Defining the "out-of-bounds" behavior. In an ideal world, this is represented as an enumeration.
        // Whether the dash "bounces from side to side" or wraps around.
        bool bounces;
        int stepSize;
        CRGB color;
        CRGB *leds;


    private:
        // Whether the dash starts with moving from left to right.
        bool startsLeftToRight;

        // The index of the dash's starting position.
        int startPosition;
};

#endif
