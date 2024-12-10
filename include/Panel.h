//
// Created by Cristi on 12/10/2024.
//

#ifndef PROJECTC_PANEL_H
#define PROJECTC_PANEL_H

#include <vector>
#include "UIComponent.h"

namespace GmLib {
    class Panel : public UIComponent {
    private:
        Texture2D *background;
        Texture2D *border;
        Rectangle position;
        std::vector<UIComponent*> components;
        bool visible;
    public:
        Panel();
        void draw() override;
        void handle() override;
        ~Panel() override;
    };
}

#endif //PROJECTC_PANEL_H
