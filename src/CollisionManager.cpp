#include "CollisionManager.h"
#include "Util.h"
#include <algorithm>


int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {
			
			object2->setIsColliding(true);

			switch (object2->getType()) {
			case PLANET:
				//std::cout << "Collision with Island!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			case MINE:
				//std::cout << "Collision with Cloud!" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			case BULLET:
				TheSoundManager::Instance()->playSound("explosion", 0);
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
					break;
			}

			return true;
		}
		return false;
	}
	else if (object2->getIsColliding())
	{
		object2->setIsColliding(false);
	}
	return false;
}

bool CollisionManager::lineLineCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float x3 = line2Start.x;
	float x4 = line2End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float y3 = line2Start.y;
	float y4 = line2End.y;

	// calculate the distance to intersection point
	float uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return true;
	}
	
	return false;
}

bool CollisionManager::lineRectCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 recStart, float recWidth, float recHeight)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float rx = recStart.x;
	float ry = recStart.y;
	float rw = recWidth;
	float rh = recHeight;

	//TODO FIX THIS

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	bool left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	bool right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	bool top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	bool bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) {
		return true;
	}

	return false;
}

bool CollisionManager::boundaryCheck(GameObject * object, int offset)
{
	if (object->getPosition().y + offset >= 600 ||
		object->getPosition().y - offset <= 0 ||
		object->getPosition().x + offset >= 800 ||
		object->getPosition().x - offset <= 0)
		return true;
	return false;
}

bool CollisionManager::circleSquareCombo(GameObject * circleObject, GameObject * squareObject)
{
	float circleR = circleObject->getWidth() * 0.6;
	float squareR = squareObject->getWidth() * 0.6;

	// Combination of square and circle collision where the circle checks corners and square checks side
	if ((squaredDistance(circleObject->getPosition(), squareObject->getPosition()) <=
		(circleR + squareR) * (circleR + squareR)) &&
		squareObject->getPosition().x <= circleObject->getWidth() + circleObject->getPosition().x &&
		squareObject->getPosition().x + squareObject->getWidth() >= circleObject->getPosition().x &&
		squareObject->getPosition().y <= circleObject->getWidth() + circleObject->getPosition().y &&
		squareObject->getPosition().y + squareObject->getHeight() >= circleObject->getPosition().y)
	{
		return true;
	}
	return false;
}

int CollisionManager::bounceQuadrant(GameObject * ball, GameObject * brick)
{
	int quad;
	float angle = atan2(brick->getPosition().y - ball->getPosition().y, brick->getPosition().x - ball->getPosition().x) * 57.29577951;

	// Set the angle to be between 0 to 360
	if (angle >= 360)
	{
		while (angle >= 360)
		{
			angle -= 360;
		}
	}
	else if (angle < 0)
	{
		while (angle < 0)
		{
			angle += 360;
		}
	}

	if (0 <= angle && angle < 90)
		return 1;
	else if (90 <= angle && angle < 180)
		return 2;
	else if (180 <= angle && angle < 270)
		return 3;
	else if (270 <= angle && angle < 360)
		return 4;

	return 0;
}

bool CollisionManager::upperBoundaryCheck(GameObject * ball)
{
	int upperBoundary = 0;

	if (ball->getPosition().y - ball->getHeight() * 0.5 <= upperBoundary)
		return true;

	return false;
}

bool CollisionManager::lowerBoundaryCheck(GameObject * ball)
{
	int lowerBoundary = 600;

	if (ball->getPosition().y + ball->getHeight() * 0.5 >= lowerBoundary)
		return true;

	return false;
}

bool CollisionManager::rightBoundaryCheck(GameObject * ball)
{
	int rightBoundary = 800;

	if (ball->getPosition().x + ball->getWidth() * 0.5 >= rightBoundary)
		return true;

	return false;
}

bool CollisionManager::leftBoundaryCheck(GameObject * ball)
{
	int leftBoundary = 0;

	if (ball->getPosition().x - ball->getWidth() * 0.5 <= leftBoundary)
		return true;

	return false;
}

float CollisionManager::circleAABBSquaredDistance(glm::vec2 circleCenter, int circleRadius, glm::vec2 boxStart, int boxWidth, int boxHeight)
{
	float dx = std::max(boxStart.x - circleCenter.x, 0.0f);
	dx = std::max(dx, circleCenter.x - (boxStart.x + boxWidth));
	float dy = std::max(boxStart.y - circleCenter.y, 0.0f);
	dy = std::max(dy, circleCenter.y - (boxStart.y + boxHeight));

	return (dx * dx) + (dy * dy);
}

bool CollisionManager::circleAABBCheck(GameObject * object1, GameObject * object2)
{
	// circle
	glm::vec2 circleCentre = object1->getPosition();
	int circleRadius = std::max(object1->getWidth() * 0.5, object1->getHeight() * 0.5);

	// AABB
	int boxWidth = object2->getWidth() * 0.3;	// Tightening the bounding box
	int boxHeight = object2->getHeight() * 0.7;  
	glm::vec2 boxStart = object2->getPosition() - glm::vec2(boxWidth * 0.5, boxHeight * 0.5);

	if (circleAABBSquaredDistance(circleCentre, circleRadius, boxStart, boxWidth, boxHeight) <= (circleRadius * circleRadius))
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case PLANET:
				std::cout << "Collision with Planet!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			case MINE:
				std::cout << "Collision with Mine!" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			case SHIP:
				TheSoundManager::Instance()->playSound("explosion", 0);
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}
	return false;
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
