#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include "player.h"
#include "../include/glad/glad.h"

void game_window() {
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error: " << SDL_GetError() << "\n";
        return;
    }
		int win_size_x = 2000, win_size_y = 2000;
		
		int x1, x2, y1, y2;
		bool have_poz1 = false;

    window = SDL_CreateWindow("jonny", 100, 100, win_size_x, win_size_y, SDL_WINDOW_SHOWN);    
		SDL_SetWindowSize(window, win_size_x + 1, win_size_y + 1);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *image = SDL_LoadBMP("./picture/tux_the_english.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
		// { x, y, height, width} 
    SDL_Rect rectangle;
		rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 40;
    rectangle.h = 40;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    bool run_game = true;
    while (run_game) {
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                run_game = false;
            }
						if (event.type == SDL_KEYDOWN){
								const Uint8 *keystate = SDL_GetKeyboardState(NULL);
                if (keystate[SDL_SCANCODE_W]) {
                    std::cout << "w is pressed\n";
										if(rectangle.y > 0){
												SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle); // the problem with render clear is that it clears the whole screen
												SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
												rectangle.y-=5;
										}
										else{
												std::cout << "there is too little space so move other direction\n";
										}
                }
                if (keystate[SDL_SCANCODE_S]) {
                    std::cout << "s is pressed\n";
										if(rectangle.y < win_size_y){
												SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle);
												SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
												rectangle.y+=5;
										}
										else{
												std::cout << "there is too little space so move other direction\n";
										}
								}
                if (keystate[SDL_SCANCODE_A]) {
                    std::cout << "a is pressed\n";
										if(rectangle.x > 0){
												SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle);
												SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
												rectangle.x-=5;
										}
										else{
												std::cout << "there is too little space so move other direction\n";
										}
								}
                if (keystate[SDL_SCANCODE_D]) {
                    std::cout << "d is pressed\n";
										if(rectangle.x < win_size_x-20){
												SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle);
												SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
												rectangle.x+=5;
										}
										else{
												std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_X]) {
										// i want to draw a line
										if(!have_poz1){
												SDL_GetMouseState(&x1, &y1);
												have_poz1 = !have_poz1;
										}
										else{
												// draw
												SDL_GetMouseState(&x2, &y2);
												SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
												have_poz1 = !have_poz1;
										}
								}
            }
						if (event.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                std::cout << "Left click at: " <<  x  <<  ", "  <<  y  <<  "\n";
                // color a pixel so i can draw a line
                SDL_SetRenderDrawColor(renderer, 57, 255, 20, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &rectangle);
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

