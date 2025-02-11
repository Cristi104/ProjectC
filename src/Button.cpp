//
// Created by cristi on 30.10.2024.
//

#include "../include/Settings.h"
#include "../include/Button.h"
#include "../include/Resources.h"

namespace GmLib {

    Button::Button() : texture(Resources::getTexture("Button.png")),
                       texturePressed(Resources::getTexture("ButtonPressed.png")),
                       position({0,0,0,0}),
                       onClick(nullptr),
                       wasPressed(false){
        this->position.width = this->texture->width;
        this->position.height = this->texture->height;
    }

    void Button::draw() {
        Rectangle src = {0, 0, 0, 0};
        Vector2 origin = {0, 0};

        // find sreen coords
        src.width = this->texture->width;
        src.height = this->texture->height;

        // draw corresponding texture
        if (this->wasPressed) {
            DrawTexturePro(*this->texturePressed, src, this->position, origin, 0, WHITE);
        } else {
            DrawTexturePro(*this->texture, src, this->position, origin, 0, WHITE);
        }
    }

    void Button::handle() {
        float x, y, minx, miny, maxx, maxy;
        bool buttonDown, buttonRelease;

        this->wasPressed = false;

        // check if left click
        buttonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        buttonRelease = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        if (buttonRelease || buttonDown) {

            // check for x collision
            minx = this->position.x * GmLib::Settings::getScaleWidth();
            x = GetMouseX();
            maxx = this->position.width * GmLib::Settings::getScaleWidth();
            if (minx <= x && x <= maxx) {

                // check for y collision
                miny = this->position.y * GmLib::Settings::getScaleHeight();
                y = GetMouseY();
                maxy = this->position.height * GmLib::Settings::getScaleHeight();
                if (miny <= y && y <= maxy) {

                    // call onClick
                    if (this->onClick != nullptr && buttonRelease) {
                        this->onClick();
                    }
                    this->wasPressed = buttonDown;
                }
            }
        }

    }

}