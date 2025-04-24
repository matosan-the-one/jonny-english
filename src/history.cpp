#include <fstream>
#include <iostream>
#include <vector> 
#include "player.h"

void history(int ses, int x1, int y1, const char ime[], std::vector <Player> tab) {
std::ofstream datap, datae;
// std::cout << "some random\n";
if(ses==0){
    datap.open("player_log/continue/play1.txt");
    datae.open("player_log/continue/bots1.txt");
}
if(ses==1){
    datap.open("player_log/continue/play2.txt");
    datae.open("player_log/continue/bots2.txt");
}
else{
    datap.open("player_log/continue/play3.txt");
    datae.open("player_log/continue/bots3.txt");
}
std::ofstream datas("player_log/continue/ses.txt");

if(!datap || !datae) {
    std::cout << "no backup history\n\n";
}

/*
std::cout<<ses+1<<" "<<ime << "\n";
std::cout<< x1 << " " << y1;
for(int i=0; i<tab.size()-1; i++)
std::cout<<tab[i].get_x() << " " <<tab[i].get_y() << " " <<tab[i].get_hp() << " " <<tab[i].get_dmg() << " " <<tab[i].get_ime() << "\n";
*/

datas<<(ses+1)<<" "<<ime << "\n";
datap << x1 << " " << y1 << "\n";
int i=0;
/*
while(datae<<tab[i].get_x() << " " <<tab[i].get_y() << " " <<tab[i].get_hp() << " " <<tab[i].get_dmg() << " " <<tab[i].get_ime() << "\n"){
    i++;
		if(i+1>tab.size())break;
}
*/
while(datae<<tab[i].get_x() << " " <<tab[i].get_y() << "\n"){
    i++;
		if(i+1>tab.size())break;
}
datae.close();
datap.close();
datas.close();

}

