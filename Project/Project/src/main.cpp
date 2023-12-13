#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <cstdlib>
#include <Events.h>
#include <Debug.h>

using namespace std;
using namespace sf;
float VectorLength(sf::Vector2f);

//added cute_c2 for collisons
#define CUTE_C2_IMPLEMENTATION
#include <cute_c2.h>



sf::Font m_CYBER;

sf::Text m_PlHealth;
sf::Text m_EnHealth;
sf::Text m_Attack;
sf::Text m_Throw;
sf::Text m_Dodge;
sf::Text m_Gameover;
sf::Texture m_Kunai_texture;
sf::Sprite m_Kunai_sprite;



void SetupFonts(){
	if (!m_CYBER.loadFromFile(m_Fonts)) {
		std::cout << "ERROR with fonts" << std::endl;
	}
	m_PlHealth.setFont(m_CYBER);
	m_PlHealth.setString("HEALTH = 100");
	m_PlHealth.setPosition(20.0f, 450.0f);
	m_PlHealth.setCharacterSize(30U);
	m_PlHealth.setFillColor(sf::Color::Green);

	m_EnHealth.setFont(m_CYBER);
	m_EnHealth.setString("HEALTH = 100");
	m_EnHealth.setPosition(550.0f, 450.0f);
	m_EnHealth.setCharacterSize(30U);
	m_EnHealth.setFillColor(sf::Color::Red);

	m_Attack.setFont(m_CYBER);
	m_Attack.setString("A : Attack '20 Dammage'");
	m_Attack.setPosition(20.0f, 550.0f);
	m_Attack.setCharacterSize(20U);
	m_Attack.setFillColor(sf::Color::Blue);
	m_Attack.setOutlineThickness(2.5f);
	m_Attack.setOutlineColor(sf::Color::White);

	m_Throw.setFont(m_CYBER);
	m_Throw.setString("S : Throw '10 Dammage'");
	m_Throw.setPosition(370.0f, 550.0f);
	m_Throw.setCharacterSize(20U);
	m_Throw.setFillColor(sf::Color::Blue);
	m_Throw.setOutlineThickness(2.5f);
	m_Throw.setOutlineColor(sf::Color::White);

	m_Dodge.setFont(m_CYBER);
	m_Dodge.setString("D :Dodge");
	m_Dodge.setPosition(720.0f, 550.0f);
	m_Dodge.setCharacterSize(20U);
	m_Dodge.setFillColor(sf::Color::Blue);
	m_Dodge.setOutlineThickness(2.5f);
	m_Dodge.setOutlineColor(sf::Color::White);

	m_Gameover.setFont(m_CYBER);
	m_Gameover.setCharacterSize(50U);
	m_Gameover.setFillColor(sf::Color::Blue);
	m_Gameover.setOutlineThickness(2.5f);
	m_Gameover.setOutlineColor(sf::Color::White);

}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "NINJA FIGHT CLUB");
	sf::Clock clock;

	SetupFonts();

	// Load a sprite to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile(PLAYER_SPRITES))
	{
		DEBUG_MSG("Failed to load file");
		if (!player_texture.loadFromFile(ERROR_SPRITES))
		{
			return EXIT_FAILURE;
		}
	}

	bool m_Graphics = true;

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);

	//Players varibles
	Player player(player_animated_sprite);
	player.m_Health = 100;
	player.m_Turn = true;
	player.m_Attacking = false;
	player.m_Shooting = false;
	player.m_Defending = false;
	
	sf::Vector2f m_PlCoLocation;
	m_PlCoLocation = sf::Vector2f{ 175.0f,230.0f };
	sf::Vector2f m_EnCoLocation;
	m_EnCoLocation = sf::Vector2f{ 610.0f,230.0f };

	//Playes Shapes
	sf::RectangleShape m_playerBody(sf::Vector2f(100, 200));
	m_playerBody.setPosition(75, 150);
	m_playerBody.setFillColor(sf::Color::Green);

	//Player Collider
	sf::CircleShape m_PlCollider(20);
	m_PlCollider.setFillColor(sf::Color::Blue);
	m_PlCollider.setPosition(m_PlCoLocation);

	//Enemys variables
	Player npc(player_animated_sprite);
	npc.m_Turn = false;
	npc.m_Health = 100;
	sf::Vector2f m_EnLocation;
	m_EnLocation = sf::Vector2f{ 650.0f,150.0f };

	//Enemys Shapes
	sf::RectangleShape m_enemyBody(sf::Vector2f(100, 200));
	m_enemyBody.setPosition(m_EnLocation);
	m_enemyBody.setFillColor(sf::Color::Red);

	//Enemy Collider
	sf::CircleShape m_EnCollider(20);
	m_EnCollider.setFillColor(sf::Color::Yellow);
	m_EnCollider.setPosition(m_EnCoLocation);


	//Setup Player Collidor
	c2Circle PlayerCollison;
	PlayerCollison.p = c2V(m_PlCollider.getPosition().x, m_PlCollider.getPosition().y);
	PlayerCollison.r = m_PlCollider.getRadius();

	//Setup Enemy Collider
	c2Circle EnemyCollison;
	EnemyCollison.p = c2V(m_EnCollider.getPosition().x, m_EnCollider.getPosition().y);
	EnemyCollison.r =  m_EnCollider.getRadius();

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(m_enemyBody.getPosition().x, m_enemyBody.getPosition().y);
	aabb_npc.max = c2V(
		m_enemyBody.getPosition().x +
		m_enemyBody.getGlobalBounds().width,
		m_enemyBody.getPosition().y +
		m_enemyBody.getGlobalBounds().height);

	//Set Player AABB
	c2AABB aabb_player;
	aabb_player.min = c2V(m_playerBody.getPosition().x, m_playerBody.getPosition().y);
	aabb_player.max = c2V(
		m_playerBody.getPosition().x +
		m_playerBody.getGlobalBounds().width,
		m_playerBody.getPosition().y +
		m_playerBody.getGlobalBounds().height);



	bool collison = c2CircletoAABB(PlayerCollison, aabb_npc);
	bool collison2 = c2CircletoAABB(EnemyCollison, aabb_player);

	gpp::Events input;
	gpp::Events ai;

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
				// Deal with KeyPressed
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
					m_Graphics = false;
					std::cout << "Graphics off" << std::endl;
				}
				if (player.m_Health >= 0) {
					if (player.m_Turn == true) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
							input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
							std::cout << "Player is attacking" << std::endl;
							player.m_Attacking = true;
							npc.m_Turn = true;
							player.m_Turn = false;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
							input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
							std::cout << "Player is throwing" << std::endl;
							player.m_Shooting = true;
							npc.m_Turn = true;
							player.m_Turn = false;

						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
							input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
							std::cout << "Player is Jumping" << std::endl;
							player.m_Defending = true;
							npc.m_Turn = true;
							player.m_Turn = false;
						}
					}
				}
			break;
	
				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::G) {
					m_Graphics = true;
					std::cout << "Graphics on" << std::endl;
				}
					if (event.key.code == sf::Keyboard::A) {
						input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
						std::cout << "Stopping Player attacking" << std::endl;
					
					}
					if (event.key.code == sf::Keyboard::S) {
						input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
						std::cout << "Stopping Player Throwing" << std::endl;
						
					}
				break;
			default:
				DEBUG_MSG("gpp::Events::Event::NONE");
				input.setCurrent(gpp::Events::Event::NONE);
				break;
			}
			// Handle input to Player
			player.handleInput(input);
		}

		
		// Update AI
		sf::Time deltaTime = clock.restart();

		if (npc.m_Health > 0 && npc.m_Turn) {
			// Decision-making
			gpp::Events aiDecision;

			// Introduce a cooldown timer for AI decisions (e.g., 1 second)
			static sf::Time aiDecisionCooldown = sf::seconds(1.0f);
			static sf::Time currentCooldown = sf::Time::Zero;

			// Only update cooldown if not in attack or throwing state
			if (!npc.m_Attacking && !npc.m_Shooting) {
				currentCooldown -= deltaTime;
			}

			if (currentCooldown <= sf::Time::Zero) {
				int weapon = rand() % 3 + 1;
				switch (weapon) {
				case 1:
					aiDecision.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
					npc.m_Attacking = true;
					break;
				case 2:
					aiDecision.setCurrent(gpp::Events::Event::THROW_START_EVENT);
					npc.m_Shooting = true;
					break;
				case 3:
					aiDecision.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
					npc.m_Defending = true;
					break;
				case 4:
					aiDecision.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
					currentCooldown = aiDecisionCooldown;
					break;
				case 5:
					aiDecision.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
					currentCooldown = aiDecisionCooldown;
					break;
				default:
					aiDecision.setCurrent(gpp::Events::Event::NONE);
					break;
				}

				// Execution
				npc.handleInput(aiDecision);
				npc.m_Turn = false;
				player.m_Turn = true;
			}
		}

			npc.handleInput(ai);

				npc.getAnimatedSprite().setScale(-1.0f, 1.0f);
				npc.getAnimatedSprite().setPosition(750.0f, 0.0f);
		

		// Update the Player
			if (player.m_Health <= 0) {
				player.m_Health = 0;
				m_PlHealth.setString("HEALTH = " + std::to_string(player.m_Health));
				input.setCurrent(gpp::Events::Event::DIED_EVENT);

				m_Gameover.setString("YOU LOSE");
				m_Gameover.setPosition(400.0f, 100.0f);
			}

            player.update();

			if (player.m_Attacking == true || player.m_Shooting == true)
			{
				m_PlCoLocation.x += 1.0f;
				m_PlCollider.setPosition(m_PlCoLocation);
				if (player.m_Shooting == true)
				{
					if (!m_Kunai_texture.loadFromFile(m_Kunai)) {
						std::cout << "ERROR with Kunai" << std::endl;
					}
					m_Kunai_sprite.setTexture(m_Kunai_texture);
					m_Kunai_sprite.setRotation(90.0f);
					m_Kunai_sprite.setPosition(m_PlCoLocation);
				}

				// Update the position of the player's collider before collision detection
				PlayerCollison.p = c2V(m_PlCoLocation.x, m_PlCoLocation.y);

				// Perform collision detection after updating the player's position
				collison = c2CircletoAABB(PlayerCollison, aabb_npc);

				if (collison || m_PlCoLocation.x >= 1000)
				{
					m_PlCoLocation = sf::Vector2f{ 175.0f, 230.0f };
					m_PlCollider.setPosition(m_PlCoLocation);
					
					if (collison)
					{
						if (player.m_Attacking == true)
						{
							if (npc.m_Defending == false)
							{
								npc.m_Health = npc.m_Health - 20;
							}
						}
						if (player.m_Shooting == true)
						{
							if (npc.m_Defending == false) {
								npc.m_Health = npc.m_Health - 10;
							}
						}
						m_EnHealth.setString("HEALTH = " + std::to_string(npc.m_Health));
					}
					player.m_Attacking = false;
					player.m_Shooting = false;
					player.m_Turn = false;
					player.m_Defending = false;
					npc.m_Turn = true;
				}
			}
		
		
		// Update the NPC
		npc.update();
		if (npc.m_Health <= 0) {
			npc.m_Health = 0;
			m_EnHealth.setString("HEALTH = " + std::to_string(npc.m_Health));
			ai.setCurrent(gpp::Events::Event::DIED_EVENT);
			m_Gameover.setString("YOU WIN");
			m_Gameover.setPosition(400.0f, 100.0f);

		}

		if (npc.m_Attacking == true || npc.m_Shooting == true)
		{
			m_EnCoLocation.x -= 1.0f;
			m_EnCollider.setPosition(m_EnCoLocation);
			if (npc.m_Shooting == true)
			{
				if (!m_Kunai_texture.loadFromFile(m_Kunai)) {
					std::cout << "ERROR with Kunai" << std::endl;
				}
				m_Kunai_sprite.setTexture(m_Kunai_texture);
				m_Kunai_sprite.setScale(1.0f, -1.0f);
				m_Kunai_sprite.setPosition(m_EnCoLocation);
			}

			// Update the position of the player's collider before collision detection
			EnemyCollison.p = c2V(m_EnCoLocation.x, m_EnCoLocation.y);

			// Perform collision detection after updating the player's position
			collison2 = c2CircletoAABB(EnemyCollison, aabb_player);

			if (collison2 || m_EnCoLocation.x <= 0)
			{
				m_EnCoLocation = sf::Vector2f{ 610.0f,230.0f };
				m_EnCollider.setPosition(m_EnCoLocation);

				if (collison2)
				{
					if (npc.m_Attacking == true)
					{
						if (player.m_Defending == false) {
							player.m_Health = player.m_Health - 20;
						}
					}
					if (npc.m_Shooting == true)
					{
						if (player.m_Defending == false) {
							player.m_Health = player.m_Health - 10;
						}
					}
					m_PlHealth.setString("HEALTH = " + std::to_string(player.m_Health));
				}
				npc.m_Attacking = false;
				npc.m_Shooting = false;
				npc.m_Turn = false;
				npc.m_Defending = false;
				player.m_Turn = true;
			}
		}
		

		

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprites & info
		
			if (m_Graphics == false)
			{
				window.draw(m_playerBody);
				window.draw(m_PlCollider);
			}
			if (m_Graphics == true)
			{
				window.draw(player.getAnimatedSpriteFrame());
				if (!collison && player.m_Shooting == true)
				{
					window.draw(m_Kunai_sprite);
				}
			}
		
		window.draw(m_PlHealth);

		// Draw the NPC's Current Animated Sprites & info
		
			if (m_Graphics == false)
			{
				window.draw(m_enemyBody);
				window.draw(m_EnCollider);
			}

			if (m_Graphics == true)
			{
				window.draw(npc.getAnimatedSpriteFrame());
			}
		
		window.draw(m_EnHealth);

		//Draw the Game Ui
		window.draw(m_Attack);
		window.draw(m_Throw);
		window.draw(m_Dodge);
		if (npc.m_Health <= 0 || player.m_Health <= 0) {
			window.draw(m_Gameover);
		}
               
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};

