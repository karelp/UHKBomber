#ifndef PLAYER_H
#define PLAYER_H

#include "CollidableObject.h"
#include <SFML/System/Vector2.hpp>

class Player : public CollidableObject<Player> {
public:
	Player(float x, float y, float width, float height, sf::Sprite* sprite = NULL);

	/**
	 * @brief
	 * Return's current player's sprite
	 * 
	 * @returns
	 * Player's sprite
	 * 
	 * @see
	 * sf::Sprite
	 */
	sf::Sprite& getSprite() { return *m_playerSprite; }
	/**
	 * @brief
	 * Sets player's sprite (NULL value removes sprite)
	 * 
	 * @param sprite
	 * Player's sprite sf::Sprite
	 * 
	 * @see
	 * sf::Sprite
	 */
	void setSprite(sf::Sprite* sprite) 
	{ 
		m_playerSprite = sprite; 
		if(m_playerSprite != NULL) m_playerSpriteOrigCenter = m_playerSprite->GetCenter(); 
		else m_playerSpriteOrigCenter = sf::Vector2f(0, 0);
	}

	/**
	 * @brief
	 * Returns player's current direction in world space coordinates
	 * 
	 * @returns
	 * Player's direction
	 *
	 * @see
	 * sf::Vector2f
	 */
	sf::Vector2f& getDirection() { return m_playerDirection; }

	// from base class
	void render(sf::RenderTarget& target, DeltaTime dt);
	void simulate(DeltaTime dt);

private:
	sf::Sprite* m_playerSprite;
	sf::Vector2f m_playerDirection;
	sf::Vector2f m_playerSpriteOrigCenter;
	int m_playerSpriteFrame;
};

#endif