#ifndef CONCRETE_COMMANDS_H
#define CONCRETE_COMMANDS_H

#include <./include/Command.h>

class MoveUpCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveUp();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveUpCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveDownCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveDown();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveDownCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveLeftCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveLeft();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveLeftCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveRightCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveRight();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveRightCommand(*this);
	}

private:
	Vector2f previous;
};

//my code
class Jump : public Command
{
public:
	virtual void execute(GameObject* gameobject) {
		previous = gameobject->getPosition();
		gameobject->Jump();
	}
	virtual void undo(GameObject* gameobject) {
		gameobject->setPosition(previous);
	}
	Command* copy() {
		return new Jump(*this);
	}
private:
	Vector2f previous;
};

class Dash : public Command
{
public:
	virtual void execute(GameObject* gameobject) {
		previous = gameobject->getPosition();
		gameobject->Dash();
	}
	virtual void undo(GameObject* gameobject) {
		gameobject->setPosition(previous);
	}
	Command* copy() {
		return new Dash(*this);
	}
private:
	Vector2f previous;
};

class Teleport : public Command
{
public:
	virtual void execute(GameObject* gameobject) {
		previous = gameobject->getPosition();
		gameobject->Teleport();
	}
	virtual void undo(GameObject* gameobject) {
		gameobject->setPosition(previous);
	}
	Command* copy() {
		return new Teleport(*this);
	}
private:
	Vector2f previous;
};

class Crouch : public Command
{
public:
	virtual void execute(GameObject* gameobject) {
		previous = gameobject->getPosition();
		gameobject->crouch();
	}
	virtual void undo(GameObject* gameobject) {
		gameobject->setPosition(previous);
	}
	Command* copy() {
		return new Crouch(*this);
	}
private:
	Vector2f previous;
};


class Attacking : public Command
{
public:
	virtual void execute(GameObject* gameobject) {
		previous = gameobject->getPosition();
		gameobject->attacking();
	}
	virtual void undo(GameObject* gameobject) {
		gameobject->setPosition(previous);
	}
	Command* copy() {
		return new Attacking(*this);
	}
private:
	Vector2f previous;
};

#endif // !CONCRETE_COMMANDS_H