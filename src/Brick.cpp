#include "Brick.h"
#include "Game.h"

Brick::Brick() :
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/brick.png",
		"brick", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::BRICK);

	m_lastLocation = getPosition();
}

Brick::~Brick()
{
}

void Brick::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("brick", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Brick::update()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	setPosition(glm::vec2(x, y));

	// Speed calculated by calculating the change in distance between each frame
	m_angle = atan2(getPosition().y - m_lastLocation.y, getPosition().x - m_lastLocation.x) * 57.29578;

	if (m_angle < 0)
		m_angle += 360;

	m_speed = sqrt((getPosition().x - m_lastLocation.x) * (getPosition().x - m_lastLocation.x) + (getPosition().y - m_lastLocation.y) * (getPosition().y - m_lastLocation.y));
	m_lastLocation = getPosition();
}

void Brick::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

Tile * Brick::getTile()
{
	return m_currentTile;
}

void Brick::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}

float Brick::getAngle()
{
	return m_angle;
}

float Brick::getSpeed()
{
	return m_speed;
}
