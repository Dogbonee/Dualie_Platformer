//
// Created by 101142429 on 2/25/2026.
//

#include "../include/Door.h"


Door::Door(const dl::Vector2f &initialPosition, dl::SpriteSheet &spriteSheet, Level *level, Player* player)
    : Entity(initialPosition, spriteSheet, level), p_player(player)
{
    m_sprite.setScale({2.5, 2.5});
    m_animationRunning = false;
}

int Door::handleMovement(float dt)
{
    handleCollision(dt);
    return 0;
}

void Door::handleCollision(float dt)
{
    if (getGlobalBounds().intersects(p_player->getGlobalBounds()))
    {
        p_player->hit(3, true);
    }
}

dl::FloatRect Door::getGlobalBounds() const
{
    return {{m_sprite.getPosition()}, {TILE_SIZE * 2.5, TILE_SIZE * 2.5}};
}


