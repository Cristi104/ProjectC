//
// Created by cristi on 30.10.2024.
//

#include <stdexcept>
#include "../include/Resources.h"

namespace GmLib{
    std::map<std::string, std::shared_ptr<Texture2D>> Resources::textures;
    std::map<std::string, std::shared_ptr<Font>> Resources::fonts;

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
                        textures.insert({fileName,std::shared_ptr<Texture2D>(
                                new Texture2D(texture),
                                [](Texture2D *ptr){UnloadTexture(*ptr);})});
                        UnloadImage(image);
                    }
                }

                // if .ttf
                if (strstr(fileName + nameSize - 4, ".ttf") != nullptr) {

                    // check if exists
                    if (fonts.find(fileName) == fonts.end()){
                        font = LoadFont(file);
                        fonts.insert({fileName, std::shared_ptr<Font>(
                                new Font(font),
                                [](Font *ptr){UnloadFont(*ptr);})});
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
        textures.clear();
        fonts.clear();
    }

    std::weak_ptr<Texture2D> Resources::getTexture(const std::string &fileName) {
        try{
            return textures.at(fileName);
        } catch (std::out_of_range &ex){
            try{
                return textures.at("MissingTexture.png");
            } catch (std::out_of_range &ex){
                Image image = GenImageChecked(64,64,4,4,
                                                {0,0,0,255},{255,0,255,255});
                Texture2D texture = LoadTextureFromImage(image);
                textures.insert({"MissingTexture.png",std::shared_ptr<Texture2D>(
                        new Texture2D(texture),
                        [](Texture2D *ptr){UnloadTexture(*ptr);})});
                UnloadImage(image);
                return textures.at("MissingTexture.png");
            }
        }
    }

    std::weak_ptr<Font> Resources::getFont(const std::string &fileName) {
//        try{
//            return fonts.at(fileName);
//        } catch (std::out_of_range &ex){
//            return {};
//        }
        return fonts.at(fileName);
    }
}
