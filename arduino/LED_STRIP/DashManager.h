#ifndef DashManager_h
#define DashManager_h

#include <Arduino.h>
#include <FastLED.h>
#include <list>

#include "Dash.h"

class DashManager {
    public:
        DashManager(int refreshRate);

        // Adds a newly managed dash.
        void addDash(Dash dash);

        // Removes all managed dashes.
        void clearDashes();

        // If applicable, advances all managed dashes by one tick.
        void updateDashes();
        CRGB* getMergedLeds(int numLeds);

    private:
        // The dashes managed by this instance.
        std::list<Dash> dashes;

        // How fast each dash should be updated, in ms.
        int refreshRate;

        // The last time the dashes were updated, in ms.
        int lastUpdateTimestamp;
};

#endif
