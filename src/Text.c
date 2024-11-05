//
// Created by Cristi on 11/3/2024.
//

#include <stdlib.h>
#include <string.h>
#include "../include/UI.h"

GmlibText *GmlibTextCreate(const char *string, Vector2 position, const char *font, unsigned int fontSize, unsigned int wrapLength) {
    GmlibText *text = calloc(1, sizeof(GmlibText));

    // set base functions
    text->base.handleEvent = NULL;
    text->base.draw = (void (*)(void *)) GmlibTextDraw;
    text->base.destroy = (void (*)(void *)) GmlibTextDestroy;

    text->position = position;
    text->fontSize = fontSize;
    text->wrapLength = wrapLength;
    text->string = NULL;

    // search for font
    if (font != NULL) {
        text->font = GmlibGetFont(font);
    }

    // fallback to default font
    if (font == NULL) {
        text->font = GmlibGetFont("8bitOperatorPlus-Regular.ttf");
    }

    // set string
    GmlibTextSetString(text, string);

    return text;
}

void GmlibTextDraw(GmlibText *text) {
    if (text == NULL) {
        return;
    }

    SetTextLineSpacing(text->fontSize * settings.scaleHeight);

    DrawTextEx(*text->font, text->string, (Vector2) {text->position.x * settings.scaleWidth, text->position.y * settings.scaleHeight}, text->fontSize * settings.scaleWidth, 1, BLACK);
}

void GmlibTextDestroy(GmlibText *text) {
    free(text->string);
    free(text);
}

void GmlibTextSetString(GmlibText *text, char *string) {
    char *stringCopy, *ptr;
    size_t length, rowLength, wordLength;

    if (text == NULL) {
        return;
    }
    if (string == NULL) {
        return;
    }

    // realocate a block of the right size;
    length = strlen(string);
    free(text->string);
    text->string = malloc(length + 1);
    memset(text->string, 0, length);
//    text->string[0] = '\0';
    rowLength = 0;

    // if textWrapping is on;
    if (text->wrapLength != 0) {

        // create a copy of string
        stringCopy = malloc(length + 2);
        strncpy(stringCopy, string, length);
        stringCopy[length] = '\0';

        // split into words
        ptr = strtok(stringCopy, " ");
        while (ptr != NULL) {

            // if the line would exceed the wrap length add a \n
            wordLength = strlen(ptr);
            if (rowLength != 0 && rowLength + wordLength + 1 >= text->wrapLength) {
                text->string[strlen(text->string) - 1] = '\n';
                rowLength = 0;
            }

            // concatenate the word
            strcpy(text->string + strlen(text->string), ptr);
            text->string[strlen(text->string)] = ' ';
            rowLength += wordLength + 1;

            ptr = strtok(NULL, " ");
        }
        free(stringCopy);
    } else {
        strncpy(text->string, string, length);
    }
    text->string[length] = '\0';
}
