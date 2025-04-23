#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "screen.h"
#include "gamesave.h"
#include "replay_m.h"

const int SCREEN_WIDTH_1 = 800;
const int SCREEN_HEIGHT_1 = 600;


bool isInside(int x, int y, SDL_Rect rect);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y);
int menu(std::string&name);
void game();

void game() {
		std::string ime;
		int h=menu(ime);
		if(!h){
				int inst=0;
				if(game_window(inst, ime.c_str(), 1))
						if(game_window(inst+1, ime.c_str(), 1))
								if(game_window(inst+2, ime.c_str(), 1)){
										// win();
                                        give_me_replay();
										// continue();
								}
		}
		else if(h==2){
				// leader board
		}
		else {
						if(!check_cont()){
								game_window(get_inst(), get_inst_c().c_str(), 0);
						}
						else{
								game();
						}
		}
}

int menu(std::string &name) {
		SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
		int choice=0;
    SDL_Window* window = SDL_CreateWindow("Menu with Text",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH_1, SCREEN_HEIGHT_1, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load font
    TTF_Font* font = TTF_OpenFont("fonts/font.ttf", 24); // Make sure Arial.ttf is in the same folder

    if (!font) {
				// std::cout << "fail";
        // std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Rect newGameBtn = {300, 150, 200, 50};
    SDL_Rect continueBtn = {300, 250, 200, 50};
		SDL_Rect leaderboardBtn = {300, 350, 200, 50};
   
		SDL_Color textColor = {255, 255, 255}; // White

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (isInside(x, y, newGameBtn)) {
										name.clear();
										SDL_StartTextInput();

										bool typing = true;
										SDL_Event inputEvent;

										running = false;
										while (typing) {
												while (SDL_PollEvent(&inputEvent)) {
														if (inputEvent.type == SDL_QUIT) {
																typing = false;
														} else if (inputEvent.type == SDL_KEYDOWN) {
																if (inputEvent.key.keysym.sym == SDLK_RETURN) {
																		typing = false;
																} else if (inputEvent.key.keysym.sym == SDLK_BACKSPACE && !name.empty()) {
																		name.pop_back();
																}
														} else if (inputEvent.type == SDL_TEXTINPUT) {
																// Optional: limit input length
																if (name.length() < 20) {
																		name += inputEvent.text.text;
																}
														}
												}

												// Rendering input
												SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
												SDL_RenderClear(renderer);

												SDL_Rect inputBox = {200, 250, 400, 50};
												SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
												SDL_RenderFillRect(renderer, &inputBox);

												renderText(renderer, font, "Enter your name:", textColor, 200, 200);
												if (!name.empty()) {
														renderText(renderer, font, name.c_str(), textColor, 210, 260);
												}

												SDL_RenderPresent(renderer);
										}

										SDL_StopTextInput();
								}
 
								else if (isInside(x, y, leaderboardBtn)) {
                    running = false;
										choice=1;
                }
								else if (isInside(x, y, continueBtn)) {
                    running = false;
										choice=2;	
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Draw buttons
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Button color
        SDL_RenderFillRect(renderer, &newGameBtn);
        SDL_RenderFillRect(renderer, &leaderboardBtn);
        SDL_RenderFillRect(renderer, &continueBtn);

        // Draw text labels
        renderText(renderer, font, "New Game", textColor, newGameBtn.x + 40, newGameBtn.y + 10);
        renderText(renderer, font, "Leaderboard", textColor, leaderboardBtn.x + 30, leaderboardBtn.y + 10);
        renderText(renderer, font, "Continue", textColor, continueBtn.x + 60, continueBtn.y + 10);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
		return choice;
}

bool isInside(int x, int y, SDL_Rect rect) {
    return (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h);
}

// Function to render text
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


