#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool isInside(int x, int y, SDL_Rect rect) {
    return (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h);
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    // Get question from user
    std::string question;
    std::cout << "Enter the question: ";
    std::getline(std::cin, question);

    // Init SDL and TTF
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Yes/No Prompt",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("./tmp/font.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Rect yesButton = { 250, 300, 100, 50 };
    SDL_Rect noButton = { 450, 300, 100, 50 };
    SDL_Color textColor = { 255, 255, 255 };

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

                if (isInside(x, y, yesButton)) {
                    std::cout << "You clicked YES\n";
                    running = false;
                } else if (isInside(x, y, noButton)) {
                    std::cout << "You clicked NO\n";
                    running = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Draw buttons
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);  // Green for Yes
        SDL_RenderFillRect(renderer, &yesButton);
        SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);  // Red for No
        SDL_RenderFillRect(renderer, &noButton);

        // Render question text
        renderText(renderer, font, question, textColor, 200, 150);

        // Render button labels
        renderText(renderer, font, "Yes", textColor, yesButton.x + 25, yesButton.y + 10);
        renderText(renderer, font, "No", textColor, noButton.x + 30, noButton.y + 10);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

