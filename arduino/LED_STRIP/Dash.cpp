#include <Arduino.h>
#include <FastLED.h>

#include "Dash.h"

Dash::Dash(int _numLeds, int _length, bool _startsLeftToRight, int _startPosition, int _maxIterations, bool _bounces, int _stepSize, CRGB _color) {
    int numLeads =  _numLeds;
    int length = _length;
    bool directionLeftToRight = _startsLeftToRight;
    int position = _startPosition;
    int maxIterations = _maxIterations;
    bool bounces = _bounces;
    int stepSize = _stepSize;
    CRGB color = _color;
}
