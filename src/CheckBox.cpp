//
// Created by Cristi on 11/1/2024.
//

#include "../include/Settings.h"
#include "../include/CheckBox.h"
#include "../include/Resources.h"

namespace GmLib {
    CheckBox::CheckBox() : texture(Resources::getTexture("CheckBox.png")),
                           textureChecked(Resources::getTexture("CheckBoxChecked.png")),
                           position({0,0,0,0}),
                           checked(false){
        this->position.width = this->texture->width;
        this->position.height = this->texture->height;
    }

    void CheckBox::draw() {
        Rectangle src = {0, 0, 0, 0};
        Vector2 origin = {0, 0};

        // find sreen coords
        src.width = this->texture->width;
        src.height = this->texture->height;


        // draw corresponding texture
        if (this->checked) {
            DrawTexturePro(*this->textureChecked, src, this->position, origin, 0, WHITE);
        } else {
            DrawTexturePro(*this->texture, src, this->position, origin, 0, WHITE);
        }

    }

    void CheckBox::handle() {
        float x, y, minx, miny, maxx, maxy;

        // check if left click
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

            // check for x collision
            minx = this->position.x * GmLib::Settings::getScaleWidth();
            x = GetMouseX();
            maxx = this->position.width * GmLib::Settings::getScaleWidth() + minx;
            if (minx <= x && x <= maxx) {

                // check for y collision
                miny = this->position.y * GmLib::Settings::getScaleHeight();
                y = GetMouseY();
                maxy = this->position.height * GmLib::Settings::getScaleHeight() + miny;
                if (miny <= y && y <= maxy) {
                    this->checked = !this->checked;
                }
            }
        }

    }
}