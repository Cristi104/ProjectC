//
// Created by Cristi on 2/11/2025.
//

#ifndef PROJECTC_SETTINGS_H
#define PROJECTC_SETTINGS_H

#include <iostream>
#include "Game_exports.h"

namespace GmLib{
    class GAME_EXPORTS Settings{
    private:
        static unsigned int resolutionWidth;
        static unsigned int resolutionHeight;
        static float scaleWidth;
        static float scaleHeight;
        static bool fullscreen;
        static bool borderless;

    public:
        static void reset();
        static void load();
        static void print(std::ostream& out);
        static void save();
        static void log();
        static void apply();

        static void setResolution(unsigned int x, unsigned int y);
        static void setFullscreen(bool value);
        static void setBorderless(bool value);

        static unsigned int getResolutionWidth();
        static unsigned int getResolutionHeight();
        static float getScaleWidth();
        static float getScaleHeight();

    };
}

#endif //PROJECTC_SETTINGS_H
