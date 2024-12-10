//
// Created by Cristi on 11/1/2024.
//

#include "../include/UI.h"
#include "../include/Panel.h"
#include "../include/Resources.h"

namespace GmLib {

    Panel::Panel() : background(Resources::getTexture("UIBackground.png")),
                     border(Resources::getTexture("UIBackgroundBorder.png")),
                     position({0,0,64,64}),
                     visible(true){}

    void Panel::draw() {
        if(!this->visible)
            return;
        Rectangle src = {0, 0, 16, 16}, helper;
        Vector2 origin = {0, 0};

        // find sreen coords
        helper.x = this->position.x + 4;
        helper.y = this->position.y + 4;
        helper.width = this->position.width - 8;
        helper.height = this->position.height - 8;

        // Draw background
        DrawTexturePro(*this->border, src, this->position, origin, 0, WHITE);
        DrawTexturePro(*this->background, src, helper, origin, 0, WHITE);

        for (auto component : this->components){
            component->draw();
        }
    }

    void Panel::handle() {
        if(!this->visible)
            return;
        for (auto component : this->components){
            component->handle();
        }
    }

    Panel::~Panel() {
        for (auto component : this->components){
            delete component;
        }
    }
}