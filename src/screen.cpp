#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "player.h"
#include "../include/glad/glad.h"
#include "window.h"
#include "files.h"
#include <fstream>

void tick();

bool game_window(int inst) {
		SDL_Window *window = nullptr;
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				std::cout << "Error: " << SDL_GetError() << "\n";
				return 0;
		}
		int win_size_x = 1920, win_size_y = 1080;

		int x1, x2, y1, y2;
		bool have_poz1 = false;
			
		int k=0;
		window = SDL_CreateWindow("jonny", 100, 100, win_size_x, win_size_y, SDL_WINDOW_SHOWN );//| SDL_WINDOW_FULLSCREEN);    
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		//SDL_SetWindowOpacity(window, 0.5f); // 80% transparent
		std::vector<Line> tab_l, h;
		std::ifstream data("file_dump/map1.txt");
		data.close();
		//if it is inside of if statments the fata isn't inicilaized
		if(inst==0){
				data.open("file_dump/map1.txt");/*
				datap.open("player_log/spawn/play1.txt");
				datae.open("player_log/spawn/bots1.txt");
				*/	
		}
		else if(inst==1){
				data.open("file_dump/map2.txt");
		}
		else{
				data.open("file_dump/map3.txt");
		}

		while(data>>x1>>y1>>x2>>y2){
				tab_l.emplace_back(x1, y1, x2, y2);
				h.emplace_back(x1, y1, x2, y2);
				add_obstacle(renderer, x1, y1, x2, y2);
		}
		data.close();
		SDL_Rect ball;
		ball.x=500;
		ball.y=500;
		ball.w=10;
		ball.h=10;
		Ball zoga;
		zoga.poz.x=500;
		zoga.poz.y=500;

		SDL_Surface *ball_img = SDL_LoadBMP("./picture/ball.bmp");
		if (!ball_img) {
		std::cerr << "Failed to load ball image: " << SDL_GetError() << std::endl;
		return 0;
		}
		SDL_SetColorKey(ball_img, SDL_TRUE, SDL_MapRGB(ball_img->format, 255, 0, 255));
		SDL_Texture *ball_texture = SDL_CreateTextureFromSurface(renderer, ball_img);
		SDL_FreeSurface(ball_img);

		//free surface
		SDL_Surface *image = SDL_LoadBMP("./picture/tux_the_english.bmp");
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
		// { x, y, height, width} 
		SDL_Rect rectangle;
		rectangle.x = 50;
		rectangle.y = 100;
		rectangle.w = 20;
		rectangle.h = 20;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_RenderFillRect(renderer, &ball);// the problem with render clear is that it clears the whole screen

		bool ok=true;

		int prev_x, prev_y;
		bool  have_prev=false;
		bool run_game = true;
		bool have_ball = true;
		while (run_game) {
				SDL_Event event;
				while (SDL_PollEvent(&event)){
						if (event.type == SDL_QUIT){
								ok=false;
								run_game = false;
						}
						if (event.type == SDL_KEYDOWN){
								const Uint8 *keystate = SDL_GetKeyboardState(NULL);
								SDL_Rect *old_rect= &rectangle;
								if (keystate[SDL_SCANCODE_W]) {
										if(rectangle.y > 0 && check_valid(rectangle.x, rectangle.y-5)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, old_rect);
												SDL_RenderFillRect(renderer, &rectangle); // the problem with render clear is that it clears the whole screen
												rectangle.y-=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_S]) {
										if(rectangle.y < win_size_y && check_valid(rectangle.x, rectangle.y+5)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle);
												rectangle.y+=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_A]) {
										if(rectangle.x > 0 && check_valid(rectangle.x-5, rectangle.y)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle);
												rectangle.x-=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_D]) {
										if(rectangle.x < win_size_x-20 && check_valid(rectangle.x+5, rectangle.y)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &rectangle);
												rectangle.x+=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								/* drawing the map */
										if (keystate[SDL_SCANCODE_X]) {
												// i want to draw a line
												if(!have_poz1){
														SDL_GetMouseState(&x1, &y1);
														have_poz1 = !have_poz1;
												}
												else{
														// draw
														SDL_GetMouseState(&x2, &y2);
														add_obstacle(renderer, x1, y1, x2, y2);
														// we have to add this to the other lines
														if( !(x1 == x2 && y1 == y2)){
																tab_l.emplace_back(x1, y1, x2, y2);
																h.emplace_back(x1, y1, x2, y2);
																have_poz1 = !have_poz1;
														}
												}
										}
								/**/
								/* saving the map into a file
										if (keystate[SDL_SCANCODE_P]){
												maps(h, k, h.size()-1);
												k=h.size()-1;			
										}
								*/
						}
						// SDL_SetRenderDrawColor(renderer, 57, 255, 20, SDL_ALPHA_OPAQUE);
					
						if (event.button.button == SDL_BUTTON_LEFT && have_ball) {
								if(!have_prev){
										SDL_GetMouseState(&prev_x, &prev_y);
										have_prev=!have_prev;
								}
						}
						if (event.type == SDL_MOUSEBUTTONUP && have_prev){
								int temp1, temp2;
								SDL_GetMouseState(&temp1, &temp2);
								// try to make a function crazymath(prev_x, prev_y, temp1, temp2);	
								have_prev=!have_prev;
								have_ball=!have_ball;
						}
				}
				
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				// SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				if(ball_valid(zoga.poz.x,zoga.poz.y)){
						zoga.poz += zoga.velocity;
						ball.x = zoga.poz.x;
						ball.y = zoga.poz.y;
				}
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				for(auto &line : tab_l){
						line.draw(renderer);
				}
				SDL_RenderCopy(renderer, texture, NULL, &rectangle);
				SDL_RenderCopy(renderer, ball_texture, NULL, &ball);
				SDL_RenderPresent(renderer);
				SDL_Delay(10);
		}

		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(ball_texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		clear(); // clear all the global vectors so i can get the walls for the new map 
		// so they don't interfir
		// return ok;
		return 1;
}


