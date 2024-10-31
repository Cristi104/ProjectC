//
// Created by cristi on 30.10.2024.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/Graphics.h"

Button *CreateButton(const char *name) {
    Button *button = calloc(1, sizeof(Button));
    char *helper;

    button->vtable.draw = (void (*)(void *)) DrawButton;
    button->vtable.handleEvent = (void (*)(void *)) HandleButton;
    button->vtable.destroy = (void (*)(void *)) DestroyButton;

    if (name != NULL) {
        helper = alloca(strlen(name) + 20);

        strncpy(helper, name, strlen(name) - 4);
        strncpy(helper + strlen(name) - 4, "Pressed", 7);
        strncpy(helper + strlen(name) + 3, ".png\0", 5);

        button->texture = GetTexture(name);
        button->texturePressed = GetTexture(helper);
    }
    if (button->texture == NULL) {
        button->texture = GetTexture("Button.png");
    }
    if (button->texturePressed == NULL) {
        button->texturePressed = GetTexture("ButtonPressed.png");
    }
    return button;
}

void HandleButton(Button *button) {
    int x, y, minx, miny, maxx, maxy;
    bool buttonDown, buttonRelease;

    if (button == NULL)
        return;

    button->prv_pressed = false;
    buttonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    buttonRelease = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (buttonRelease || buttonDown) {
        minx = button->position.x;
        x = GetMouseX();
        maxx = button->texture->width + minx;
        if (minx <= x && x <= maxx) {
            miny = button->position.y;
            y = GetMouseY();
            maxy = button->texture->height + miny;
            if (miny <= y && y <= maxy) {
                if (button->onClick != NULL && buttonRelease) {
                    button->onClick(button->params);
                }
                button->prv_pressed = buttonDown;
            }
        }
    }
}

void DrawButton(Button *button) {
    Color tint = {255, 255, 255, 255};
    if (button->prv_pressed) {
        DrawTextureV(*button->texturePressed, button->position, tint);
    } else {
        DrawTextureV(*button->texture, button->position, tint);
    }
}

void DestroyButton(Button *button) {
    free(button);
}
