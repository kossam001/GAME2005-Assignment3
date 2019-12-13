#include "Bullet.h"
#include "Game.h"

Bullet::Bullet() :
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/cannonball.png",
		"cannonball", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("cannonball");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::BULLET);

	setPosition(glm::vec2(1 + rand() % 799, 1));
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("cannonball", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Bullet::update()
{
	setPosition(glm::vec2(getPosition().x, getPosition().y + 10));

	if (getPosition().y >= 600 && CollisionManager::boundaryCheck(this, 0))
	{
		setPosition(glm::vec2(1 + rand() % 799, 1));
	}
}

void Bullet::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

Tile * Bullet::getTile()
{
	return m_currentTile;
}

void Bullet::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}
