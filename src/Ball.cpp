#include "Ball.h"
#include "Game.h"

Ball::Ball() :
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/Ball.png",
		"Ball", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("Ball");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::BALL);
}

Ball::~Ball()
{
}

void Ball::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("Ball", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Ball::update()
{
	setPosition(glm::vec2(getPosition().x + horizontalDirection * cos(m_angle * 0.01745) * m_speed, 
		getPosition().y + verticalDirection * sin(m_angle * 0.01745) * m_speed));
}

void Ball::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

Tile * Ball::getTile()
{
	return m_currentTile;
}

void Ball::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}

void Ball::setAngle(float angle)
{
	m_angle = angle;
}

void Ball::setSpeed(float speed)
{
	m_speed = speed;
}

float Ball::getAngle()
{
	return m_angle;
}

float Ball::getSpeed()
{
	return m_speed;
}

void Ball::setVerticalDirection(int direction)
{
	verticalDirection = direction;
}

void Ball::setHorizontalDirection(int direction)
{
	horizontalDirection = direction;
}

int Ball::getVerticalDirection()
{
	return verticalDirection;
}

int Ball::getHorizontalDirection()
{
	return horizontalDirection;
}
