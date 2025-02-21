//
// Created by Cristi on 2/21/2025.
//

#ifndef PROJECTC_FLOOR_H
#define PROJECTC_FLOOR_H

#include <string>
#include "raylib.h"
#include <iostream>
#include "Game_exports.h"
#include "Serialiazation.h"

namespace GmLib {

    struct GAME_EXPORTS Floor : public Serializable{
        Texture2D *texture;
        std::string textureName;
        unsigned int drawPriority;

        Floor();
        Floor(const std::string &textureName, unsigned int drawPriority);

        void serialize(std::ostream &out) const override;
        void deserialize(std::istream &in) override;

    };

} // GmLib

#endif //PROJECTC_FLOOR_H
