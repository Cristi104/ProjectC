//
// Created by cristi on 31.10.2024.
//

#include "../include/UI.h"
#include "../include/Slider.h"
#include "../include/Resources.h"

namespace GmLib {

    GmLib::Slider::Slider() : pointTexture(Resources::getTexture("Point.png")),
                              sliderTexture(Resources::getTexture("Slide.png")),
                              slidePosition({0,0,0,0}),
                              onClick(nullptr),
                              pointPosition(0),
                              wasPressed(false),
                              percent(0){
        this->slidePosition.width = this->sliderTexture->width;
        this->slidePosition.height = this->sliderTexture->height;
    }

    void Slider::draw() {
        Rectangle src = {0, 0, 0, 0};
        Vector2 origin = {0, 0};

        // find sreen coords
        src.width = this->sliderTexture->width;
        src.height = this->sliderTexture->height;

        // draw slide
        DrawTexturePro(*this->sliderTexture, src, this->slidePosition, origin, 0, WHITE);

        origin.x = this->slidePosition.x + this->pointPosition;
        origin.y = this->slidePosition.y;

        // draw point
        DrawTextureEx(*this->pointTexture, origin, 0, 1, WHITE);
    }

    void Slider::handle() {
        float x, y, minx, miny, maxx, maxy;
        bool buttonDown, buttonRelease;

        this->wasPressed = false;

        // check if left click
        buttonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        buttonRelease = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        if (buttonRelease || buttonDown) {

            // check for x collision
            minx = this->slidePosition.x * settings.scaleWidth;
            x = GetMouseX();
            maxx = this->slidePosition.width * settings.scaleWidth + minx;
            if (minx <= x && x <= maxx) {

                // check for y collision
                miny = this->slidePosition.y * settings.scaleHeight;
                y = GetMouseY();
                maxy = this->slidePosition.height * settings.scaleHeight + miny;
                if (miny <= y && y <= maxy) {

                    // find percentage
                    x -= minx + this->pointTexture->width * settings.scaleWidth / 2;
                    this->percent = x / ((this->slidePosition.width - this->pointTexture->width) * settings.scaleWidth);
                    if (this->percent < 0) {
                        this->percent = 0;
                    }
                    if (this->percent > 1) {
                        this->percent = 1;
                    }

                    // update point position
                    this->pointPosition = this->percent * (this->slidePosition.width - this->pointTexture->width);

                    // call onClick
                    if (this->onClick != NULL && buttonRelease) {
                        this->onClick(this->percent);
                    }
                    this->wasPressed = buttonDown;
                }
            }
        }
    }
}