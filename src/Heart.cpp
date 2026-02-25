//
// Created by 101142429 on 2/23/2026.
//

#include "../include/Heart.h"


Heart::Heart(dl::Vector2f initialPosition, dl::SpriteSheet &spriteSheet) : p_spriteSheet(&spriteSheet)
{
    m_sprite.loadFromSpriteSheet(spriteSheet, 0);
    m_sprite.setScale({5, 5});
    m_sprite.setOrigin({8 * m_sprite.getScale().x, 8 * m_sprite.getScale().y});
    m_sprite.setPosition(initialPosition);
    m_sprite.viewShouldAffect(false);
}

void Heart::restore()
{
    m_sprite.loadFromSpriteSheet(*p_spriteSheet, 0);
    m_sprite.setScale({5, 5});
    m_alive = true;
}

void Heart::kill()
{
    m_sprite.loadFromSpriteSheet(*p_spriteSheet, 1);
    m_sprite.setScale({5, 5});
    m_alive = false;
}

void Heart::drawHeart(dl::RenderWindow &window)
{
    window.draw(m_sprite);
}
