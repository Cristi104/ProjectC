//
// Created by Cristi on 12/10/2024.
//

#ifndef PROJECTC_CHECKBOX_H
#define PROJECTC_CHECKBOX_H

#include "UIComponent.h"

namespace GmLib {
    class CheckBox : public UIComponent {
    private:
        Texture2D *texture;
        Texture2D *textureChecked;
        Rectangle position;
        bool checked;
    public:
        CheckBox();
        void draw() override;
        void handle() override;
        ~CheckBox() override = default;
    };
}

#endif //PROJECTC_CHECKBOX_H
