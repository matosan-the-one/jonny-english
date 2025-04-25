#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "../include/glad/glad.h"
#include "window.h"
#include "files.h"
#include "history.h"
#include "replay_m.h"
#include "clues.h"
#include "call_game.h"
#include <fstream>
#include <ctime>
#include <cmath>

void tick();

bool game_window(int inst, const char ime_j[], bool continue_g, float &score) {
        std::cout << "game window up\n";
		int counter=0;
		SDL_Window *window = nullptr;
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				std::cout << "Error: " << SDL_GetError() << "\n";
				return 0;
		}
		int win_size_x = 1920, win_size_y = 1080;

		int x1, x2, y1, y2;
		bool have_poz1 = false;
			
		int k=0;
		window = SDL_CreateWindow("jonny", 100, 100, win_size_x, win_size_y, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);    
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		//SDL_SetWindowOpacity(window, 0.5f); // 80% transparent
		std::vector<Line> tab_l, h;
        
		SDL_Rect player;
		player.x = 50;
		player.y = 100;
		player.w = 20;
		player.h = 20;

		std::ifstream data;
		std::ifstream datap;
		std::ifstream datae;
		data.close();
		//if it is inside of if statments the fata isn't inicilaized
		if(inst==0){
				data.open("file_dump/map1.txt");
				if(continue_g) {
						datap.open("player_log/spawn/play1.txt");
						datae.open("player_log/spawn/bots1.txt");
				}
				else{
						datap.open("player_log/continue/play1.txt");
						datae.open("player_log/continue/bots1.txt");
				}
		}
		else if(inst==1){
				data.open("file_dump/map2.txt");
				if(continue_g) {
						datap.open("player_log/spawn/play2.txt");
						datae.open("player_log/spawn/bots2.txt");
				}
				else{
						datap.open("player_log/continue/play2.txt");
						datae.open("player_log/continue/bots2.txt");
				}
		}
		else{
				data.open("file_dump/map3.txt");
				if(continue_g) {
						datap.open("player_log/spawn/play3.txt");
						datae.open("player_log/spawn/bots3.txt");
				}
				else{
						datap.open("player_log/continue/play3.txt");
						datae.open("player_log/continue/bots3.txt");
				}
		}
        if(!data || !datae || !datap){
               std::cout << "there are no files\n\n";
               SDL_DestroyRenderer(renderer);   
               SDL_DestroyWindow(window);    
               SDL_Quit();
               return 0;  
           }
		
		while(data>>x1>>y1>>x2>>y2){
				tab_l.emplace_back(x1, y1, x2, y2);
				h.emplace_back(x1, y1, x2, y2);
				add_obstacle(renderer, x1, y1, x2, y2);
		}
		
		// naredi 4 pozicije za igralca in rand()%4+0;
		datap>>player.x>>player.y;
        
        Player main_char(player.x, player.y, ime_j, 1);


		std::vector<Player> tab_e;
		if(1) {
				int o, p;
				char opa[20]={'e','n','e','m','y'};
				while(datae>>o>>p){
						tab_e.emplace_back(o, p, opa, 0);
				}
				if(continue_g){
						tab_e.emplace_back(-40, -40, opa, 0);
				}
		}


		data.close();
		datap.close();
		datae.close();

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
		

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_RenderFillRect(renderer, &ball);// the problem with render clear is that it clears the whole screen

		bool ok=true;

		// std::vector<Clue> tab;
		// Clue a;
		 int indone = 0;
		// tab = Clue::read_clues(inst);

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
								SDL_Rect *old_rect= &player;
								if (keystate[SDL_SCANCODE_W]) {
										if(player.y > 0 && check_valid(player.x, player.y-5)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, old_rect);
												SDL_RenderFillRect(renderer, &player); // the problem with render clear is that it clears the whole screen
												player.y-=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_S]) {
										if(player.y < win_size_y && check_valid(player.x, player.y+5)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &player);
												player.y+=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_A]) {
										if(player.x > 0 && check_valid(player.x-5, player.y)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &player);
												player.x-=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_D]) {
										if(player.x < win_size_x-20 && check_valid(player.x+5, player.y)){
												SDL_SetRenderDrawColor(renderer,  0, 0, 0, SDL_ALPHA_OPAQUE);
												SDL_RenderFillRect(renderer, &player);
												player.x+=5;
										}
										else{
												// std::cout << "there is too little space so move other direction\n";
										}
								}
								if (keystate[SDL_SCANCODE_ESCAPE]){
										SDL_DestroyTexture(texture);
										SDL_DestroyTexture(ball_texture);
										SDL_DestroyRenderer(renderer);
										SDL_DestroyWindow(window);
										SDL_Quit();
										replay_save(inst);
										clear();
										game(continue_g, ime_j, inst, score);
								}
								/* drawing the map 
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
								*/
								if (keystate[SDL_SCANCODE_C]) {
										SDL_GetMouseState(&x1, &y1);
										indone++;
										if(indone<4)
										//tab[indone].write(inst, x1, y1);
										std::cout << "mouse cords: " << x1 << " " << y1 << "\n";
								}
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
                /*
                if(!tab_e.empty())
              for (auto it = tab_e.begin(); it != tab_e.end(); ) {
                it->show(renderer);

                if (27 > sqrt((it->get_x() - player.x)*(it->get_x() - player.x) +    
                              (it->get_y() - player.y)*(it->get_y() - player.y))) {
                    
                    int result = it->collide_p(&main_char); // Only call once!

                    if (result == -1) {
                        ok = false;
                        run_game = false;
                        break;
                    }
                    else if (result == 0) {
                        if(!tab_e.empty())
                        it = tab_e.erase(it);
                        continue;
                    }
                }
                if(!tab_e.empty())
                ++it;
            } *//*
for (auto it = tab_e.begin(); it != tab_e.end(); ) {
    it->show(renderer);

    double dx = it->get_x() - player.x;
    double dy = it->get_y() - player.y;

    if ((dx * dx + dy * dy) < (27 * 27)) {
        int result = it->collide_p(&main_char);

        if (result == -1) {
            ok = false;
            run_game = false;
            return 0; // or break outer game loop safely
        }
        else if (result == 0) {
            std::vector<Player>::iterator tmp;
            tmp=it;
            it++;
            tab_e.erase(tmp); // even if last, this is valid
            continue;
        }
    }

    ++it;
}*/

for (auto it = tab_e.begin(); it != tab_e.end(); ) {
    if (27 > sqrt((it->get_x() - player.x)*(it->get_x() - player.x) +
                  (it->get_y() - player.y)*(it->get_y() - player.y)) && tab_e.size()>=1) {
        int result = it->collide_p(&main_char); 
        if (result == -1) {
            ok = false;
            run_game = false;
            break;
        } else if (result == 0) {
						
            it = tab_e.erase(it); 
            score+=250;
            continue;
        }

    }
		++it;
}


                /*
				for(auto &eny :	tab_e){
                    if(27>sqrt((eny.get_x()-player.x)*(eny.get_x()-player.x)+(eny.get_y()-player.y)*(eny.get_y()-player.y)))
                        if(eny.collide_p()==-1){ok=false; run_game=false;}
                        else if(eny.collide_p()==0){
                            eny.erase();
                        }
						eny.show(renderer);
				}*/

								for(auto &eny:tab_e) {
                    eny.show(renderer);
								}
                if(counter==20){
                    counter=0;
                    score-=0.1;
                    for(auto &eny :tab_e){
                        SDL_Delay(0.1);
                        eny.move(player.x, player.y);
                        // history(main_char, tab_e);
                    }
                }
								if(tab_e.size()==1){
										ok=1;
										run_game=0;
								}
                counter++;
								// std::cout << "seg1\n";
								history(inst, player.x, player.y, ime_j, tab_e);
								// std::cout << "seg2\n";
				/*
				for(int i=0; i<3; i++){
						std::cout << "rand \n";
						if(!tab[i].isFound()){
								std::cout << "rand \n";
								tab[i].check(player.x, player.y);
						}
						std::cout << "rand \n";
				}*/

				SDL_RenderCopy(renderer, texture, NULL, &player);
				SDL_RenderCopy(renderer, ball_texture, NULL, &ball);
				SDL_RenderPresent(renderer);
				SDL_Delay(10);
        replay(player.x, player.y);
		}

		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(ball_texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
        replay_save(inst);
		clear(); // clear all the global vectors so i can get the walls for the new map 
		// so they don't interfir
		return ok;
}


