//
// Created by cristi on 31.10.2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "../include/Graphics.h"

GmlibSlider *GmlibSliderCreate(const char *sliderTexture, const char *pointTexture) {
    GmlibSlider *slider = calloc(1, sizeof(GmlibSlider));

    slider->base.draw = (void (*)(void *)) GmlibSliderDraw;
    slider->base.handleEvent = (void (*)(void *)) GmlibSliderHandle;
    slider->base.destroy = (void (*)(void *)) GmlibSliderDestroy;

    if (sliderTexture != NULL) {
        slider->sliderTexture = GmlibGetTexture(sliderTexture);
    }
    if (pointTexture != NULL) {
        slider->pointTexture = GmlibGetTexture(pointTexture);
    }
    if (slider->sliderTexture == NULL) {
        slider->sliderTexture = GmlibGetTexture("Slide.png");
    }
    if (slider->pointTexture == NULL) {
        slider->pointTexture = GmlibGetTexture("Point.png");
    }

    slider->slidePosition.width = slider->sliderTexture->width;
    slider->slidePosition.height = slider->sliderTexture->height;
    return slider;
}

void GmlibSliderHandle(GmlibSlider *slider) {
    float x, y, minx, miny, maxx, maxy;
    bool buttonDown, buttonRelease;

    if (slider == NULL)
        return;

    slider->prv_pressed = false;
    buttonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    buttonRelease = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (buttonRelease || buttonDown) {
        minx = slider->slidePosition.x * settings.scaleWidth;
        x = GetMouseX();
        maxx = slider->slidePosition.width * settings.scaleWidth + minx;
        if (minx <= x && x <= maxx) {
            miny = slider->slidePosition.y * settings.scaleHeight;
            y = GetMouseY();
            maxy = slider->slidePosition.height * settings.scaleHeight + miny;
            if (miny <= y && y <= maxy) {
                x -= minx + slider->pointTexture->width * settings.scaleWidth / 2;
                slider->percent = x / ((slider->slidePosition.width - slider->pointTexture->width) * settings.scaleWidth);
                if (slider->percent < 0) {
                    slider->percent = 0;
                }
                if (slider->percent > 1) {
                    slider->percent = 1;
                }
                slider->pointPosition = slider->percent * (slider->slidePosition.width - slider->pointTexture->width) * settings.scaleWidth;
                if (slider->onClick != NULL && buttonRelease) {
                    slider->onClick(slider->params, slider->percent);
                }
                slider->prv_pressed = buttonDown;
            }
        }
    }
}

void GmlibSliderDraw(GmlibSlider *slider) {
    Rectangle src = {0, 0, 0, 0}, dest;
    Vector2 origin = {0, 0};

    src.width = slider->sliderTexture->width;
    src.height = slider->sliderTexture->height;
    dest = slider->slidePosition;
    dest.x *= settings.scaleWidth;
    dest.y *= settings.scaleHeight;
    dest.width *= settings.scaleWidth;
    dest.height *= settings.scaleHeight;

    DrawTexturePro(*slider->sliderTexture, src, dest, origin, 0, WHITE);

    origin.x = dest.x + slider->pointPosition;
    origin.y = dest.y;
    DrawTextureEx(*slider->pointTexture, origin, 0, settings.scaleWidth, WHITE);
}

void GmlibSliderDestroy(GmlibSlider *slider) {
    free(slider);
}
