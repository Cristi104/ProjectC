//
// Created by Cristi on 11/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include "../include/Graphics.h"

GmlibCheckBox *GmlibCheckBoxCreate(const char *texture) {
    GmlibCheckBox *checkBox = calloc(1, sizeof(GmlibCheckBox));
    char *helper;

    checkBox->base.handleEvent = (void (*)(void *)) GmlibCheckBoxHandle;
    checkBox->base.draw = (void (*)(void *)) GmlibCheckBoxDraw;
    checkBox->base.destroy = (void (*)(void *)) GmlibCheckBoxDestroy;

    if (texture != NULL) {
        helper = malloc(strlen(texture) + 20);

        strncpy(helper, texture, strlen(texture) - 4);
        strncpy(helper + strlen(texture) - 4, "Checked", 7);
        strncpy(helper + strlen(texture) + 4, ".png\0", 5);

        checkBox->texture = GmlibGetTexture(texture);
        checkBox->textureChecked = GmlibGetTexture(helper);
        free(helper);
    }
    if (checkBox->texture == NULL) {
        checkBox->texture = GmlibGetTexture("CheckBox.png");
    }
    if (checkBox->textureChecked == NULL) {
        checkBox->textureChecked = GmlibGetTexture("CheckBoxChecked.png");
    }

    checkBox->position.width = checkBox->texture->width;
    checkBox->position.height = checkBox->texture->height;

    return checkBox;
}

void GmlibCheckBoxHandle(GmlibCheckBox *checkBox) {
    int x, y, minx, miny, maxx, maxy;

    if (checkBox == NULL)
        return;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        minx = checkBox->position.x * settings.scaleWidth;
        x = GetMouseX();
        maxx = checkBox->position.width * settings.scaleWidth + minx;
        if (minx <= x && x <= maxx) {
            miny = checkBox->position.y * settings.scaleHeight;
            y = GetMouseY();
            maxy = checkBox->position.height * settings.scaleHeight + miny;
            if (miny <= y && y <= maxy) {
                checkBox->checked = !checkBox->checked;
            }
        }
    }
}

void GmlibCheckBoxDraw(GmlibCheckBox *checkBox) {
    Rectangle src = {0, 0, 0, 0}, dest;
    Vector2 origin = {0, 0};

    src.width = checkBox->texture->width;
    src.height = checkBox->texture->height;
    dest = checkBox->position;
    dest.x *= settings.scaleWidth;
    dest.y *= settings.scaleHeight;
    dest.width *= settings.scaleWidth;
    dest.height *= settings.scaleHeight;

    if (checkBox->checked) {
        DrawTexturePro(*checkBox->textureChecked, src, dest, origin, 0, WHITE);
    } else {
        DrawTexturePro(*checkBox->texture, src, dest, origin, 0, WHITE);
    }
}

void GmlibCheckBoxDestroy(GmlibCheckBox *checkBox) {
    free(checkBox);
}
