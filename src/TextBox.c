//
// Created by Cristi on 11/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/UI.h"

GmlibTextBox *GmlibTextBoxCreate(const char *backgroundTexture, const char *font) {
    GmlibTextBox *textBox = calloc(1, sizeof(GmlibTextBox));

    // set base functions
    textBox->base.handleEvent = (void (*)(void *)) GmlibTextBoxHandle;
    textBox->base.draw = (void (*)(void *)) GmlibTextBoxDraw;
    textBox->base.destroy = (void (*)(void *)) GmlibTextBoxDestroy;

    // search for textures
    if (backgroundTexture != NULL) {
        textBox->background = GmlibGetTexture(backgroundTexture);
    }
    if (font != NULL) {
        textBox->font = GmlibGetFont(font);
    }

    // fallback to default textures
    if (textBox->background == NULL) {
        textBox->background = GmlibGetTexture("TextBox.png");
    }
    if (textBox->font == NULL) {
        textBox->font = GmlibGetFont("8bitOperatorPlus-Regular.ttf");
    }

    // set default size
    textBox->position.width = textBox->background->width;
    textBox->position.height = textBox->background->height;

    return textBox;
}

void GmlibTextBoxHandle(GmlibTextBox *textBox) {
    float x, y, minx, miny, maxx, maxy;
    int key, length;

    if (textBox == NULL) {
        return;
    }

    // check if left click
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        textBox->prv_pressed = false;

        // check for x collision
        minx = textBox->position.x * settings.scaleWidth;
        x = GetMouseX();
        maxx = textBox->position.width * settings.scaleWidth + minx;
        if (minx <= x && x <= maxx) {

            // check for y collision
            miny = textBox->position.y * settings.scaleHeight;
            y = GetMouseY();
            maxy = textBox->position.height * settings.scaleHeight + miny;
            if (miny <= y && y <= maxy) {
                textBox->prv_pressed = true;
                while (GetCharPressed());
            }
        }
    }

    // if selected
    if (textBox->prv_pressed) {

        // overflow check
        length = strlen(textBox->text);

        // text input
        while (key = GetCharPressed()) {
            if (length == 30 || key > 255) {
                continue;
            }
            textBox->text[length] = key;
            length++;
        }

        // text deletion
        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && length > 0) {
            length--;
            textBox->text[length] = '\0';
        }

        // call onClick
        if (textBox->onClick != NULL && IsKeyReleased(KEY_ENTER)) {
            textBox->onClick(textBox->params, textBox->text);
        }
    }
}

void GmlibTextBoxDraw(GmlibTextBox *textBox) {
    int maxChars;
    Rectangle src = {0, 0, 0, 0}, dest;
    Vector2 origin = {0, 0};

    // find sreen coords
    src.width = textBox->background->width;
    src.height = textBox->background->height;
    dest = textBox->position;
    dest.x *= settings.scaleWidth;
    dest.y *= settings.scaleHeight;
    dest.width *= settings.scaleWidth;
    dest.height *= settings.scaleHeight;

    // draw background
    DrawTexturePro(*textBox->background, src, dest, origin, 0, WHITE);

    origin.x = dest.x + settings.scaleWidth;
    origin.y = dest.y;

    // find number of shown chars
    maxChars = textBox->position.width / 8;
    if (maxChars > 30) {
        maxChars = 30;
    }

    // draw text
    if (strlen(textBox->text) >= maxChars) {
        DrawTextEx(*textBox->font, textBox->text + strlen(textBox->text) - maxChars, origin, 16 * settings.scaleWidth, 1,
                   WHITE);
    } else {
        DrawTextEx(*textBox->font, textBox->text, origin, 16 * settings.scaleWidth, 1, WHITE);
    }
}

void GmlibTextBoxDestroy(GmlibTextBox *textBox) {
    free(textBox);
}
