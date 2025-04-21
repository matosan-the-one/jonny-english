#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"

const int SCREEN_WIDTH_1 = 800;
const int SCREEN_HEIGHT_1 = 600;


bool isInside(int x, int y, SDL_Rect rect);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y);
int menu();
void game();

void game() {
		int h=menu();
		if(!h){
				int inst=0;
				if(game_window(inst))
						if(game_window(inst+1))
								if(game_window(inst+2)){
										// win();
										// continue();
								}
		}
		else if(h==2){
				// leader board
		}
		else {
				/*
						if(have_game_save()){
								// continue from here
						}
						else{
								game();
						}
				*/
		}
}

int menu() {
		SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
		int choice=0;
    SDL_Window* window = SDL_CreateWindow("Menu with Text",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH_1, SCREEN_HEIGHT_1, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load font
    TTF_Font* font = TTF_OpenFont("fonts/font.ttf", 24); // Make sure Arial.ttf is in the same folder
    if (!font) {
        return -1;
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
                    running = false;
										choice=0;
                }
								else if (isInside(x, y, leaderboardBtn)) {
                    running = false;
										choice=2;
                }
								else if (isInside(x, y, continueBtn)) {
                    running = false;
										choice=1;	
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
        renderText(renderer, font, "continue", textColor, continueBtn.x + 60, continueBtn.y + 10);

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


