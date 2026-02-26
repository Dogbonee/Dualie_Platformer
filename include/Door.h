//
// Created by 101142429 on 2/25/2026.
//

#ifndef DUALIE_PLATFORMER_DOOR_H
#define DUALIE_PLATFORMER_DOOR_H
#include <Entity.h>
#include <Player.h>

class Door : public Entity {
    Player* p_player;

public:
    Door(const dl::Vector2f &initialPosition, dl::SpriteSheet &spriteSheet, Level *level, Player* player);

    int handleMovement(float dt) override;

    void handleCollision(float dt) override;

    dl::FloatRect getGlobalBounds() const override;
};


#endif //DUALIE_PLATFORMER_DOOR_H