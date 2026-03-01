//
// Created by 101142429 on 2/23/2026.
//

#include "../include/Goblin.h"

Goblin::Goblin(const dl::Vector2f &initialPosition, dl::SpriteSheet &spriteSheet, Level *level,
               Player *player) : Entity(initialPosition, spriteSheet, level),
                                 p_player(player)
{
    m_friction = 1;
    m_maxSpeed = 125;
    m_acceleration = 100;
}

int Goblin::handleMovement(float dt)
{
    float distance = p_player->getPosition().x - m_sprite.getPosition().x;

    if (!p_player->isDead() && abs(distance) < 250)
    {
        if (distance != 0.0f) {
            float direction = (distance > 0) ? 1.0f : -1.0f;
            m_attemptedVelocity.x = dt * m_acceleration * direction;
        } else {
            m_attemptedVelocity.x = 0;
        }
    } else
    {
        m_velocity.x = 0;
    }

    Entity::handleMovement(dt);

    if (getGlobalBounds().intersects(p_player->getGlobalBounds()))
    {
        p_player->hit(1, p_player->getPosition().x < m_sprite.getPosition().x);
    }
    return 0;
}

bool Goblin::handleAnimation(float dt)
{
    if (m_velocity.x == 0 && m_velocity.y == 0)
    {
        m_sheetOffset = 18;
        m_frames = 4;
    } else if (m_velocity.x != 0 && m_velocity.y == 0)
    {
        m_frames = 6;
        m_sheetOffset = 0;
    }
    return Entity::handleAnimation(dt);
}

void Goblin::drawEntity(dl::RenderWindow &window)
{
    Entity::drawEntity(window);
}
