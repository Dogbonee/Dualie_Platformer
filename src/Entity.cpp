//
// Created by 101142429 on 2/23/2026.
//

#include "Entity.h"

Entity::Entity(dl::Vector2f initialPosition, dl::SpriteSheet &spriteSheet, Level *level) : p_spriteSheet(&spriteSheet),
    p_level(level),
    m_animationClock(0), m_frameTime(0.1),
    m_frames(4), m_currentFrame(0), m_sheetOffset(0),
    m_gravity(500), m_isOnGround(false),
    m_jumpForce(300), m_facingRight(true),
    m_friction(10), m_maxSpeed(300), m_acceleration(500),
    m_initialPosition(initialPosition), m_animationRunning(true)
{
    m_sprite.loadFromSpriteSheet(spriteSheet, 0);
    m_sprite.setPosition(initialPosition);
}

int Entity::handleMovement(float dt)
{
    m_velocity.y += m_gravity * dt;

    if (m_attemptedVelocity.x == 0)
    {
        m_velocity.x = std::lerp(m_velocity.x, 0, m_friction * dt);
        if (abs(m_velocity.x) < 1)
        {
            m_velocity.x = 0;
        }
    }

    m_velocity = m_velocity + m_attemptedVelocity;

    m_velocity.x = std::clamp(m_velocity.x, -m_maxSpeed, m_maxSpeed);


    handleCollision(dt);

    m_sprite.move({m_velocity.x * dt, m_velocity.y * dt});

    m_attemptedVelocity = {0, 0};

    return 0;
}

void Entity::handleCollision(float dt)
{
    dl::FloatRect projectedX = dl::FloatRect(m_sprite.getPosition() + dl::Vector2f(m_velocity.x * dt, 0),
                                             {TILE_SIZE * SPRITE_SCALE, TILE_SIZE * SPRITE_SCALE});
    dl::FloatRect projectedY = dl::FloatRect(m_sprite.getPosition() + dl::Vector2f(0, m_velocity.y * dt),
                                             {TILE_SIZE * SPRITE_SCALE, TILE_SIZE * SPRITE_SCALE});

    if (projectedX.left < 0)
    {
        m_sprite.setPosition({0, m_sprite.getPosition().y});
        m_velocity.x = 0;
    }

    dl::Vector2i projectedUnit = {
        static_cast<int>((m_sprite.getPosition().x + m_velocity.x * dt) / (TILE_SIZE * SPRITE_SCALE)),
        static_cast<int>((m_sprite.getPosition().y + m_velocity.y * dt) / (TILE_SIZE * SPRITE_SCALE))
    };

    for (int i = projectedUnit.y - 1; i <= projectedUnit.y + 1; i++)
    {
        if (i < 0 || i >= p_level->size()) continue;

        for (int j = projectedUnit.x - 1; j <= projectedUnit.x + 1; j++)
        {
            if (j < 0 || j >= (*p_level)[i].size()) continue;

            dl::Sprite *tile = (*p_level)[i][j];
            if (tile)
            {
                dl::FloatRect tileRect(tile->getPosition(), {TILE_SIZE * SPRITE_SCALE, TILE_SIZE * SPRITE_SCALE});

                if (projectedX.intersects(tileRect))
                {
                    if (m_velocity.x > 0)
                    {
                        m_sprite.setPosition({
                            tile->getPosition().x - (TILE_SIZE * SPRITE_SCALE), m_sprite.getPosition().y
                        });
                    } else if (m_velocity.x < 0)
                    {
                        m_sprite.setPosition({
                            tile->getPosition().x + (TILE_SIZE * SPRITE_SCALE), m_sprite.getPosition().y
                        });
                    }
                    m_velocity.x = 0;
                }

                if (projectedY.intersects(tileRect))
                {
                    if (m_velocity.y > 0)
                    {
                        m_sprite.setPosition({
                            m_sprite.getPosition().x, tile->getPosition().y - (TILE_SIZE * SPRITE_SCALE)
                        });
                        m_isOnGround = true;
                    } else if (m_velocity.y < 0)
                    {
                        m_sprite.setPosition({
                            m_sprite.getPosition().x, tile->getPosition().y + (TILE_SIZE * SPRITE_SCALE)
                        });
                    }
                    m_velocity.y = 0;
                }
            }
        }
    }
}

bool Entity::handleAnimation(float dt)
{
    if (!m_animationRunning) return false;
    bool lastFrame = false;
    m_animationClock += dt;
    if (m_animationClock >= m_frameTime)
    {
        m_currentFrame++;
        if (m_currentFrame >= m_frames)
        {
            lastFrame = true;
            m_currentFrame = 0;
        }
        m_sprite.loadFromSpriteSheet(*p_spriteSheet, m_sheetOffset + m_currentFrame);
        m_animationClock = 0;
    }

    if (m_velocity.x > 0)
    {
        m_facingRight = true;
    } else if (m_velocity.x < 0)
    {
        m_facingRight = false;
    }
    m_sprite.setScale({m_facingRight ? SPRITE_SCALE : -SPRITE_SCALE, SPRITE_SCALE});
    return lastFrame;
}

void Entity::drawEntity(dl::RenderWindow &window)
{
    window.draw(m_sprite);
}

const dl::Vector2f &Entity::getPosition() const
{
    return m_sprite.getPosition();
}

dl::FloatRect Entity::getGlobalBounds() const
{
    return {{m_sprite.getPosition()}, {TILE_SIZE * SPRITE_SCALE, TILE_SIZE * SPRITE_SCALE}};
}
