//
// Created by cristi on 31.10.2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "../include/Graphics.h"

GmlibSlider *GmlibCreateSlider(const char *sliderTexture, const char *pointTexture) {
    GmlibSlider *slider = calloc(1, sizeof(GmlibSlider));

    slider->base.draw = (void (*)(void *)) GmlibDrawSlider;
    slider->base.handleEvent = (void (*)(void *)) GmlibHandleSlider;
    slider->base.destroy = (void (*)(void *)) GmlibDestroySlider;

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

    return slider;
}

void GmlibHandleSlider(GmlibSlider *slider) {
    int x, y, minx, miny, maxx, maxy;
    bool buttonDown, buttonRelease;

    if (slider == NULL)
        return;

    slider->prv_pressed = false;
    buttonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    buttonRelease = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (buttonRelease || buttonDown) {
        minx = slider->slidePosition.x;
        x = GetMouseX();
        maxx = slider->sliderTexture->width + minx;
        if (minx <= x && x <= maxx) {
            miny = slider->slidePosition.y;
            y = GetMouseY();
            maxy = slider->sliderTexture->height + miny;
            if (miny <= y && y <= maxy) {
                x -= minx;
                slider->percent = (float) x / (float) slider->sliderTexture->width;
                slider->pointPosition.x =
                        minx + slider->percent * (slider->sliderTexture->width - slider->pointTexture->width);
                if (slider->onClick != NULL && buttonRelease) {
                    slider->onClick(slider->params, slider->percent);
                }
                printf("%f\n", slider->percent);
                slider->prv_pressed = buttonDown;
            }
        }
    }
}

void GmlibDrawSlider(GmlibSlider *slider) {
    Color tint = {255, 255, 255, 255};
    DrawTextureV(*slider->sliderTexture, slider->slidePosition, tint);
    DrawTextureV(*slider->pointTexture, slider->pointPosition, tint);
}

void GmlibDestroySlider(GmlibSlider *slider) {
    free(slider);
}
