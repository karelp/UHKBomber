#include "Player.h"

/**
 * @brief
 * Default player constructor
 * 
 * @param x
 * X-axis coordinates of player initial position in world space
 * 
 * @param y
 * Y-axis coordinates of player initial position in world space
 * 
 * @param width
 * Player width in world space coordinates
 * 
 * @param height
 * Player height in world space coordinates
 * 
 * @param sprite
 * Pointer to player's sprite (optional parameter)
 * 
 * @see
 * CollidableObject
 */
Player::Player(float x, float y, float width, float height, sf::Sprite* sprite) : CollidableObject(x, y, width, height)
{
	m_playerSprite = NULL;
	if(sprite != NULL) setSprite(sprite);
	m_playerSpriteFrame = 0;
}

void Player::render(sf::RenderTarget& target, DeltaTime dt)
{
	if(m_playerSprite != NULL) {
		m_playerSprite->SetCenter( m_playerSpriteOrigCenter + sf::Vector2f(0, m_playerSpriteFrame * m_width));
		target.Draw(*m_playerSprite);
	}
}

void Player::simulate(DeltaTime dt)
{

}