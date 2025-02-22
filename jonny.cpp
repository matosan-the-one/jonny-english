#include <cmath>
#include <ctime>
#include <vector>
#include <cstring>
#include <iostream>

using std::cout;
using std::cin;
using std::vector;

class Player{
		int hp, dmg;
		char ime[20];
		vector <int> xcord;
		vector <int> ycord;
public:
		void vpis();
		void izpis();

};	

int main() {
		Player a;
		a.vpis();
		a.izpis();
		return 0;
}

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
