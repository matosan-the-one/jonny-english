#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

bool is_insider(int x, int y, SDL_Rect rect);
void write_me_text(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);

class Clue{
		std::string hint, ask;
		bool  collected, truth;
		int x, y;
		public:
		void read();
		void found();
		bool isFound();
		bool check(int k, int g);
		void write(int , int , int );
		bool run_clue();
};

std::vector<Clue> read_clues(int u);
