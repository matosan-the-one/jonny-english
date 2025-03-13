#include <fstream>
#include <vector>
#include "ball.h"

void maps(std::vector <Line> buf, int n, int si){
	std::ofstream data("./file_dump/walls");	
	for(auto const &x : buf){
		data << x.x1 << ","<< x.y1 << "," << x.x2 << "," << x.y2 << "\n";  	
	}
	data.close();
}

