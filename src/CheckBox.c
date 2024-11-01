//
// Created by Cristi on 11/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include "../include/Graphics.h"

GmlibCheckBox *GmlibCreateCheckBox(const char *texture) {
    GmlibCheckBox *checkBox = calloc(1, sizeof(GmlibCheckBox));
    char *helper;

    checkBox->base.handleEvent = (void (*)(void *)) GmlibHandleCheckBox;
    checkBox->base.draw = (void (*)(void *)) GmlibDrawCheckBox;
    checkBox->base.destroy = (void (*)(void *)) GmlibDestroyCheckBox;

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

    return checkBox;
}

void GmlibHandleCheckBox(GmlibCheckBox *checkBox) {
    int x, y, minx, miny, maxx, maxy;

    if (checkBox == NULL)
        return;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        minx = checkBox->position.x;
        x = GetMouseX();
        maxx = checkBox->texture->width + minx;
        if (minx <= x && x <= maxx) {
            miny = checkBox->position.y;
            y = GetMouseY();
            maxy = checkBox->texture->height + miny;
            if (miny <= y && y <= maxy) {
                checkBox->checked = !checkBox->checked;
            }
        }
    }
}

void GmlibDrawCheckBox(GmlibCheckBox *checkBox) {
    if (checkBox->checked) {
        DrawTextureV(*checkBox->textureChecked, checkBox->position, WHITE);
    } else {
        DrawTextureV(*checkBox->texture, checkBox->position, WHITE);
    }
}

void GmlibDestroyCheckBox(GmlibCheckBox *checkBox) {
    free(checkBox);
}
