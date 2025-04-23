#include <fstream>
#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;

struct pla{
		int sc;
		char im[20];
};

void wr_lead(int score, const char ime[]){
		ifstream data("player_log/leaderboard/top.bin", std::ios::binary);
		pla h;
		h.sc=score;
		strcpy(h.im, ime);
		
		data.close();
}
