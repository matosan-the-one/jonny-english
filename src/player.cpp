#include "player.h"
#include <cmath>
#include <ctime>
#include <cstring>
#include <iostream>

using std::cout;
using std::cin;
using std::vector;

void Player::vpis(){
		hp=100;
		cout << "vpisi ime:\n";
		cin >> ime;
		if(!strcmp( ime, "jonny")){
				dmg = 50;
		}
		else {
				dmg = 10;
		}
		xcord.push_back(rand()%100+0);
		ycord.push_back(rand()%100+0);
}

void Player::izpis(){
		cout << "\nizpis:\nime: " << ime << "\nhp " << hp << "\ndmg " << dmg << "\nxcord " << xcord[0] << "\nycord " << ycord[0] << "\n";
}
