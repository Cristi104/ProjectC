//
// Created by Cristi on 11/2/2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "raylib.h"
#include "../include/Settings.h"

namespace GmLib{

    unsigned int Settings::resolutionWidth = 960;
    unsigned int Settings::resolutionHeight = 540;
    float Settings::scaleWidth = 1;
    float Settings::scaleHeight = 1;
    bool Settings::fullscreen = false;
    bool Settings::borderless = false;

    void Settings::reset(){
        if(IsWindowReady()){
            setResolution(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
        } else {
            setResolution(960, 540);
        }
        fullscreen = false;
        borderless = false;
    }

    void Settings::load() {
        std::ifstream file("settings.txt");
        std::string buffer;
        std::vector<std::string> splits;

        while (file >> buffer){
            splits.push_back(buffer);
        }
//        std::string token;
//        unsigned int pos = 0;
//        while ((pos = buffer.find(' ') != std::string::npos)){
//            token = buffer.substr(0, pos);
//            splits.push_back(token);
//            buffer.erase(0, pos + 1);
//        }

        bool ok = true;
        for(unsigned int i = 0; i < splits.size(); i++){
            if(splits[i] == "Resolution:"){
                unsigned int x;
                unsigned int y;

                if(splits[i + 2] == "X"){
                    try{
                        x = std::stoi(splits[i + 1]);
                        y = std::stoi(splits[i + 3]);
                    } catch (std::invalid_argument &e){
                        ok = false;
                        break;
                    } catch (std::out_of_range &e){
                        ok = false;
                        break;
                    }
                } else {
                    ok = false;
                    break;
                }

                setResolution(x, y);
                i += 3;

            } else if(splits[i] == "Fullscreen:"){
                fullscreen = (splits[i + 1] == "0");
                i++;

            } else if(splits[i] == "Borderless:"){
                borderless = (splits[i + 1] == "0");
                i++;

            } else if(splits[i] == "") {

            }
        }
    }

    void Settings::setResolution(unsigned int x, unsigned int y) {
        resolutionWidth = x;
        resolutionHeight = y;
        scaleWidth = x / 960.0;
        scaleHeight = y / 540.0;
    }

    void Settings::print(std::ostream &out) {
        out << "Resolution: " << resolutionWidth << " X " << resolutionHeight << '\n'
            << "Fullscreen: " << fullscreen << '\n'
            << "Borderless: " << borderless << '\n';
    }

    void Settings::save() {
        std::ofstream file("settings.txt");
        print(file);
    }

    void Settings::log() {
        print(std::cout);
    }

    void Settings::apply() {
        SetWindowSize(resolutionWidth, resolutionHeight);

        unsigned int flags = FLAG_VSYNC_HINT |
                             FLAG_WINDOW_ALWAYS_RUN;
        if(fullscreen) flags |= FLAG_FULLSCREEN_MODE;
        if(borderless) flags |= FLAG_BORDERLESS_WINDOWED_MODE;

        SetWindowState(flags);
    }

    void Settings::setFullscreen(bool value) {
        fullscreen = value;
    }

    void Settings::setBorderless(bool value) {
        borderless = value;
    }

    unsigned int Settings::getResolutionWidth() {
        return resolutionWidth;
    }

    unsigned int Settings::getResolutionHeight() {
        return resolutionHeight;
    }

    float Settings::getScaleWidth() {
        return scaleWidth;
    }

    float Settings::getScaleHeight() {
        return scaleHeight;
    }


}
