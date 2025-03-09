#include <SDL2/SDL.h>
#include <vector>
#include <cmath>


extern std::vector<float> a;
extern std::vector<float> n; 
extern std::vector<float> lim1x;
extern std::vector<float> lim2x;
extern std::vector<float> lim1y;
extern std::vector<float> lim2y;
void add_obstacle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
bool check_valid(int x, int y);
bool ball_valid(int x, int y);
