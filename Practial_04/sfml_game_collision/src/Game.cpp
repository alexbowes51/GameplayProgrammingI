#include <./include/Game.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

using namespace sf;

#define CUTE_C2_IMPLEMENTATION
#include <./include/cute_c2.h>

sf::RenderWindow* window = new RenderWindow(sf::VideoMode(800, 600), "Launching...");


sf::Texture player_texture;
sf::Texture npc_texture;

sf::Sprite player_sprite;
sf::Sprite npc_sprite;



//Make a RectShape 100x100
sf::RectangleShape player_rect(sf::Vector2f(100, 100));
//Make a RectShape 100X100
sf::RectangleShape npc_rect(sf::Vector2f(100, 100));
//Make a Circle R=50
sf::CircleShape npc_cir(50);
//Make a Circle R=50
sf::CircleShape player_cir(50);
//Make a caspule S=R,20 M=40x80 E=R,20
sf::CircleShape npc_C_S(20);
sf::RectangleShape npc_C_M(sf::Vector2f(80, 40));
sf::CircleShape npc_C_E(20);



Game::Game(){}

void Game::initialize()
{
	//making new GameObjects
	player = new Player();
	npc = new NPC();
	npc_Cir = new NPC();
	player_Cir = new Player();
	npc_Pill_1 = new NPC();
	npc_Pill_2 = new NPC();
	npc_Pill_3 = new NPC();

	window->setSize(sf::Vector2u(640, 480));
	window->setTitle("Game");

	player->x = 0;
	player->y = 0;

	npc->x = 0;
	npc->y = 0;

	npc_Cir->x = 400;
	npc_Cir->y = 300; 
	

	player_Cir->x = 590;
	player_Cir->y = 200;
	

	npc_Pill_1->x = 200;
	npc_Pill_1->y = 450;
	

	npc_Pill_2->x = 210;
	npc_Pill_2->y = 450;

	npc_Pill_3->x = 270;
	npc_Pill_3->y = 450;
	
	


	player_texture.loadFromFile(".//images//player//Player.png");
	npc_texture.loadFromFile(".//images//npc//npc.png");
	

	player_sprite.setTexture(player_texture);
	npc_sprite.setTexture(npc_texture);
	
	//setting player_rect to player cords
	player_rect.setPosition(player->x, player->y);
	player_rect.setFillColor(sf::Color::Green);

	//setting npc_rect to npc cords
	npc_rect.setPosition(npc->x, npc->y);
	npc_rect.setFillColor(sf::Color::Blue);

	//setting npc_cir to npc_Cir cords 
	npc_cir.setPosition(npc_Cir->x, npc_Cir->y);
	npc_cir.setFillColor(sf::Color::Yellow);

	//setting up player_cir to player_Cir cords
	player_cir.setPosition(player_Cir->x, player_Cir->y);
	player_cir.setFillColor(sf::Color::Blue);

	//setting up Npc_c Capsule cords
	npc_C_S.setPosition(npc_Pill_1->x, npc_Pill_1->y);
	npc_C_S.setFillColor(sf::Color::Yellow);
	npc_C_M.setPosition(npc_Pill_2->x, npc_Pill_2->y);
	npc_C_M.setFillColor(sf::Color::Yellow);
	npc_C_E.setPosition(npc_Pill_3->x, npc_Pill_3->y);
	npc_C_E.setFillColor(sf::Color::Yellow);



}

void Game::run()
{
	initialize();

	while (window->isOpen())
	{
		update();
		draw();
	}
}

void Game::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		//Input for Rect
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				player_rect.move(5.0f, 0.0f);
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				player_rect.move(-5.0f, 0.0f);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				player_rect.move(0.0f, 5.0f);
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				player_rect.move(0.0f, -5.0f);
			}

			//Input for circle
			if (event.key.code == sf::Keyboard::D)
			{
				player_cir.move(5.0f, 0.0f);
			}
			if (event.key.code == sf::Keyboard::A)
			{
				player_cir.move(-5.0f, 0.0f);
			}
			if (event.key.code == sf::Keyboard::S)
			{
				player_cir.move(0.0f, 5.0f);
			}
			if (event.key.code == sf::Keyboard::W)
			{
				player_cir.move(0.0f, -5.0f);
			}
		   
		}

		//updates GameObjects indivually
		player->update();
		npc->update();
		npc_Cir->update();
		npc_Pill_1->update();
		npc_Pill_2->update();
		npc_Pill_3->update();
		

		//Setup NPC AABB
		c2AABB aabb_npc;
		aabb_npc.min = c2V(npc_rect.getPosition().x, npc_rect.getPosition().y);
		aabb_npc.max = c2V(
			npc_rect.getPosition().x +
			npc_rect.getGlobalBounds().width, 
			npc_rect.getPosition().y +
			npc_rect.getGlobalBounds().height);
			
		//Setup Player AABB
		c2AABB aabb_player;
		aabb_player.min = c2V(player_rect.getPosition().x,player_rect.getPosition().y);
    	aabb_player.max = c2V(player_rect.getGlobalBounds().width, player_rect.getGlobalBounds().height);

		//Setup NPC Circle
		c2Circle Circle_Npc;
		Circle_Npc.p = c2V(npc_cir.getPosition().x, npc_cir.getPosition().y);
		Circle_Npc.r = npc_cir.getRadius();

		//Setup Player Circle 
		c2Circle Circle_player;
		Circle_player.p = c2V(player_cir.getPosition().x, player_cir.getPosition().y);
		Circle_player.r = player_cir.getRadius();

		// Setup NPC Capsule
		c2Capsule capsule_npc;
		capsule_npc.a = c2V(npc_C_S.getPosition().x, npc_C_S.getPosition().y);
		capsule_npc.b = c2V(npc_C_E.getPosition().x, npc_C_E.getPosition().y);
		capsule_npc.r = npc_C_M.getSize().x / 2.0f;

		//making bools out of the collisions there set to true by default 
		
		
		bool collisionCircle = c2CircletoAABB(Circle_Npc, aabb_player);
		bool collisonCircle2 = c2CircletoCircle(Circle_Npc, Circle_player);

        bool collisionAABB = c2AABBtoAABB(aabb_npc, aabb_player);
		bool collisonAABB2 = c2CircletoAABB(Circle_player, aabb_npc);

		bool collisionCapsule = c2CircletoCapsule(Circle_player, capsule_npc);
		


		//if Collison Rect to Rect
		if (collisionAABB)
		{
			std::cout << " Player_rect Collision with npc_rect" << std::endl;
			player_rect.setFillColor(sf::Color::Magenta);
			npc_rect.setFillColor(sf::Color::Red);
		}
		else if (collisionCircle) //if Collison Rect to Circle
		{
			std::cout << "Player_rect Collison with npc_cir" << std::endl;
			player_rect.setFillColor(sf::Color::Yellow);
			npc_cir.setFillColor(sf::Color::Red);
		}
		else if (collisonCircle2)
		{
			std::cout << "Player_Cir Collison with npc_cir" << std::endl;
			player_cir.setFillColor(sf::Color::Red);
			npc_cir.setFillColor(sf::Color::Red);

		}
		else if (collisonAABB2)
		{
			std::cout << "Player_cir Collison with npc_rect" << std::endl;
			player_cir.setFillColor(sf::Color::Red);
			npc_rect.setFillColor(sf::Color::Red);
		}
		else if (collisionCapsule)
		{
			std::cout << "Player_cir Collision with npc_capsule" << std::endl;
			player_cir.setFillColor(sf::Color::Red);
			npc_C_S.setFillColor(sf::Color::Red);
			npc_C_M.setFillColor(sf::Color::Red);
			npc_C_E.setFillColor(sf::Color::Red);
		}
		else if (!collisionAABB || !collisionCircle || !collisonAABB2 || !collisonCircle2 || !collisionCapsule)//if no Collison with any object 
		{
			std::cout << "No Collision" << std::endl;
			player_rect.setFillColor(sf::Color::Green);
			npc_cir.setFillColor(sf::Color::Yellow);
			npc_rect.setFillColor(sf::Color::Blue);
			player_cir.setFillColor(sf::Color::Blue);
			npc_C_S.setFillColor(sf::Color::Yellow);
			npc_C_M.setFillColor(sf::Color::Yellow);
			npc_C_E.setFillColor(sf::Color::Yellow);

		}
	}
	
}

void Game::draw()
{
	window->clear();
	//draws GameObjects 
	window->draw(player_rect);
	window->draw(npc_rect);
	window->draw(npc_cir);
	window->draw(player_cir);
	window->draw(npc_C_S);
	window->draw(npc_C_M);
	window->draw(npc_C_E);
	//player->draw();
	//npc->draw();
	window->display();
}


