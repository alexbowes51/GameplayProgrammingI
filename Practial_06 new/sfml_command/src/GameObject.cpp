#include <./include/GameObject.h>

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

void GameObject::initialize(String image){
	if (!texture.loadFromFile(image + ".png"))
	{
		std::cout << "Image file not found";
	}
	sprite.setTexture(texture); 
	sprite.setPosition(sf::Vector2f(position.x, position.y));
	
}

void GameObject::update()
{
	sprite.setPosition(this->position);
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void GameObject::setPosition(Vector2f position)
{
	this->position = position;
}

Vector2f GameObject::getPosition()
{
	return this->position;
}

void GameObject::moveUp()
{
	this->position.y -= 5;
	Direction = 1;
}

void GameObject::moveDown()
{
	this->position.y += 5;
	Direction = 2;
}

void GameObject::moveLeft()
{
	this->position.x -= 5;
	Direction = 3;
}

void GameObject::moveRight()
{
	this->position.x += 5;
	Direction = 4;
}

//my code
void GameObject::Jump()
{
	this->position.y -= 10;
	std::cout << "Player is jumping" << std::endl;
}

void GameObject::Dash()
{
	if (Direction == 3) {
		this->position.x -= 10;
		std::cout << "Player is Dashing left" << std::endl;
   }
	if (Direction == 4) {
		this->position.x += 10;
		std::cout << "Player is Dashing right" << std::endl;
	}
}

void GameObject::Teleport()
{
	srand((unsigned)time(0));
	int X;
	int Y;
	X = (rand() & 800) + 1;
	Y = (rand() & 600) + 1;

	this->position.x = X;
	this->position.y = Y;

	std::cout << "WHAT where am i ??" << std::endl;
	std::cout << "Player Teleported" << std::endl;
}

void GameObject::crouch()
{
	this->position.y += 5;

	std::cout << "Player is crouching :)" << std::endl;
}

void GameObject::attacking()
{
	this->position.x += 5;
	this->position.x -= 5;

	std::cout << "Player is attacking" << std::endl;
}

