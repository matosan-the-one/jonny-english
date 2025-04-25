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

bool Player::can_see(int x_p, int y_p){
		double dx = x_p - x;
    double dy = y_p - y;
    double distance = std::sqrt(dx * dx + dy * dy);

    int steps = distance / 0.5;  // Smaller step = more accurate

    double stepX = dx / steps;
    double stepY = dy / steps;

    double x_s = x;
    double y_s = y;

    for (int i = 0; i <= steps; i++) {
        if (!check_valid((int)x_s, (int)y_s)) {
            return false; // Hit a wall
        }
        x_s += stepX;
        y_s += stepY;
    }

    return true;	
			
}

void Player::move(int x_p, int y_p) {
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(0, 399); // Random int from 0 to 100
    if(x<0||y<0)return;
		
		if(250>sqrt(pow((x_p+10-x) , 2)+ pow((y_p+10-y) , 2))){
				int a, b;

				a=(x_p+10)-(x+20);
				b=(y_p+10)-(y+20);

				a = std::max(-5, std::min(5, a));
				b = std::max(-5, std::min(5, b));
				if((*this).can_see(x_p, y_p)){
						x+=a;
						y+=b;
						return;
				}

		}


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

int Player::get_hp(){
		return hp;
}

int Player::get_dmg(){
		return dmg;
}

const char * Player::get_ime(){
		return ime;
}
