//
// Created by Cristi on 11/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include "../include/UI.h"
#include "../include/DataStructs.h"

GmlibPanel *GmlibPanelCreate(const char *background, Rectangle position) {
    GmlibPanel *panel = calloc(1, sizeof(GmlibPanel));
    char *helper;

    // set base functions
    panel->base.draw = (void (*)(void *)) GmlibPanelDraw;
    panel->base.handleEvent = (void (*)(void *)) GmlibPanelHandle;
    panel->base.destroy = (void (*)(void *)) GmlibPanelDestory;

    panel->position = position;
    panel->visible = true;
    panel->components = GmlibArrayCreate(5, false);

    // search for textures
    if (background != NULL) {
        helper = malloc(strlen(background) + 20);

        strncpy(helper, background, strlen(background) - 4);
        strncpy(helper + strlen(background) - 4, "Border", 7);
        strncpy(helper + strlen(background) + 2, ".png\0", 5);

        panel->background = GmlibGetTexture(background);
        panel->border = GmlibGetTexture(helper);
        free(helper);
    }

    // fallback to default textures
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
    Rectangle src = {0, 0, 16, 16}, helper;
    Vector2 origin = {0, 0};

    if (panel == NULL) {
        return;
    }
    if (!panel->visible) {
        return;
    }

    // find sreen coords
    helper.x = panel->position.x + 4;
    helper.y = panel->position.y + 4;
    helper.width = panel->position.width - 8;
    helper.height = panel->position.height - 8;

    // Draw background
    DrawTexturePro(*panel->border, src, panel->position, origin, 0, WHITE);
    DrawTexturePro(*panel->background, src, helper, origin, 0, WHITE);

    // draw components
    array = panel->components;
    for (int i = 0; i < array->size; i++) {
        component = array->arr[i];
        if (component->draw != NULL) {
            component->draw(component);
        }
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

    // call handle on components
    array = panel->components;
    for (int i = 0; i < array->size; i++) {
        component = array->arr[i];
        if (component->handleEvent != NULL) {
            component->handleEvent(component);
        }
    }
}

void GmlibPanelDestory(GmlibPanel *panel) {
    GmlibArray *array;
    GmlibUIComponent *component;

    if (panel == NULL) {
        return;
    }

    // free components
    array = panel->components;
    for (int i = 0; i < array->size; i++) {
        component = array->arr[i];
        component->destroy(component);
    }

    // free panel
    GmlibArrayDestroy(array);
    free(panel);
}
