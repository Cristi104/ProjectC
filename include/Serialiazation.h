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
        /// serializes the inner data of a object
        virtual void serializeData(std::ostream &out) const = 0;

        /// deserializes the inner data of a object
        virtual void deserializeData(std::istream &in) = 0;

        virtual ~Serializable() = default;
    };

    /// serializes any object of a Serializable derived class to a given ostream using a human readable json-like format
    /// @param out the output stream where the object data will be printed
    /// @param name the name used to identify the data
    /// @param obj object to serialize if the object is not a primitive it will be surrounded by {}
    template<typename T>
    void Serialize(std::ostream &out, const std::string &name, const T &obj){
        out << name << ": {\n";
        obj.serializeData(out);
        out << "}\n";
    }

    /// serializes any object of a Serializable derived class to a given ostream using a human readable json-like format
    /// @param out the output stream where the object data will be printed
    /// @param name the name used to identify the data
    /// @param obj object to serialize if the object is not a primitive it will be surrounded by {}
    template<>
    void GAME_EXPORTS Serialize<std::string>(std::ostream &out, const std::string &name, const std::string &obj);

    /// serializes any object of a Serializable derived class to a given ostream using a human readable json-like format
    /// @param out the output stream where the object data will be printed
    /// @param name the name used to identify the data
    /// @param obj object to serialize if the object is not a primitive it will be surrounded by {}
    template<>
    void GAME_EXPORTS Serialize<int>(std::ostream &out, const std::string &name, const int &obj);

    /// serializes any object of a Serializable derived class to a given ostream using a human readable json-like format
    /// @param out the output stream where the object data will be printed
    /// @param name the name used to identify the data
    /// @param obj object to serialize if the object is not a primitive it will be surrounded by {}
    template<>
    void GAME_EXPORTS Serialize<unsigned int >(std::ostream &out, const std::string &name, const unsigned int &obj);

    /// serializes any object of a Serializable derived class to a given ostream using a human readable json-like format
    /// @param out the output stream where the object data will be printed
    /// @param name the name used to identify the data
    /// @param obj object to serialize if the object is not a primitive it will be surrounded by {}
    template<>
    void GAME_EXPORTS Serialize<float>(std::ostream &out, const std::string &name, const float &obj);

    /// deserializes any object of a Serializable derived class from a given istream
    /// @param in the input stream where the object data is
    /// @param name the expected name of the object
    /// @returns the deserialized object
    /// @throws std::runtime_error if the data is not found in the expected format or order
    template<typename T>
    T Deserialize(std::istream &in, const std::string &name){
        std::string buffer;
        std::string keyString = name + ": {";
        std::string::size_type begin;
        T obj;

        std::getline(in, buffer);
        while (buffer.empty())
            std::getline(in, buffer);

        if(buffer == keyString){
            obj.deserializeData(in);
        } else {
            std::getline(in, buffer);
            throw std::runtime_error("Missing " + name + ": {###} while reading a serialized object\n");
        }

        std::getline(in, buffer);
        while (buffer.empty())
            std::getline(in, buffer);

        if(buffer != "}"){
            throw std::runtime_error("Missing } while reading a serialized object\n");
        }

        return obj;
    }

    /// deserializes any object of a Serializable derived class from a given istream
    /// @param in the input stream where the object data is
    /// @param name the expected name of the object
    /// @returns the deserialized object
    /// @throws std::runtime_error if the data is not found in the expected format or order
    template<>
    std::string GAME_EXPORTS Deserialize<std::string>(std::istream &in, const std::string &name);

    /// deserializes any object of a Serializable derived class from a given istream
    /// @param in the input stream where the object data is
    /// @param name the expected name of the object
    /// @returns the deserialized object
    /// @throws std::runtime_error if the data is not found in the expected format or order
    template<>
    int GAME_EXPORTS Deserialize<int>(std::istream &in, const std::string &name);

    /// deserializes any object of a Serializable derived class from a given istream
    /// @param in the input stream where the object data is
    /// @param name the expected name of the object
    /// @returns the deserialized object
    /// @throws std::runtime_error if the data is not found in the expected format or order
    template<>
    unsigned int GAME_EXPORTS Deserialize<unsigned int>(std::istream &in, const std::string &name);

    /// deserializes any object of a Serializable derived class from a given istream
    /// @param in the input stream where the object data is
    /// @param name the expected name of the object
    /// @returns the deserialized object
    /// @throws std::runtime_error if the data is not found in the expected format or order
    template<>
    float GAME_EXPORTS Deserialize<float>(std::istream &in, const std::string &name);

} // GmLib

#endif //PROJECTC_SERIALIAZATION_H
