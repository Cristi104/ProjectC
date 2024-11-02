//
// Created by Cristi on 11/2/2024.
//

#include <stdio.h>
#include "../include/Graphics.h"

GmlibVideoSettings settings;

void GmlibVideoSettingsInit() {
    FILE *file = fopen("../settings.txt", "r");
    if (file == NULL) {
        settings.resolutionWidth = GetMonitorWidth(GetCurrentMonitor());
        settings.resolutionHeight = GetMonitorHeight(GetCurrentMonitor());
        settings.scaleWidth = settings.resolutionWidth / 960.0f;
        settings.scaleHeight = settings.resolutionHeight / 540.0f;
        settings.fullscreen = true;
        GmlibVideoSettingsSave();
    } else {
        fread((char *) &settings, sizeof(GmlibVideoSettings), 1, file);
        fclose(file);
    }

}

void GmlibVideoSettingsSave() {
    FILE *file = fopen("../settings.txt", "w");
    fwrite((char *) &settings, sizeof(GmlibVideoSettings), 1, file);
    fclose(file);
}

void GmlibVideoSettingsApply() {
    SetWindowSize(settings.resolutionWidth, settings.resolutionHeight);
    if (IsWindowFullscreen() != settings.fullscreen) {
        ToggleFullscreen();
    }
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE) != settings.borderless) {
        ToggleBorderlessWindowed();
    }
}

void GmlibVideoSettingsLog() {
    printf("Resolution: %uX%u\n", settings.resolutionWidth, settings.resolutionHeight);
    printf("Scale: %fX%f\n", settings.scaleWidth, settings.scaleHeight);
    printf("Fullscreen: %u\n", settings.fullscreen);
    printf("Borderless: %u\n", settings.borderless);
}
