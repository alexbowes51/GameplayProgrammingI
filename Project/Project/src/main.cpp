#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Events.h>
#include <Debug.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Player Finite State Machine");

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

	//Players varibles/shapes
	sf::RectangleShape m_playerBody(sf::Vector2f(100, 200));
	m_playerBody.setPosition(75, 150);
	m_playerBody.setFillColor(sf::Color::Green);
	Player player(player_animated_sprite);
	player.m_Health = 100;
	player.m_Turn = true;




	sf::RectangleShape m_enemyBody(sf::Vector2f(100, 200));
	m_enemyBody.setPosition(750,150);
	m_enemyBody.setFillColor(sf::Color::Red);
	Player npc(player_animated_sprite);
	npc.m_Turn = false;
	npc.m_Health = 100;
	


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
		npc.getAnimatedSprite().setPosition(900.0f, 0.0f);
		

		// Update the Player
		if (player.m_Health >= 0)
		{
			player.update();
		}
		
		// Update the NPC
		if (npc.m_Health >= 0)
		{
			npc.update();
		}

		// Clear screen
		window.clear();

		// Draw the Players Current Animated Sprite
		if (player.m_Health >= 0)
		{
			if (m_Graphics == false)
			{
				window.draw(m_playerBody);
			}
			if (m_Graphics == true)
			{
				window.draw(player.getAnimatedSpriteFrame());
			}
		}

		// Draw the NPC's Current Animated Sprite
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

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};