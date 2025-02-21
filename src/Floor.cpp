//
// Created by Cristi on 2/21/2025.
//

#include <stdexcept>
#include "../include/Floor.h"
#include "../include/Resources.h"

namespace GmLib {

    Floor::Floor(const std::string &textureName, unsigned int drawPriority)
            :texture(Resources::getTexture(textureName)), textureName(textureName), drawPriority(drawPriority) {}

    Floor::Floor()
            :texture(Resources::getTexture("MissingTexture.png")), textureName("MissingTexture.png"), drawPriority(0){}

    void Floor::serialize(std::ostream &out) const {
        Serialize(out, "Texture name", textureName);
        Serialize(out, "Draw priority", drawPriority);
    }

    void Floor::deserialize(std::istream &in) {
        Deserialize(in, "Texture name", textureName);
        if(textureName.find(".png", textureName.length() - 4) != std::string ::npos)
            texture = Resources::getTexture(textureName);
        else
            throw std::runtime_error("Texture name given for Floor is not a .png\n");
        Deserialize(in, "Draw priority", drawPriority);
    }

} // GmLib