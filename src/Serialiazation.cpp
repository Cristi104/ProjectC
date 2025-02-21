//
// Created by Cristi on 2/21/2025.
//

#include <string>
#include "../include/Serialiazation.h"

namespace GmLib {
    template<>
    void GmLib::Serialize<std::string>(std::ostream &out, const std::string &name, const std::string &obj) {
        out << name << ": \"" << obj << "\"\n";
    }

    template<>
    void GmLib::Serialize<int>(std::ostream &out, const std::string &name, const int &obj) {
        out << name << ": " << obj << "\n";
    }

    template<>
    void GmLib::Serialize<unsigned int>(std::ostream &out, const std::string &name, const unsigned int &obj) {
        out << name << ": " << obj << "\n";
    }

    template<>
    void Serialize<float>(std::ostream &out, const std::string &name, const float &obj){
        out << name << ": " << obj << "\n";
    }

    template<>
    void Deserialize<std::string>(std::istream &in, const std::string &name, std::string &obj){
        std::string buffer;
        std::string keyString = name + ": \"";
        std::string::size_type begin, end;

        std::getline(in, buffer);
        begin = buffer.find(keyString);
        end = buffer.rfind('\"');

        if(begin != std::string::npos && end != std::string ::npos && begin + keyString.length() != end){
            obj = buffer.substr(begin + keyString.length(), end - begin- keyString.length());
        } else throw std::runtime_error("Missing " + name + ": \"#####\" while reading a serialized object\n");
    }

    template<>
    void Deserialize<int>(std::istream &in, const std::string &name, int &obj){
        std::string buffer;
        std::string keyString = name + ": ";
        std::string::size_type begin;

        std::getline(in, buffer);
        begin = buffer.find(keyString);

        if(begin != std::string::npos){
            try{
                obj = std::stoi(buffer.substr(begin + keyString.length(), buffer.length() - begin - keyString.length()));
            } catch (std::invalid_argument &e){
                throw std::runtime_error("Invalid " + name + " argument while reading a serialized object");
            } catch (std::out_of_range &e){
                throw std::runtime_error("Invalid " + name + " argument while reading a serialized object");
            }
        } else throw std::runtime_error("Missing " + name + ": ### while reading a serialized object\n");
    }

    template<>
    void Deserialize<unsigned int>(std::istream &in, const std::string &name, unsigned int &obj){
        std::string buffer;
        std::string keyString = name + ": ";
        std::string::size_type begin;

        std::getline(in, buffer);
        begin = buffer.find(keyString);

        if(begin != std::string::npos){
            try{
                obj = std::stoi(buffer.substr(begin + keyString.length(), buffer.length() - begin - keyString.length()));
            } catch (std::invalid_argument &e){
                throw std::runtime_error("Invalid " + name + " argument while reading a serialized object");
            } catch (std::out_of_range &e){
                throw std::runtime_error("Invalid " + name + " argument while reading a serialized object");
            }
        } else throw std::runtime_error("Missing " + name + ": ### while reading a serialized object\n");
    }

    template<>
    void Deserialize<float>(std::istream &in, const std::string &name, float &obj){
        std::string buffer;
        std::string keyString = name + ": ";
        std::string::size_type begin;

        std::getline(in, buffer);
        begin = buffer.find(keyString);

        if(begin != std::string::npos){
            try{
                obj = std::stof(buffer.substr(begin + keyString.length(), buffer.length() - begin - keyString.length()));
            } catch (std::invalid_argument &e){
                throw std::runtime_error("Invalid " + name + " argument while reading a serialized object");
            } catch (std::out_of_range &e){
                throw std::runtime_error("Invalid " + name + " argument while reading a serialized object");
            }
        } else throw std::runtime_error("Missing " + name + ": ###.### while reading a serialized object\n");
    }

} // GmLib