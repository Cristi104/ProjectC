//
// Created by Cristi on 12/9/2024.
//

#ifndef PROJECTC_TEXTBOX_H
#define PROJECTC_TEXTBOX_H

#include <functional>
#include <string>
#include "UIComponent.h"

namespace GmLib {
    class TextBox : public UIComponent {
    private:
        std::shared_ptr<Texture2D> texture;
        std::shared_ptr<Font> font;
        Rectangle position;
        std::function<void(std::string&)> onClick;
        bool wasPressed;
        std::string text;
    public:
        TextBox();
        void draw() override;
        void handle() override;
        ~TextBox() override = default;
    };
}

#endif //PROJECTC_TEXTBOX_H
