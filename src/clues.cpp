#include <iostream>
#include <vector>
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

void write_me_text(SDL_Renderer* ren_clue, TTF_Font* font_clue, const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font_clue, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren_clue, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(ren_clue, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}



class Clue{
		std::string hint, ask;
		bool collected, truth;
		int x, y;
		public:
		void read(int u);
				
		void found(){
				collected=true;
		}

		bool isFound();
		
		bool run_clue();
		

		std::vector<Clue> read_clues(int u);
		void check(int k, int g);
		void write(int u, int g, int k);
				
		

};

void Clue::read(int u){
		//
}

bool Clue::isFound(){
				return collected;
}

std::vector<Clue> Clue::read_clues(int u) {
    std::ifstream data;
    if(u == 1)
        data.open("./clues/cords1.txt");
    else if(u == 2)
        data.open("./clues/cords2.txt");
    else
        data.open("./clues/cords3.txt");

    std::vector<Clue> clues;
    Clue temp;
    while (data >> temp.x >> temp.y >> temp.truth) {
        data.ignore(); // Ignore leftover newline
        std::getline(data, temp.ask);
        std::getline(data, temp.hint);
        temp.collected = false;
        clues.push_back(temp);
    }

    data.close();
    return clues;
}


void Clue::check(int k, int g){
				if(250>sqrt((k-x)*(k-x)+(g-y)*(g-y)) && (*this).run_clue()) {
						(*this).found();
				}
}

void Clue::write(int u, int g, int k){
    std::ofstream data;
    if(u==1)
        data.open("./clues/cords1.txt", std::ios::app);
    else if(u==2)
        data.open("./clues/cords2.txt", std::ios::app);
    else
        data.open("./clues/cords3.txt", std::ios::app);

    std::cout << "Enter question:\n";
    std::getline(std::cin, ask);
    std::cout << "Enter truth (1 or 0):\n";
    std::cin >> truth;
    std::cin.ignore();
    std::cout << "Enter hint:\n";
    std::getline(std::cin, hint);

    x = g;
    y = k;
    collected = false;

    data << x << ' ' << y << ' ' << truth << '\n' << ask << '\n' << hint << '\n';
    data.close();
}


bool Clue::run_clue(){
		std::string question=ask;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window_clue = SDL_CreateWindow("Yes/No",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* ren_clue = SDL_CreateRenderer(window_clue, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font_clue = TTF_OpenFont("./fonts/font.ttf", 28);
    if (!font_clue) {
        std::cerr << "Failed to load font_clue: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Rect yes_button = { 250, 300, 100, 50 };
    SDL_Rect no_button = { 450, 300, 100, 50 };
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

                if (is_insider(x, y, yes_button)) {
										clk=true;
                    running = false;
                } 
								else if (is_insider(x, y, no_button)) {
										clk=false;
                    running = false;
                }
            }
        }

        SDL_SetRenderDrawColor(ren_clue, 30, 30, 30, 255);
        SDL_RenderClear(ren_clue);

        SDL_SetRenderDrawColor(ren_clue, 0, 128, 0, 255);  // Yes
        SDL_RenderFillRect(ren_clue, &yes_button);
        SDL_SetRenderDrawColor(ren_clue, 128, 0, 0, 255);  // No
        SDL_RenderFillRect(ren_clue, &no_button);

        write_me_text(ren_clue, font_clue, question, textColor, 200, 150);

        write_me_text(ren_clue, font_clue, "Yes", textColor, yes_button.x + 25, yes_button.y + 10);
        write_me_text(ren_clue, font_clue, "No", textColor, no_button.x + 30, no_button.y + 10);

        SDL_RenderPresent(ren_clue);
    }

    TTF_CloseFont(font_clue);
    SDL_DestroyRenderer(ren_clue);
    SDL_DestroyWindow(window_clue);
    TTF_Quit();
    SDL_Quit();

		if(truth == clk)return 1;
    return 0;
}
