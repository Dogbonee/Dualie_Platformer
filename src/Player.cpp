//
// Created by 101142429 on 2/21/2026.
//
#include <stdio.h>
#include "../include/Player.h"

Player::Player(std::vector<dl::SpriteSheet *> &spriteSheets, Level *level) : p_spriteSheets(&spriteSheets),
                                                                             p_currentSheet(&spriteSheets[0]),
                                                                             p_level(level), m_speed(150),
                                                                             m_animationClock(0), m_frameTime(0.1),
                                                                             m_frames(4), m_currentFrame(0),
                                                                             m_gravity(0.5), m_isOnGround(false),
                                                                             m_jumpForce(0.15), m_facingRight(true)
{
    m_sprite.loadFromSpriteSheet(*spriteSheets[0], 0);
    m_sprite.setPosition({120, 120});
}

void Player::handleMovement(float dt)
{
    m_velocity.x = dt * m_speed * (dl::Input::isKeyHeld(dl::Input::RIGHT) - dl::Input::isKeyHeld(dl::Input::LEFT));
    m_velocity.y += m_gravity * dt;
    if (m_isOnGround && dl::Input::isKeyPressed(dl::Input::A))
    {
        m_isOnGround = false;
        m_velocity.y = -m_jumpForce;
    }
    if (dl::Input::isKeyReleased(dl::Input::A) && m_velocity.y < 0)
    {
        m_velocity.y /= 2;
    }


    dl::FloatRect projectedX = dl::FloatRect(m_sprite.getPosition() + dl::Vector2f(m_velocity.x, 0), {16, 16});
    dl::FloatRect projectedY = dl::FloatRect(m_sprite.getPosition() + dl::Vector2f(0, m_velocity.y), {16, 16});

    dl::Vector2i projectedUnit = {
        static_cast<int>((m_sprite.getPosition().x + m_velocity.x) / 16),
        static_cast<int>((m_sprite.getPosition().y + m_velocity.y) / 16)
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
                dl::FloatRect tileRect(tile->getPosition(), {16, 16});

                if (projectedX.intersects(tileRect))
                {
                    if (m_velocity.x > 0)
                    {
                        m_sprite.setPosition({tile->getPosition().x - 16, m_sprite.getPosition().y});
                    } else if (m_velocity.x < 0)
                    {
                        m_sprite.setPosition({tile->getPosition().x + 16, m_sprite.getPosition().y});
                    }
                    m_velocity.x = 0;
                }

                if (projectedY.intersects(tileRect))
                {
                    if (m_velocity.y > 0)
                    {
                        m_sprite.setPosition({m_sprite.getPosition().x, tile->getPosition().y - 16});
                        m_isOnGround = true;
                    } else if (m_velocity.y < 0)
                    {
                        m_sprite.setPosition({m_sprite.getPosition().x, tile->getPosition().y + 16});
                    }
                    m_velocity.y = 0;
                }
            }
        }
    }

    m_sprite.move(m_velocity);
}

void Player::handleAnimation(float dt)
{
    if (m_velocity.x == 0 && m_velocity.y == 0)
    {
        m_frames = 4;
        p_currentSheet = &(*p_spriteSheets)[0];
    } else if (m_velocity.x != 0 && m_velocity.y == 0)
    {
        m_frames = 6;
        p_currentSheet = &(*p_spriteSheets)[1];
    } else if (m_velocity.y < 0)
    {
        m_frames = 3;
        p_currentSheet = &(*p_spriteSheets)[2];
    } else if (m_velocity.y > 0)
    {
        m_frames = 3;
        p_currentSheet = &(*p_spriteSheets)[3];
    }
    m_animationClock += dt;
    if (m_animationClock >= m_frameTime)
    {
        m_currentFrame++;
        if (m_currentFrame >= m_frames)
        {
            m_currentFrame = 0;
        }
        m_sprite.loadFromSpriteSheet(**p_currentSheet, m_currentFrame);
        m_animationClock = 0;
    }

    if (m_velocity.x > 0)
    {
        m_facingRight = true;
    } else if (m_velocity.x < 0)
    {
        m_facingRight = false;
    }
    m_sprite.setScale({m_facingRight ? 1.f : -1.f, 1});
}

void Player::drawPlayer(dl::RenderWindow &window)
{
    dl::Vector2f actualPos = m_sprite.getPosition();
    dl::Vector2f roundedPos = {std::floor(actualPos.x), std::floor(actualPos.y)};

    m_camera.reset({roundedPos.x - 50.0f, roundedPos.y - 160.0f, 400.0f, 240.0f});
    m_sprite.setPosition(roundedPos);

    window.draw(m_sprite);
    window.setView(m_camera);
    window.display();
    m_sprite.setPosition(actualPos); // Fix to prevent tearing
}
