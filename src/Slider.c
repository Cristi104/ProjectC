//
// Created by cristi on 31.10.2024.
//
#include <stdlib.h>
#include <stdio.h>
#include "../include/Graphics.h"

Slider *CreateSlider(const char *sliderTexture, const char *pointTexture) {
    Slider *slider = calloc(1, sizeof(Slider));

    slider->vtable.draw = (void (*)(void *)) DrawSlider;
    slider->vtable.handleEvent = (void (*)(void *)) HandleSlider;
    slider->vtable.destroy = (void (*)(void *)) DestroySlider;

    if (sliderTexture != NULL) {
        slider->sliderTexture = GetTexture(sliderTexture);
    }
    if (pointTexture != NULL) {
        slider->pointTexture = GetTexture(pointTexture);
    }
    if (slider->sliderTexture == NULL) {
        slider->sliderTexture = GetTexture("Slide.png");
    }
    if (slider->pointTexture == NULL) {
        slider->pointTexture = GetTexture("Point.png");
    }

    return slider;
}

void HandleSlider(Slider *slider) {
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
                    slider->onClick(slider->percent);
                }
                printf("%f\n", slider->percent);
                slider->prv_pressed = buttonDown;
            }
        }
    }
}

void DrawSlider(Slider *slider) {
    Color tint = {255, 255, 255, 255};
    DrawTextureV(*slider->sliderTexture, slider->slidePosition, tint);
    DrawTextureV(*slider->pointTexture, slider->pointPosition, tint);
}

void DestroySlider(Slider *slider) {
    free(slider);
}
