//
// Created by Cristi on 11/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/Graphics.h"

GmlibTextBox *GmlibTextBoxCreate(const char *backgroundTexture, const char *font) {
    GmlibTextBox *textBox = calloc(1, sizeof(GmlibTextBox));

    textBox->base.handleEvent = (void (*)(void *)) GmlibTextBoxHandle;
    textBox->base.draw = (void (*)(void *)) GmlibTextBoxDraw;
    textBox->base.destroy = (void (*)(void *)) GmlibTextBoxDestroy;

    if (backgroundTexture != NULL) {
        textBox->background = GmlibGetTexture(backgroundTexture);
    }
    if (font != NULL) {
        textBox->font = GmlibGetFont(font);
    }
    if (textBox->background == NULL) {
        textBox->background = GmlibGetTexture("TextBox.png");
    }
    if (textBox->font == NULL) {
        textBox->font = GmlibGetFont("8bitOperatorPlus-Regular.ttf");
    }

    return textBox;
}

void GmlibTextBoxHandle(GmlibTextBox *textBox) {
    int x, y, minx, miny, maxx, maxy, length;
    int key;

    if (textBox == NULL) {
        return;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        textBox->prv_pressed = false;
        minx = textBox->position.x;
        x = GetMouseX();
        maxx = textBox->background->width + minx;
        if (minx <= x && x <= maxx) {
            miny = textBox->position.y;
            y = GetMouseY();
            maxy = textBox->background->height + miny;
            if (miny <= y && y <= maxy) {
                textBox->prv_pressed = true;
                while (GetCharPressed());
            }
        }
    }
    if (textBox->prv_pressed) {
        length = strlen(textBox->text);
        while (key = GetCharPressed()) {
            if (length == 30 || key > 255) {
                continue;
            }
            textBox->text[length] = key;
            length++;
        }
        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && length > 0) {
            length--;
            textBox->text[length] = '\0';
        }
    }
}

void GmlibTextBoxDraw(GmlibTextBox *textBox) {
    DrawTextureV(*textBox->background, textBox->position, WHITE);
    if (strlen(textBox->text) >= 8) {
        DrawTextEx(*textBox->font, textBox->text + strlen(textBox->text) - 8, textBox->position, 16, 1, WHITE);
    } else {
        DrawTextEx(*textBox->font, textBox->text, textBox->position, 16, 1, WHITE);
    }
}

void GmlibTextBoxDestroy(GmlibTextBox *textBox) {
    free(textBox);
}
