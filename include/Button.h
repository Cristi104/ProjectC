//
// Created by Cristi on 12/8/2024.
//

#ifndef PROJECTC_BUTTON_H
#define PROJECTC_BUTTON_H

#include <functional>
#include "UIComponent.h"
#include "Game_exports.h"

namespace GmLib {
    class GAME_EXPORTS Button : public UIComponent {
    private:
        Texture2D *texture;
        Texture2D *texturePressed;
        Rectangle position;
        std::function<void()> onClick;
        bool wasPressed;
    public:
        Button();
        void draw() override;
        void handle() override;
        ~Button() override = default;
    };
}

#endif //PROJECTC_BUTTON_H
