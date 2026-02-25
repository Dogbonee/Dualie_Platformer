//
// Created by 101142429 on 2/21/2026.
//
#include <stdio.h>
#include "../include/Player.h"

Player::Player(const dl::Vector2f &initialPosition, dl::SpriteSheet &spriteSheet, Level *level)
    : Entity(initialPosition, spriteSheet, level),
      m_hit(false),
      m_dead(false),
      m_invincible(false),
      m_lives(5),
      m_health(3),
      m_invincibleTimer(0),
      m_invincibleTime(1),
      m_deathTimer(0),
      m_deathTime(2)
{
}

int Player::handleMovement(float dt)
{
    if (m_dead)
    {
        m_velocity = {0, 0};
        return m_health;
    }
    m_attemptedVelocity.x = dt * m_acceleration * (
                                dl::Input::isKeyHeld(dl::Input::RIGHT) - dl::Input::isKeyHeld(dl::Input::LEFT));

    if (m_isOnGround && dl::Input::isKeyPressed(dl::Input::A))
    {
        m_isOnGround = false;
        m_attemptedVelocity.y = -m_jumpForce;
    }
    if (dl::Input::isKeyReleased(dl::Input::A) && m_velocity.y < 0)
    {
        m_velocity.y /= 2;
    }

    Entity::handleMovement(dt);

    if (m_invincible)
    {
        m_invincibleTimer += dt;
        if (m_invincibleTimer > m_invincibleTime)
        {
            m_invincible = false;
            m_invincibleTimer = 0;
        }
    }

    return m_health;
}

bool Player::handleAnimation(float dt)
{
    m_sheetOffset = 0;
    if (m_dead)
    {
        m_frames = 8;
        m_sheetOffset = 0;
    } else if (m_hit)
    {
        m_frames = 3;
        m_sheetOffset = 64;
    } else if (m_velocity.x == 0 && m_velocity.y == 0)
    {
        m_frames = 4;
        m_sheetOffset = 40;
    } else if (m_velocity.x != 0 && m_velocity.y == 0)
    {
        m_frames = 6;
        m_sheetOffset = 8;
    } else if (m_velocity.y < 0)
    {
        m_frames = 3;
        m_sheetOffset = 56;
    } else if (m_velocity.y > 0)
    {
        m_frames = 3;
        m_sheetOffset = 48;
    }

    bool done = Entity::handleAnimation(dt);
    if (m_dead)
    {
        if (done)
        {
            m_sprite.loadFromSpriteSheet(*p_spriteSheet, 15);
            m_animationRunning = false;
        }
        m_deathTimer += dt;
        if (m_deathTimer >= m_deathTime)
        {
            m_dead = false;
            m_sprite.setPosition(m_initialPosition);
            m_health = MAX_HEALTH;
            m_animationRunning = true;
            m_deathTimer = 0;
        }
    } else if (m_hit && done)
    {
        m_hit = false;
    }


    return true;
}

void Player::hit(bool fromRight)
{
    if (m_invincible)
    {
        return;
    }
    m_health--;
    if (m_health <= 0)
    {
        m_dead = true;
        return;
    }
    m_hit = true;
    m_invincible = true;
    m_isOnGround = false;
    m_currentFrame = 0;
    m_animationClock = 0;
    m_velocity.y = -m_jumpForce / 1.5;
    m_velocity.x = fromRight ? -m_jumpForce : m_jumpForce;
}

void Player::drawEntity(dl::RenderWindow &window)
{
    dl::Vector2f actualPos = m_sprite.getPosition();
    dl::Vector2f roundedPos = {std::floor(actualPos.x), std::floor(actualPos.y)};

    float xClamp = std::clamp(roundedPos.x - 120.f, 0.f, 100000.f);
    m_camera.reset({xClamp, 200.0f, 400.0f, 240.0f});
    m_sprite.setPosition(roundedPos);

    window.draw(m_sprite);
    window.setView(m_camera);
    window.display();
    m_sprite.setPosition(actualPos); // Fix to prevent tearing
}

const bool &Player::isDead() const
{
    return m_dead;
}
