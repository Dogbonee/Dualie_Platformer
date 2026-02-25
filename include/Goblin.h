//
// Created by 101142429 on 2/23/2026.
//

#ifndef DUALIE_PLATFORMER_GOBLIN_H
#define DUALIE_PLATFORMER_GOBLIN_H
#include <Entity.h>
#include <Player.h>

class Goblin : public Entity {


    Player* p_player;

public:
    Goblin(const dl::Vector2f &initialPosition, dl::SpriteSheet& spriteSheet, Level *level, Player *player);


    int handleMovement(float dt) override;

    bool handleAnimation(float dt) override;

    void drawEntity(dl::RenderWindow &window) override;
};


#endif //DUALIE_PLATFORMER_GOBLIN_H