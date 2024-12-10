//
// Created by Cristi on 12/8/2024.
//

#ifndef PROJECTC_UICOMPONENT_H
#define PROJECTC_UICOMPONENT_H

#include "raylib.h"

namespace GmLib {
    class UIComponent {
    public:
        virtual void draw() = 0;
        virtual void handle() = 0;
        virtual ~UIComponent() = default;
    };
}

#endif //PROJECTC_UICOMPONENT_H
