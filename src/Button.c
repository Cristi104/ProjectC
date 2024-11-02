//
// Created by cristi on 30.10.2024.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/Graphics.h"

GmlibButton *GmlibButtonCreate(const char *name) {
    GmlibButton *button = calloc(1, sizeof(GmlibButton));
    char *helper;

    button->base.draw = (void (*)(void *)) GmlibButtonDraw;
    button->base.handleEvent = (void (*)(void *)) GmlibButtonHandle;
    button->base.destroy = (void (*)(void *)) GmlibButtonDestroy;

    if (name != NULL) {
        helper = malloc(strlen(name) + 20);

        strncpy(helper, name, strlen(name) - 4);
        strncpy(helper + strlen(name) - 4, "Pressed", 7);
        strncpy(helper + strlen(name) + 3, ".png\0", 5);

        button->texture = GmlibGetTexture(name);
        button->texturePressed = GmlibGetTexture(helper);
        free(helper);
    }
    if (button->texture == NULL) {
        button->texture = GmlibGetTexture("Button.png");
    }
    if (button->texturePressed == NULL) {
        button->texturePressed = GmlibGetTexture("ButtonPressed.png");
    }

    button->position.width = button->texture->width;
    button->position.height = button->texture->height;

    return button;
}

void GmlibButtonHandle(GmlibButton *button) {
    int x, y, minx, miny, maxx, maxy;
    bool buttonDown, buttonRelease;

    if (button == NULL)
        return;

    button->prv_pressed = false;
    buttonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    buttonRelease = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (buttonRelease || buttonDown) {
        minx = button->position.x * settings.scaleWidth;
        x = GetMouseX();
        maxx = button->position.width * settings.scaleWidth + minx;
        if (minx <= x && x <= maxx) {
            miny = button->position.y * settings.scaleWidth;
            y = GetMouseY();
            maxy = button->position.height * settings.scaleWidth + miny;
            if (miny <= y && y <= maxy) {
                if (button->onClick != NULL && buttonRelease) {
                    button->onClick(button->params);
                }
                button->prv_pressed = buttonDown;
            }
        }
    }
}

void GmlibButtonDraw(GmlibButton *button) {
    Rectangle src = {0, 0, 0, 0}, dest;
    Vector2 origin = {0, 0};

    src.width = button->texture->width;
    src.height = button->texture->height;
    dest = button->position;
    dest.x *= settings.scaleWidth;
    dest.y *= settings.scaleHeight;
    dest.width *= settings.scaleWidth;
    dest.height *= settings.scaleHeight;

    if (button->prv_pressed) {
        DrawTexturePro(*button->texturePressed, src, dest, origin, 0, WHITE);
    } else {
        DrawTexturePro(*button->texture, src, dest, origin, 0, WHITE);
    }
}

void GmlibButtonDestroy(GmlibButton *button) {
    free(button);
}
