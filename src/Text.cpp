//
// Created by Cristi on 11/3/2024.
//

#include <sstream>
#include "../include/UI.h"
#include "../include/Text.h"
#include "../include/Resources.h"

namespace GmLib {

    Text::Text() : position({0,0}),
                   font(Resources::getFont("8bitOperatorPlus-Regular.ttf")),
                   fontSize(8),
                   wrapLength(20){}

    void Text::draw() {
        SetTextLineSpacing(this->fontSize);
        DrawTextEx(*this->font, this->string.c_str(), {this->position.x, this->position.y}, this->fontSize, 1, BLACK);
    }

    void Text::handle() {
    }

    void Text::setText(const std::string &string) {
        unsigned int length, rowLength = 0;

        rowLength = 0;
        this->string = std::string();
        // if textWrapping is on;
        if (this->wrapLength != 0) {
            std::vector<std::string> words = Text::split(string);
            for(auto word : words){
                if(rowLength + word.length() + 1 > this->wrapLength && rowLength != 0){
                    this->string += '\n' + word + ' ';
                    rowLength = 0;
                } else {
                    this->string += word + ' ';
                }
                rowLength += word.length() + 1;
            }
        }
    }

    std::vector<std::string> Text::split(const std::string &string) {
        std::vector<std::string> words;
        std::istringstream stream(string);
        std::string word;
        while(std::getline(stream, word, ' ')){
            words.push_back(word);
        }
        return words;
    }
}