#include <fstream>
#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;

struct pla{
		int sc;
		char im[20];
};

void renderTextlead(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void wr_lead(float score, const char ime[]){
		ifstream data("player_log/leaderboard/top.bin", std::ios::binary);
		ofstream datao("player_log/leaderboard/new.bin", std::ios::binary);
		pla h, g;
		h.sc=score;
		strcpy(h.im, ime);
		bool ins=0;
		int w=0;
		while(data.read((char *)&g, sizeof(g))){
				if(h.sc>g.sc && !ins){
						datao.write((char *)&h, sizeof(h));
						ins=1;
						w++;
				}	
				datao.write((char *)&g, sizeof(g));
				w++;
		}
		if(!ins && w<5){
				datao.write((char *)&h, sizeof(g));
		}

		datao.close();
		data.close();
		remove("player_log/leaderboard/top.bin");
		rename("player_log/leaderboard/new.bin", "player_log/leaderboard/top.bin");
}

void leader() {
		std::ifstream data("player_log/leaderboard/top.bin", std::ios::binary);
    std::vector<pla> players;
    pla g;
    while (data.read((char*)&g, sizeof(g))) {
        players.push_back(g);
    }
    data.close();

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        SDL_Log("Failed to initialize SDL or SDL_ttf: %s", SDL_GetError());
        return;
    }

    SDL_Window* window = SDL_CreateWindow("Leaderboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* fontTitle = TTF_OpenFont("fonts/font.ttf", 48);
    TTF_Font* fontText = TTF_OpenFont("fonts/font.ttf", 24);

    if (!fontTitle || !fontText) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderTextlead(renderer, fontTitle, "LEADERBOARD", yellow, 160, 30);

        // Render each player
        int startY = 120;
        for (size_t i = 0; i < players.size(); ++i) {
            std::string line = std::to_string(i + 1) + ". " + players[i].im + " - " + std::to_string(players[i].sc);
            renderTextlead(renderer, fontText, line, white, 150, startY + i * 50);
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(fontTitle);
    TTF_CloseFont(fontText);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

