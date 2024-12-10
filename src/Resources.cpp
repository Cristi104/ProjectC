//
// Created by cristi on 30.10.2024.
//

#include <stdexcept>
#include "../include/Resources.h"

namespace GmLib{
    std::map<std::string, Texture2D*> Resources::textures;
    std::map<std::string, Font*> Resources::fonts;

    void Resources::Load(const std::string &directory) {
        FilePathList list = LoadDirectoryFiles(directory.c_str());
        unsigned int nameSize;
        char *file, *fileName;
        Image image;
        Texture2D texture;
        Font font;

        // iterate through files
        for (int i = 0; i < list.count; i++) {
            file = list.paths[i];
            fileName = file + strlen(directory.c_str()) + 1;
            nameSize = strlen(fileName);

            // check if file or dir
            if (strchr(fileName, '.') != nullptr) {

                // if .png
                if (strstr(fileName + nameSize - 4, ".png") != nullptr) {

                    // check if exists
                    if (textures.find(fileName) == textures.end()){
                        image = LoadImage(file);
                        texture = LoadTextureFromImage(image);
                        textures.insert({fileName, new Texture2D(texture)});
                        UnloadImage(image);
                    }
                }

                // if .ttf
                if (strstr(fileName + nameSize - 4, ".ttf") != nullptr) {

                    // check if exists
                    if (fonts.find(fileName) == fonts.end()){
                        font = LoadFont(file);
                        fonts.insert({fileName, new Font(font)});
                    }
                }
            } else {
                // recursive loading
                Load(file);
            }
        }
        UnloadDirectoryFiles(list);
    }

    void Resources::Unload() {
        for(const auto& pair : textures){
            UnloadTexture(*pair.second);
            delete pair.second;
        }
        for(const auto& pair : fonts){
            UnloadFont(*pair.second);
            delete pair.second;
        }
    }

    Texture2D *Resources::getTexture(const std::string &fileName) {
        try{
            return textures.at(fileName);
        } catch (std::out_of_range &ex){
            return nullptr;
        }
    }

    Font *Resources::getFont(const std::string &fileName) {
        try{
            return fonts.at(fileName);
        } catch (std::out_of_range &ex){
            return nullptr;
        }
    }
}
