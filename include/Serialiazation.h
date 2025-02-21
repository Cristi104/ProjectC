//
// Created by Cristi on 2/21/2025.
//

#ifndef PROJECTC_SERIALIAZATION_H
#define PROJECTC_SERIALIAZATION_H

#include <iostream>
#include "Game_exports.h"

namespace GmLib {

    class GAME_EXPORTS Serializable{
    public:
        virtual void serialize(std::ostream &out) const = 0;
        virtual void deserialize(std::istream &in) = 0;
    };

    template<typename t>
    void Serialize(std::ostream &out, const std::string &name, const t &obj){
        out << name << ": {\n";
        obj.serialize(out);
        out << "}\n";
    }

    template<>
    void GAME_EXPORTS Serialize<std::string>(std::ostream &out, const std::string &name, const std::string &obj);
    template<>
    void GAME_EXPORTS Serialize<int>(std::ostream &out, const std::string &name, const int &obj);
    template<>
    void GAME_EXPORTS Serialize<unsigned int >(std::ostream &out, const std::string &name, const unsigned int &obj);
    template<>
    void GAME_EXPORTS Serialize<float>(std::ostream &out, const std::string &name, const float &obj);


    template<typename t>
    void Deserialize(std::istream &in, const std::string &name, t &obj){
        std::string buffer;
        std::string keyString = name + ": {";
        std::string::size_type begin;

        std::getline(in, buffer);
        if(buffer == keyString){
            obj.deserialize(in);
        } else {
            std::getline(in, buffer);
            throw std::runtime_error("Missing " + name + ": {###} while reading a serialized object\n");
        }

        std::getline(in, buffer);
        if(buffer != "}"){
            throw std::runtime_error("Missing } while reading a serialized object\n");
        }
    }

    template<>
    void GAME_EXPORTS Deserialize<std::string>(std::istream &in, const std::string &name, std::string &obj);
    template<>
    void GAME_EXPORTS Deserialize<int>(std::istream &in, const std::string &name, int &obj);
    template<>
    void GAME_EXPORTS Deserialize<unsigned int>(std::istream &in, const std::string &name, unsigned int &obj);
    template<>
    void GAME_EXPORTS Deserialize<float>(std::istream &in, const std::string &name, float &obj);

} // GmLib

#endif //PROJECTC_SERIALIAZATION_H
