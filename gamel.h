#include <SFML/audio.hpp>
#include <SFML/graphics.hpp>
#include <SFML/window.hpp>
#include <SFML/system.hpp>
#include <SFML/network.hpp>
#include <iostream>
#include <ctime>

class Game
{
 public:
	 Game();
	 void run();
 private:
 	 //methods
	 void processEvents();
	 void update(sf::Time deltaTime);
	 void render();
	 void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	 void handleBombShooting(sf::Keyboard::Key key);
	 void rotation();
	 void isInEdgeTop(sf::Sprite sprite);
	 void isInEdgeDown(sf::Sprite sprite);
	 void isInEdgeLeft(sf::Sprite sprite);
	 void isInEdgeRight(sf::Sprite sprite);
	 void spawnEnemy();
	 void shootEnemy(sf::Time deltaTime2);
	 void stopMoving();
	 int setDirection();
	 void moveEnemy(sf::Time deltaTime3);
	 void endGame();
 	 //variables
	 sf::RenderWindow mWindow;
	 sf::Texture enemyTexture;
	 sf::Texture planeTexture;
	 sf::Texture bombTexture;
	 bool mIsMovingUp;
	 bool mIsMovingDown;
	 bool mIsMovingLeft;
	 bool mIsMovingRight;
	 bool mIsShooting;
	 bool isGameEnd;
	 int enemyDirection;
	 float PlayerSpeed;
	 float bombSpeed;
	 float enemySpeed;
	 sf::Time TimePerFrame;
	 sf::Sprite playerPlane;
	 sf::Sprite bombSprite;
	 sf::Sprite enemySprite;
	 int health;
	 int score;
};

