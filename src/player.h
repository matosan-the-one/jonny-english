#include <vector>
#include <SDL2/SDL.h>

class Player{
		int hp, dmg;
		char ime[20];
		int x, y;
public:
		void show(SDL_Renderer *ren);
		Player(int , int, const char *, bool h);
        void move();
        int get_x();
        int get_y();
				int get_hp();
				int get_dmg();
				const char * get_ime();
        int collide_p(Player *smt);
        void j_clue();
};	
