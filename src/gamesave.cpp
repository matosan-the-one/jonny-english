#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "player.h"


bool check_cont(){
		std::ifstream data("player_log/continue/ses.txt");
        if(!data)
            std::cout << "no player continue\n\n";
		int sum;
		data >> sum;
		if(sum==1 || sum==2 || sum==3)return true;
		return false;
}

int get_inst(){
		std::ifstream data("player_log/continue/ses.txt");
        if(!data)
            std::cout << "no player continue\n\n";
		int sum;
		data >> sum;
		return (sum-1);
}

std::string get_inst_c(){
		std::ifstream data("player_log/continue/ses.txt");
        if(!data)
            std::cout << "no player continue\n\n";
		int sum;
		char tab[20];
		data >> sum >> tab;
		return tab;
}
