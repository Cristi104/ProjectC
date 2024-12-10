//
// Created by Cristi on 11/2/2024.
//

#include <stdio.h>
#include "../include/UI.h"

GmlibSettings settings;

void GmlibSettingsInit() {
    FILE *file = fopen("../settings.txt", "r");

    // if settings.txt is missing set default else read settings
    if (file == NULL) {
        settings.resolutionWidth = GetMonitorWidth(GetCurrentMonitor());
        settings.resolutionHeight = GetMonitorHeight(GetCurrentMonitor());
        settings.scaleWidth = settings.resolutionWidth / 960.0f;
        settings.scaleHeight = settings.resolutionHeight / 540.0f;
        settings.fullscreen = true;
        GmlibSettingsSave();
    } else {
        fread((char *) &settings, sizeof(GmlibSettings), 1, file);
        fclose(file);
    }

}

void GmlibSettingsSave() {
    FILE *file = fopen("../settings.txt", "w");
    fwrite((char *) &settings, sizeof(GmlibSettings), 1, file);
    fclose(file);
}

void GmlibSettingsApply() {
    SetWindowSize(settings.resolutionWidth, settings.resolutionHeight);
    if (IsWindowFullscreen() != settings.fullscreen) {
        ToggleFullscreen();
    }
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE) != settings.borderless) {
        ToggleBorderlessWindowed();
    }
}

void GmlibSettingsLog() {
    printf("Resolution: %uX%u\n", settings.resolutionWidth, settings.resolutionHeight);
    printf("Scale: %fX%f\n", settings.scaleWidth, settings.scaleHeight);
    printf("Fullscreen: %u\n", settings.fullscreen);
    printf("Borderless: %u\n", settings.borderless);
}
