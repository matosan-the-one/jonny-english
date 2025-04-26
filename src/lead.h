#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void wr_lead(float score, const char ime[]);
void leader();
void renderTextlead(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);

