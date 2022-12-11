#include <Arduino.h>
#include <FastLED.h>
#include <iterator>
#include <list>

#include "Dash.h"
#include "DashManager.h"

DashManager::DashManager(int _refreshRate) {
    std::list<Dash> dashes;

    refreshRate = _refreshRate;

    lastUpdateTimestamp = 0;
}

void DashManager::addDash(Dash dash) {
    dashes.push_back(dash);
}


void DashManager::clearDashes() {
    dashes.clear();
}

bool validateMaxIterations(Dash dash) {
    dash.numIterations++;
    if (dash.numIterations > dash.maxIterations) {
        return false;
    }
    return true;
}

// XXX: This method's out-of-bound detection always works with the dash's index closest to either
// edge as it does _not_ take the actual length of the dash into account.
bool handleDashPositionUpdate(Dash dash) {
    int newPos = 0;
    if (dash.directionLeftToRight) {
        newPos = dash.position + dash.stepSize;
        if (newPos >= dash.numLeds) {
            if (!validateMaxIterations(dash)) {
                return false;
            }

            if (dash.bounces) {
                newPos = dash.numLeds - 1;
                dash.directionLeftToRight = !dash.directionLeftToRight;
            } else {
                // We wrap around, i.e. start again at the beginning.
                newPos = 0;
            }
        }
    } else {
        newPos = dash.position - dash.stepSize;
        if (newPos < 0) {
            if (!validateMaxIterations(dash)) {
                return false;
            }

            if (dash.bounces) {
                newPos = 0;
                dash.directionLeftToRight = !dash.directionLeftToRight;
            } else {
                // We wrap around, i.e. start again at the end.
                newPos = dash.numLeds - 1;
            }
        }
    }
    dash.position = newPos;
    return true;
}

void blackoutAllDashLeds(Dash dash) {
    for (int led = 0; led < dash.numLeds; led++) {
        dash.leds[led] = CRGB::Black;
    }
}

void updateDashLeds(Dash dash) {
    for (int led = 0; led < dash.length; led++) {
        float fadingColorCode = (float) led / (float) dash.length;

        CRGB ledColor = dash.color;
        ledColor.nscale8(quadwave8(255 * fadingColorCode));

        int ledPos = dash.position + (dash.directionLeftToRight ? led : -led);

        // XXX: This works around C++ not using the modulo, but the remainder operator. Modulo would
        // return non-negative values, whereas the remainder can return negative ones.
        // See https://stackoverflow.com/questions/11720656/modulo-operation-with-negative-numbers.
        if (ledPos < 0) {
            ledPos = ledPos + dash.numLeds;
        }
        dash.leds[ledPos % dash.numLeds] = ledColor;
    }
}

bool updateDash(Dash dash) {
    if (!handleDashPositionUpdate(dash)) {
        return false;
    };
    blackoutAllDashLeds(dash);
    updateDashLeds(dash);

    return true;
}

bool shouldUpdate(int refreshRate, int lastUpdateTimestamp) {
    int now = millis();
    bool shouldUpdate = (now - lastUpdateTimestamp) > refreshRate;
    if (shouldUpdate) {
        lastUpdateTimestamp = now;
    }
    return shouldUpdate;
}

void DashManager::updateDashes() {
    if (!shouldUpdate(refreshRate, lastUpdateTimestamp)) {
        return;
    }

    std::list<Dash>::iterator it;
    for (it = dashes.begin(); it != dashes.end(); ++it) {
        Dash dash = *it;
        bool shouldRemove = !updateDash(dash);
        dashes.remove(dash);
    }
}

CRGB* DashManager::getMergedLeds(int numLeds) {
    CRGB updatedLeds[numLeds] = {CRGB::Black};

    std::list<Dash>::iterator it;
    for (it = dashes.begin(); it != dashes.end(); ++it) {
        Dash dash = *it;
        for(int led; led < numLeds; led++) {
            updatedLeds[led] = dash.leds[led];
        }
    }
    return updatedLeds;
}
