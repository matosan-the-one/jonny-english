#include "player.h"
#include <cstring>

using std::vector;

Player::Player(int g, int k, char im[20]){
		hp=100;
		// cout << "vpisi ime:\n";
		// cin >> ime;
		if(!strcmp( ime, "jonny")){
				dmg = 50;
		}
		else {
				dmg = 10;
		}
		x=g;
		y=k;
}

void Player::show(SDL_Renderer *ren) {
		SDL_Rect rand;
		rand.x=x;
		rand.y=y;
		rand.w=20;
		rand.h=20;
    SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(ren, &rand );
}
