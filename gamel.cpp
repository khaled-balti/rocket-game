#include "gamel.h"
#include <iostream>


//game logic implementation

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, planeTexture()
	, playerPlane()
	, bombTexture()
	, bombSprite()
	, enemyTexture()
	, enemySprite()
	{
		//loading
		if (!planeTexture.loadFromFile("images.png"))
		 {
		 // Handle loading error
		 std::cout<<"error1"<<std::endl;
		 }
 		 playerPlane.setTexture(planeTexture);
 		 playerPlane.setPosition(100.f, 100.f);
		 playerPlane.setScale(0.5, 0.5);
		 
		 if(!bombTexture.loadFromFile("bomb.jpg"))
		 {
		 	std::cout<<"error2"<<std::endl;
		 }
		 bombSprite.setTexture(bombTexture);
		 bombSprite.setScale(0.1, 0.1);
		 bombSprite.setPosition(playerPlane.getPosition().x + 10 + playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );
		 if(!enemyTexture.loadFromFile("alien.jpg")) 
		 {
		 	std::cout<<"error3"<<std::endl;
		 }
		 enemySprite.setTexture(enemyTexture);
		 enemySprite.setScale(0.35, 0.35);
		 enemySprite.setPosition(static_cast<float> ( rand() % static_cast<int> (mWindow.getSize().x - enemySprite.getLocalBounds().width / 2)),
	                    		 static_cast<float> ( rand() % static_cast<int> (mWindow.getSize().y - enemySprite.getLocalBounds().height / 2)));
	     enemyDirection = setDirection();
		 //initVariables
		 PlayerSpeed = 180;
		 bombSpeed = 550;
		 enemySpeed = 80;
		 TimePerFrame = sf::seconds (1.f/60.f);
		 mIsMovingUp = false;
		 mIsMovingDown = false;
		 mIsMovingLeft = false;
		 mIsMovingRight = false;
		 mIsShooting = false;
		 isGameEnd = false;
		 health = 5;
		 score = 0;
	}
void Game::processEvents()
{
	 sf::Event event;
	 while (mWindow.pollEvent(event))
	 {
		switch (event.type)
 		{
	 		 case sf::Event::KeyPressed:
			 handlePlayerInput(event.key.code, true);
			 break;
			 case sf::Event::KeyReleased:
			 handlePlayerInput(event.key.code, false);
			 break;
			 case sf::Event::Closed:
			 mWindow.close();
			 break;
		}
	}	 
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{ 
	playerPlane.setOrigin(sf::Vector2f(playerPlane.getLocalBounds().width, playerPlane.getLocalBounds().height) / 2.f);
	bombSprite.setOrigin(sf::Vector2f(playerPlane.getLocalBounds().width / 2.f, playerPlane.getLocalBounds().height) / 2.f);
	 if (key == sf::Keyboard::Z) {
	 	mIsMovingUp = isPressed;
	 	playerPlane.setRotation(90);	 		 	
	 	bombSprite.setPosition(playerPlane.getPosition().x , playerPlane.getPosition().y - playerPlane.getLocalBounds().height / 2 + 10); 		 	
	 }
	else if (key == sf::Keyboard::S) {
		mIsMovingDown = isPressed;
	 	playerPlane.setRotation(-90);	
	 	bombSprite.setPosition(playerPlane.getPosition().x , playerPlane.getPosition().y + playerPlane.getLocalBounds().height / 2 - 10);
	}
	 else if (key == sf::Keyboard::Q) {
	 	mIsMovingLeft = isPressed;
	 	playerPlane.setRotation(0);	 	
	 	bombSprite.setPosition(playerPlane.getPosition().x + 10 - playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );	 	
	 }
	 else if (key == sf::Keyboard::D) {
	 	mIsMovingRight = isPressed;
	 	playerPlane.setRotation(180);	 	
	 	bombSprite.setPosition(playerPlane.getPosition().x - 10 + playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );	 	
	 }
	 else if (key == sf::Keyboard::K) {
	 	mIsShooting = isPressed;
	 }	
}
void Game::isInEdgeTop(sf::Sprite sprite) {
	if (sprite.getPosition().y <= sprite.getLocalBounds().height / 6) {
		mIsMovingUp = false;
	}
}
void Game::isInEdgeDown(sf::Sprite sprite) {
	if(sprite.getPosition().y >= (mWindow.getSize().y - sprite.getLocalBounds().height / 6)) {
		mIsMovingDown = false;
	}
}
void Game::isInEdgeLeft(sf::Sprite sprite) { 
	if(sprite.getPosition().x <= sprite.getLocalBounds().height / 6) {
		mIsMovingLeft = false;
	}
}
void Game::isInEdgeRight(sf::Sprite sprite) {
	if(sprite.getPosition().x >= (mWindow.getSize().x - sprite.getLocalBounds().height / 6)) {
		mIsMovingRight = false;
	}
}
void Game::stopMoving() {
	if(enemySprite.getGlobalBounds().intersects(playerPlane.getGlobalBounds())) {
		if(playerPlane.getPosition().x + bombSprite.getLocalBounds().width >= enemySprite.getPosition().x - enemySprite.getLocalBounds().width &&
		playerPlane.getPosition().x + bombSprite.getLocalBounds().width <= enemySprite.getPosition().x + enemySprite.getLocalBounds().width)                                        
			mIsMovingRight = false;
		if(playerPlane.getPosition().x - bombSprite.getLocalBounds().width<= enemySprite.getPosition().x + enemySprite.getLocalBounds().width &&
		playerPlane.getPosition().x - bombSprite.getLocalBounds().width >= enemySprite.getPosition().x - enemySprite.getLocalBounds().width)
			mIsMovingLeft = false;
		if(playerPlane.getPosition().y + bombSprite.getLocalBounds().height >= enemySprite.getPosition().y - enemySprite.getLocalBounds().height &&
		playerPlane.getPosition().y + bombSprite.getLocalBounds().height <= enemySprite.getPosition().y + enemySprite.getLocalBounds().height)
			mIsMovingDown = false;
		if(playerPlane.getPosition().y - bombSprite.getLocalBounds().height <= enemySprite.getPosition().y + enemySprite.getLocalBounds().height &&
		playerPlane.getPosition().y - bombSprite.getLocalBounds().height >= enemySprite.getPosition().y - enemySprite.getLocalBounds().height)
			mIsMovingUp = false;
	}
}
void Game::shootEnemy(sf::Time deltaTime2) {
	if(mIsShooting) {
		sf::Vector2f translation(0.f,0.f);
		if(playerPlane.getRotation() == 90) {
			translation.y -=bombSpeed;
		}
		if(playerPlane.getRotation() == 270) {
			translation.y +=bombSpeed;
		}
		if(playerPlane.getRotation() == 0) {
			translation.x -=bombSpeed;
		}
		if(playerPlane.getRotation() == 180) {
			translation.x +=bombSpeed;
		}
		bombSprite.move(translation * deltaTime2.asSeconds());	
	}
	else {
		if(playerPlane.getRotation() == 90) {
			bombSprite.setPosition(playerPlane.getPosition().x , playerPlane.getPosition().y - playerPlane.getLocalBounds().height / 2 + 10);
		}
		if(playerPlane.getRotation() == 270) {
			bombSprite.setPosition(playerPlane.getPosition().x , playerPlane.getPosition().y + playerPlane.getLocalBounds().height / 2 - 10);
		}
		if(playerPlane.getRotation() == 0) {
			bombSprite.setPosition(playerPlane.getPosition().x + 10 - playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );	 
		}
		if(playerPlane.getRotation() == 180) {
			bombSprite.setPosition(playerPlane.getPosition().x - 10 + playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );
		}
	}
	if (mIsShooting && (bombSprite.getPosition().x - playerPlane.getPosition().x >=350 ||
	                    bombSprite.getPosition().x - playerPlane.getPosition().x <=-350 ||
						bombSprite.getPosition().y - playerPlane.getPosition().y >=350 ||
						bombSprite.getPosition().y - playerPlane.getPosition().y <=-350)) {
		if(playerPlane.getRotation() == 90) {
			bombSprite.setPosition(playerPlane.getPosition().x , playerPlane.getPosition().y - playerPlane.getLocalBounds().height / 2 + 10);
		}
		if(playerPlane.getRotation() == 270) {
			bombSprite.setPosition(playerPlane.getPosition().x , playerPlane.getPosition().y + playerPlane.getLocalBounds().height / 2 - 10);
		}
		if(playerPlane.getRotation() == 0) {
			bombSprite.setPosition(playerPlane.getPosition().x + 10 - playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );	 
		}
		if(playerPlane.getRotation() == 180) {
			bombSprite.setPosition(playerPlane.getPosition().x - 10 + playerPlane.getLocalBounds().height / 2 , playerPlane.getPosition().y );
		}
	}
	if (mIsShooting && bombSprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
		score += 1;
		spawnEnemy();
	}
}
void Game::update(sf::Time deltaTime)
{
		isInEdgeTop(playerPlane);
	    isInEdgeDown(playerPlane);
	    isInEdgeLeft(playerPlane);
	    isInEdgeRight(playerPlane);
	    stopMoving();
		sf::Vector2f movement(0.f , 0.f);
		if(mIsMovingUp)
			movement.y -= PlayerSpeed;
		if(mIsMovingDown)
			movement.y += PlayerSpeed;
		if(mIsMovingLeft)
			movement.x -= PlayerSpeed;
		if(mIsMovingRight)
			movement.x += PlayerSpeed;
		playerPlane.move(movement * deltaTime.asSeconds());
		bombSprite.move(movement * deltaTime.asSeconds());
}
int Game::setDirection() {
	int direction;
	direction = static_cast<int> ( rand() % static_cast<int> (3));
	return direction;
}
void Game::moveEnemy(sf::Time deltaTime3) {
	sf::Vector2f translation2(0.f,0.f);
	if (enemyDirection == 0) {
		translation2.x += enemySpeed;
	}
	if (enemyDirection == 1) {
		translation2.x -= enemySpeed;
	}
	if (enemyDirection == 2) {
		translation2.y += enemySpeed;
	}
	if (enemyDirection == 3) {
		translation2.y -= enemySpeed;
	}
	enemySprite.move(translation2 * deltaTime3.asSeconds());
	if (enemySprite.getPosition().x  + enemySprite.getLocalBounds().width /2 <0 ||
		enemySprite.getPosition().x> mWindow.getSize().x ||
		enemySprite.getPosition().y + enemySprite.getLocalBounds().height /2 <0 ||
		enemySprite.getPosition().y > mWindow.getSize().y) {
			health--;
			spawnEnemy();	
		}
}
void Game::spawnEnemy() {
	enemySprite.setPosition(static_cast<float> ( rand() % static_cast<int> (mWindow.getSize().x - enemySprite.getLocalBounds().width / 2)),
	                        static_cast<float> ( rand() % static_cast<int> (mWindow.getSize().y - enemySprite.getLocalBounds().height / 2)));
	enemyDirection = setDirection();
	std::cout<<"score = "<<score<<std::endl;
	std::cout<<"health = "<<health<<std::endl;
	enemySpeed +=5;
}
void Game::endGame() {
	if(score >= 20) {
		std::cout<<"YOU WON"<<std::endl;
		isGameEnd = true;	
	}
	if(health < 0) {
		std::cout<<"YOU LOST"<<std::endl;
		isGameEnd = true;	
	}
}
void Game::render()
{
	endGame();
	if (!isGameEnd) {
		 mWindow.clear();
		 mWindow.draw(playerPlane);
		 if (mIsShooting) {
			mWindow.draw(bombSprite);	
		 }
		 mWindow.draw(enemySprite);
		 mWindow.display();
		 
	}
	else {
		std::cout<<"GAME OVER"<<std::endl;
		std::cout<<score<<std::endl;
		mWindow.close();
	}
}
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
 	while(mWindow.isOpen()) {
 		timeSinceLastUpdate += clock.restart();
 		while (timeSinceLastUpdate > TimePerFrame) {
 			timeSinceLastUpdate -= TimePerFrame;
 			processEvents();
			update(TimePerFrame);
			shootEnemy(TimePerFrame);
			moveEnemy(TimePerFrame);
		 }
		render();
	}
}
