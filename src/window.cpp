#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "globals.h"

void add_obstacle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
		// Draw the obstacle line
		if( x1 == x2 && y1 == y2)return;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		// f(x) = ax + n
		// a = (y2 - y1) / (x2 - x1)
		// n = y1 - a * x1
		if (y1 == y2) {
				a.push_back(0);
				n.push_back(y1);
		}
		else if (std::abs(x2-x1)>10) { 
				a.push_back((float)(y2 - y1) / (x2 - x1));
				if(a[a.size()-1] >= 0)
						n.push_back((y1 - a.back() * x1));
				else
						n.push_back((y1 - a.back() * x1));// -
		} 
		else {
				if((float)(y2 - y1) / (x2 - x1) > 0){
						a.push_back(10000); 
						n.push_back((-std::min(x1, x2))*10000);
				}
				else {
						a.push_back(-10000); 
						n.push_back((std::min(x1, x2))*10000);
			
				}
		}

		// Store the x and y limits for the line segment
		if (x1 > x2) {
				lim1x.push_back(x2);
				lim2x.push_back(x1);
		}
		else {
				lim1x.push_back(x1);
				lim2x.push_back(x2);
		}
		if (y1 > y2) {
				lim1y.push_back(y2);
				lim2y.push_back(y1);
		} 
		else {
				lim1y.push_back(y1);
				lim2y.push_back(y2);
		}

		int len = a.size() - 1;
		std::cout << "f(x) = " << a[len] << "x + " << n[len] << "\nlim1x = " << lim1x[lim1x.size()-1] << " lim1y = " << lim1y[lim1y.size()-1] << " lim2x = " << lim2x[lim2x.size()-1] << " lim2y = " << lim2y[lim2y.size()-1] << "\n";
}


/*
bool check_valid(int x, int y){
		// najprej glej kerim limitom se ujema
		// maybe check if perperdicular			
		// f(x) = ax +n
		// we know a is same with both
		// so we compare n-s
		// disance is |c2-c1|/sqrt(a^2+1)
		// c = n
		for(int i=0; i<a.size(); i++)	// if( x+5>=lim1x[i] && x-5<=lim2x[i] && y+5 >= lim1y[i] && y-5 <= lim2y[i] && std::abs((y - a[i]*x + n[i])) >= 5 )
				// if((std::abs(n[i]-(y-a[i]*x))/sqrt(a[i]*a[i] + 1)) > 5 && std::abs((y - a[i]*x + n[i])) >= 5 )
				if(std::abs(a[i] * x - y + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5 && std::abs((y - a[i]*x + n[i])) >= 5 ){
						if( y+5 >= lim1y[i] && y-5 <= lim2y[i])// && x <= lim2x[i] && x >= lim1x[i])
										return false;
				}
				else if(std::abs(a[i] * (x+40) - (y+40) + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5 && std::abs(((y+40) - a[i]*(x+40) + n[i])) >= 5) {
								if( y+5 >= lim1y[i] && y-5 <= lim2y[i])// && x <= lim2x[i] && x >= lim1x[i])
										return false;
				}
				else if(std::abs(a[i] * (x+40) - y + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5 && std::abs((y - a[i]*(x+40) + n[i])) >= 5) {
								if( y+5 >= lim1y[i] && y-5 <= lim2y[i])// && x <= lim2x[i] && x >= lim1x[i])
										return false;
				}
				else if(std::abs(a[i] * x - (y+40) + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5 && std::abs(((y+40) - a[i]*x + n[i])) >= 5) {
								if( y+5 >= lim1y[i] && y-5 <= lim2y[i])// && x <= lim2x[i] && x >= lim1x[i])
										return false;
				}
		return true;		
}
*/
bool check_valid(int x, int y){
		x+=10;
		y+=10;
		for (int i = 0; i < a.size(); i++) {
				// Upper left corner (x, y)
				if (y + 5 >= lim1y[i] && y - 5 <= lim2y[i] && x-5 <= lim2x[i] && x+5 >= lim1x[i])
					if (std::abs(a[i] * x - y + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5 && std::abs((y - a[i]*x + n[i])) >= 5 ) {
									return false;
					}
				
		}
		return true;
}

/*
 // Lower right corner (x+40, y+40)
				else if (std::abs(a[i] * (x + 40) - (y + 40) + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5) {
						if (y + 40 + 5 >= lim1y[i] && y + 40 - 5 <= lim2y[i])
								return false;
				}
				// Upper right corner (x+40, y)
				else if (std::abs(a[i] * (x + 40) - y + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5) {
						if (y + 5 >= lim1y[i] && y - 5 <= lim2y[i])
								return false;
				}
				// Lower left corner (x, y+40)
				else if (std::abs(a[i] * x - (y + 40) + n[i]) / std::sqrt(a[i] * a[i] + 1) < 5) {
						if (y - 40 + 5 >= lim1y[i] && y + 40 - 5 <= lim2y[i] && x - 5 <= lim2x[i] && x + 5 >= lim1x[i])
								return false;
				}
 */

bool ball_valid(int x, int y){
		x+=5;
		y+=5;
		for (int i = 0; i < a.size(); i++) {
				if (std::abs(a[i] * x - y + n[i]) / std::sqrt(a[i] * a[i] + 1) < 25 && std::abs((y - a[i]*x + n[i])) >= 5 ) {
						if (y + 30 >= lim1y[i] && y - 30 <= lim2y[i] && x-30 <= lim2x[i] && x+30 >= lim1x[i])
								return false;
				}
		}
		return true;
}

