#ifndef GAME_H
#define GAME_H

#include <./include/Player.h>
#include <./include/NPC.h>

class Game
{
	public:
		Game();
		void run();
	private:
		void initialize();
		void update();
		void draw();
		Player* player;
		Player* player_Cir;
		NPC* npc;
		NPC* npc_Cir;
		NPC* npc_Pill_1;
		NPC* npc_Pill_2;
		NPC* npc_Pill_3;

};

#endif