#include "player.h"
#include "window.h"
#include <cstring>
#include <cmath>
#include <ctime>
#include <random>

using std::vector;

Player::Player(int g, int k, const char im[19], bool h){
        strcpy(ime, im);
		if(!strcmp( ime, "jonny")){
				dmg = 100;
                hp=1000;
		}
        else if(h){
            hp=100;
            dmg=10;
        }
		else {
				dmg = 10;
                hp = 10;
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

void Player::move() {
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(0, 399); // Random int from 0 to 100
    
    int rnd=dist(gen)/100;
    if(rnd==0){
       if(check_valid(x, y-5)) {
           y-=5;
       }
    }
    else if(rnd==1){
        if(check_valid(x, y+5)) {
           y+=5;
        }}
    else if(rnd==2){
        if(check_valid(x+5, y)) {
           x+=5;
        }}
    else {
        if(check_valid(x-5, y)) {
            x-=5;
        }
    }

}

void Player::j_clue(){
    hp+=1000;
}

int Player::collide_p(Player *smt) {
    smt->hp-=10;
    hp-=smt->dmg;
    if(smt->hp<=0) {
        return -1;
    }
    if(hp<=0) {
        return 0;
    }
    return 1;
}

int Player::get_x(){
    return x;
}

int Player::get_y(){
    return y;
}
