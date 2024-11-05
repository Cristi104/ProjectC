//
// Created by Cristi on 11/5/2024.
//

#include <stdbool.h>
#include "../include/Game.h"

GmlibTile GmlibTileCreate(unsigned int id) {
    GmlibTile tile;

    tile.id = id;
    tile.objects = GmlibArrayCreate(1, false);

    return tile;
}

void GmlibTileDestroy(GmlibTile tile) {
    GmlibArrayDestroy(tile.objects);
}
