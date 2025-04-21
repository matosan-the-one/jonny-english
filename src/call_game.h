#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y);
bool isInside(int x, int y, SDL_Rect rect);
int menu();
void game();
