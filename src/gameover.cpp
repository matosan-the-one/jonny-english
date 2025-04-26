#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void game_over(const char name[], float &score) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        SDL_Log("Failed to initialize SDL or SDL_ttf: %s", SDL_GetError());
        return;
    }

    SDL_Window* window = SDL_CreateWindow("End Game Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* fontLarge = TTF_OpenFont("fonts/font.ttf", 48); // Replace with a valid path to a .ttf file
    TTF_Font* fontSmall = TTF_OpenFont("fonts/font.ttf", 24);

    if (!fontLarge || !fontSmall) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color red = {255, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
        SDL_RenderClear(renderer);

        // Render "GAME OVER"
        renderText(renderer, fontLarge, "GAME OVER", red, 180, 100);

        // Render username
        std::string nameText = std::string("Player: ") + name;
        renderText(renderer, fontSmall, nameText, white, 200, 200);
				nameText = "maybe try a name that starts with jonny";
				renderText(renderer, fontSmall, nameText, white, 100, 300);
        // Render score
        std::stringstream ss;
        ss << "Score: " << score;
        renderText(renderer, fontSmall, ss.str(), white, 200, 250);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(fontLarge);
    TTF_CloseFont(fontSmall);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

