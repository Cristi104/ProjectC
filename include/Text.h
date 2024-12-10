//
// Created by Cristi on 12/10/2024.
//

#ifndef PROJECTC_TEXT_H
#define PROJECTC_TEXT_H

#include <string>
#include <vector>
#include "UIComponent.h"

namespace GmLib {
    class Text : public UIComponent {
    private:
        Vector2 position;
        Font *font;
        std::string string;
        unsigned int fontSize;
        unsigned int wrapLength;
        static std::vector<std::string> split(const std::string &string);
    public:
        Text();
        void draw() override;
        void handle() override;
        void setText(const std::string &string);
        ~Text() override = default;
    };
}

#endif //PROJECTC_TEXT_H
