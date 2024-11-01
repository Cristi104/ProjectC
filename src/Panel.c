//
// Created by Cristi on 11/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include "../include/Graphics.h"
#include "../include/DataStructs.h"

GmlibPanel *GmlibPanelCreate(const char *background) {
    GmlibPanel *panel = calloc(1, sizeof(GmlibPanel));
    char *helper;

    panel->base.draw = (void (*)(void *)) GmlibPanelDraw;
    panel->base.handleEvent = (void (*)(void *)) GmlibPanelHandle;
    panel->base.destroy = (void (*)(void *)) GmlibPanelDestory;

    panel->location.width = 400;
    panel->location.height = 300;

    panel->visible = true;
    panel->components = GmlibArrayCreate(5, false);

    if (background != NULL) {
        helper = malloc(strlen(background) + 20);

        strncpy(helper, background, strlen(background) - 4);
        strncpy(helper + strlen(background) - 4, "Border", 7);
        strncpy(helper + strlen(background) + 2, ".png\0", 5);

        panel->background = GmlibGetTexture(background);
        panel->border = GmlibGetTexture(helper);
        free(helper);
    }
    if (panel->background == NULL) {
        panel->background = GmlibGetTexture("UIBackground.png");
    }
    if (panel->border == NULL) {
        panel->border = GmlibGetTexture("UIBackgroundBorder.png");
    }

    return panel;
}

void GmlibPanelDraw(GmlibPanel *panel) {
    GmlibArray *array;
    GmlibUIComponent *component;
    Rectangle src = {0, 0, 16, 16}, dest, helper;
    Vector2 origin = {0, 0};

    if (panel == NULL) {
        return;
    }
    if (!panel->visible) {
        return;
    }

    dest = panel->location;
    helper.x = dest.x + 4;
    helper.y = dest.y + 4;
    helper.width = dest.width - 8;
    helper.height = dest.height - 8;

    DrawTexturePro(*panel->border, src, dest, origin, 0, WHITE);
    DrawTexturePro(*panel->background, src, helper, origin, 0, WHITE);

    array = panel->components;
    for (int i = 0; i < array->size; i++) {
        component = array->arr[i];
        component->draw(component);
    }
}

void GmlibPanelHandle(GmlibPanel *panel) {
    GmlibArray *array;
    GmlibUIComponent *component;

    if (panel == NULL) {
        return;
    }
    if (!panel->visible) {
        return;
    }

    array = panel->components;
    for (int i = 0; i < array->size; i++) {
        component = array->arr[i];
        component->handleEvent(component);
    }
}

void GmlibPanelDestory(GmlibPanel *panel) {
    GmlibArray *array;
    GmlibUIComponent *component;

    if (panel == NULL) {
        return;
    }

    array = panel->components;
    for (int i = 0; i < array->size; i++) {
        component = array->arr[i];
        component->destroy(component);
    }
    GmlibArrayDestroy(array);
    free(panel);
}
