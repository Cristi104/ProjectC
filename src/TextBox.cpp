//
// Created by Cristi on 11/1/2024.
//

#include "../include/UI.h"
#include "../include/TextBox.h"
#include "../include/Resources.h"

namespace GmLib {
    TextBox::TextBox() : texture(Resources::getTexture("TextBox.png")),
                         font(Resources::getFont("8bitOperatorPlus-Regular.ttf")),
                         position({0,0,0,0}),
                         onClick(nullptr),
                         wasPressed(false){
        this->position.width = this->texture->width;
        this->position.height = this->texture->height;
    }

    void TextBox::draw() {
        unsigned int maxChars;
        Rectangle src = {0, 0, 0, 0};
        Vector2 origin = {0, 0};

        // find sreen coords
        src.width = this->texture->width;
        src.height = this->texture->height;

        // draw texture
        DrawTexturePro(*this->texture, src, this->position, origin, 0, WHITE);

        origin.x = this->position.x + 1;
        origin.y = this->position.y;

        // find number of shown chars
        maxChars = this->position.width / 8;

        // draw text
        if (this->text.length() >= maxChars) {
            DrawTextEx(*this->font, this->text.c_str() + this->text.length() - maxChars, origin, 16, 1,
                       WHITE);
        } else {
            DrawTextEx(*this->font, this->text.c_str(), origin, 16, 1, WHITE);
        }
    }

    void TextBox::handle() {
        float x, y, minx, miny, maxx, maxy;
        int key, length;

        // check if left click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            this->wasPressed = false;

            // check for x collision
            minx = this->position.x * settings.scaleWidth;
            x = GetMouseX();
            maxx = this->position.width * settings.scaleWidth + minx;
            if (minx <= x && x <= maxx) {

                // check for y collision
                miny = this->position.y * settings.scaleHeight;
                y = GetMouseY();
                maxy = this->position.height * settings.scaleHeight + miny;
                if (miny <= y && y <= maxy) {
                    this->wasPressed = true;
                    while (GetCharPressed());
                }
            }
        }

        // if selected
        if (this->wasPressed) {

            // text input
            key = GetCharPressed();
            while (key != 0) {
                if (key > 255) {
                    continue;
                }
                this->text.push_back(key);
                key = GetCharPressed();
            }

            // text deletion
            if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && this->text.length() > 0) {
                this->text.erase(this->text.length() - 1);
            }

            // call onClick
            if (this->onClick != nullptr && IsKeyReleased(KEY_ENTER)) {
                this->onClick(this->text);
            }
        }
    }
}

