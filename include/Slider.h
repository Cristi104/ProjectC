//
// Created by Cristi on 12/9/2024.
//

#ifndef PROJECTC_SLIDER_H
#define PROJECTC_SLIDER_H

#include <functional>
#include "UIComponent.h"

namespace GmLib {
    class Slider : public UIComponent {
    private:
        std::shared_ptr<Texture2D> sliderTexture;
        std::shared_ptr<Texture2D> pointTexture;
        Rectangle slidePosition;
        std::function<void(float)> onClick;
        float pointPosition;
        bool wasPressed;
        float percent;
    public:
        Slider();
        void draw() override;
        void handle() override;
        ~Slider() override = default;
    };
}

#endif //PROJECTC_SLIDER_H
