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
	m_Attack.setFillColor(sf::Color::White);
	m_Attack.setOutlineThickness(2.5f);
	m_Attack.setOutlineColor(sf::Color::Black);

}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "NINJA FIGHT CLUB");

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

	//Setup Player Collidor
	c2Circle PlayerCollison;
	PlayerCollison.p = c2V(m_PlCollider.getPosition().x, m_PlCollider.getPosition().y);
	PlayerCollison.r = m_PlCollider.getRadius();

	//Setup NPC AABB
	c2AABB aabb_npc;
	aabb_npc.min = c2V(m_enemyBody.getPosition().x, m_enemyBody.getPosition().y);
	aabb_npc.max = c2V(
		m_enemyBody.getPosition().x +
		m_enemyBody.getGlobalBounds().width,
		m_enemyBody.getPosition().y +
		m_enemyBody.getGlobalBounds().height);

	bool collison = c2CircletoAABB(PlayerCollison, aabb_npc);

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
				if (player.m_Turn == true){
				     if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
						std::cout << "Player is attacking" << std::endl;
						player.m_Attacking = true;
					}
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						 input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
						 std::cout << "Player is throwing" << std::endl;
						 player.m_Shooting = true;
					 }
					 if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						 input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
						 std::cout << "Player is Jumping" << std::endl;
					 }

				}
			break;
	
				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::G) {
					m_Graphics = true;
					std::cout << "Graphics on" << std::endl;
				}
				if (player.m_Turn == true){
					if (event.key.code == sf::Keyboard::A) {
						input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
						std::cout << "Stopping Player attacking" << std::endl;
						player.m_Attacking = true;
					}
					if (event.key.code == sf::Keyboard::S) {
						input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
						std::cout << "Stopping Player Throwing" << std::endl;
					}
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
       

		if (npc.m_Health >= 0)
		{
			if (npc.m_Turn == true) {
				int weapon = rand() % 2 + 1;

				switch (weapon)
				{
				case 1:
					ai.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
					break;
				case 2:
					ai.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
					break;
				case 3:
					ai.setCurrent(gpp::Events::Event::THROW_START_EVENT);
					break;
				case 4:
					ai.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
					break;
				default:
					ai.setCurrent(gpp::Events::Event::NONE);
					break;
				}

				npc.handleInput(ai);
			}
		}
		npc.getAnimatedSprite().setScale(-1.0f, 1.0f);
		npc.getAnimatedSprite().setPosition(800.0f, 0.0f);
		

		// Update the Player
		if (player.m_Health >= 0)
		{
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
					player.m_Attacking = false;
					player.m_Shooting = false;
					if (collison)
					{
						npc.m_Health = npc.m_Health - 20;
						m_EnHealth.setString("HEALTH = " + std::to_string(npc.m_Health));
					}
				}
			}
		}
		
		// Update the NPC
		if (npc.m_Health >= 0)
		{
			npc.update();
		}

		

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprites & info
		if (player.m_Health >= 0)
		{
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
		} 
		window.draw(m_PlHealth);

		// Draw the NPC's Current Animated Sprites & info
		if (npc.m_Health >= 0)
		{
			if (m_Graphics == false)
			{
				window.draw(m_enemyBody);
			}

			if (m_Graphics == true)
			{
				window.draw(npc.getAnimatedSpriteFrame());
			}
		}
		window.draw(m_EnHealth);

		//Draw the Game Ui
		window.draw(m_Attack);	
               
		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};

