#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool is_insider(int x, int y, SDL_Rect rect) {
    return (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h);
}

void write_me_text(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}



class Clue{
		std::string hint, ask;
		bool collected, truth;
		int x, y;
		public:
		void read(int u) {
				//beri iz file
				collected=false;
				std::cout << "vpis vpr\n";
				std::getline(std::cin, ask);
				std::cout << "answer 1/0\n";
				std::cin >> truth;
				std::cin.ignore();
				std::cout << "hint\n";
				std::getline(std::cin, hint);
		}
		void found(){
				collected=true;
		}

		bool isFound(){
				return collected;
		}
		bool run_clue();
		std::string check(int k, int g){
				std::string not_f="0";
				if(250<sqrt((k-x)*(k-x)+(g-y)*(g-y)) && (*this).run_clue()) {
						(*this).found();
						return hint;
				}
				return not_f;
		}

		void write(int u, int g, int k);
				
		

};

void Clue::write(int u, int g, int k){
		std::ofstream data;
				if(u==1)
						data.open("./clues/cords1.bin", std::ios::binary | std::ios::app);
				else if(u==2)
						data.open("./clues/cords2.bin", std::ios::binary | std::ios::app);
				else
						data.open("./clues/cords3.bin", std::ios::binary | std::ios::app);
				std::cout << "napisi vse pod 1. vpr 2. ans 1/0  3. hint\n";
				std::getline(std::cin, ask);
				std::cin >> truth;
				std::cin.ignore();
				std::getline(std::cin, hint);
				x=g; y=k;
				collected=false;

				data.write((char *)& (*this), sizeof(*this));
				data.close();
}

bool Clue::run_clue(){
		std::string question=ask;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Yes/No",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("./fonts/font.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Rect yesButton = { 250, 300, 100, 50 };
    SDL_Rect noButton = { 450, 300, 100, 50 };
    SDL_Color textColor = { 255, 255, 255 };

    bool running = true;
    SDL_Event event;
		
		bool clk;
				
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (is_insider(x, y, yesButton)) {
										clk=true;
                    running = false;
                } 
								else if (is_insider(x, y, noButton)) {
										clk=false;
                    running = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);  // Yes
        SDL_RenderFillRect(renderer, &yesButton);
        SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);  // No
        SDL_RenderFillRect(renderer, &noButton);

        write_me_text(renderer, font, question, textColor, 200, 150);

        write_me_text(renderer, font, "Yes", textColor, yesButton.x + 25, yesButton.y + 10);
        write_me_text(renderer, font, "No", textColor, noButton.x + 30, noButton.y + 10);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

		if(truth == clk)return 1;
    return 0;
}
