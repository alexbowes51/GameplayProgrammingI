#ifndef PLAYER_H
#define PLAYER_H
#include <Events.h>
#include <PlayerState.h>
#include <AnimatedSprite.h>
#include <stdio.h>
#include <IdlePlayerState.h>



class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;

public:
	Player(const AnimatedSprite&);
	~Player();
	bool m_Turn; 
	bool m_Attacking;
	bool m_Shooting;
	bool m_Defending;
	int m_Health;
	
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
};
#endif

