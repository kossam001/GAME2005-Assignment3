#include "Wall.h"
#include "Game.h"

Wall::Wall() :
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/planet.png",
		"planet", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("planet");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::WALL);
}

Wall::~Wall()
{
}

void Wall::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("planet", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);

	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_Rect r = SDL_Rect{ (int)getPosition().x, (int)getPosition().y, (int)getWidth(), (int)getHeight() };
	SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &r);
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 1);
}

void Wall::update()
{
}

void Wall::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

Tile * Wall::getTile()
{
	return m_currentTile;
}

void Wall::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}