#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include "player.h"
#include "../include/glad/glad.h"

void clear_screen(SDL_Surface *screen){
		// first you have to lock your screen to safely modify the pixels
		SDL_LockSurface(screen);

    /* This assumes that color value zero is black. Use
       SDL_MapRGBA() for more robust surface color mapping! */
    /* height times pitch is the size of the surface's whole buffer. */
    SDL_memset(screen->pixels, 0, screen->h * screen->pitch);

    SDL_UnlockSurface(screen);
}

void color_pixel(SDL_Surface *screen, int x, int y, int r, int g, int b){
		SDL_LockSurface(screen);
		uint8_t *pixel_tab = (uint8_t *)screen->pixels;
		// the rgb pixels can't populate the same space because they would just overwrite memory
		pixel_tab[y*screen->pitch + x*screen->format->BytesPerPixel + 0]= b;
		pixel_tab[y*screen->pitch + x*screen->format->BytesPerPixel + 1]= g;
		pixel_tab[y*screen->pitch + x*screen->format->BytesPerPixel + 2]= r;
		pixel_tab[y*screen->pitch + x*screen->format->BytesPerPixel + 6]= b;
		pixel_tab[y*screen->pitch + x*screen->format->BytesPerPixel + 5]= g;
		pixel_tab[y*screen->pitch + x*screen->format->BytesPerPixel + 4]= r;
		SDL_UnlockSurface(screen);
}

void game_window(){
		SDL_Window *window=nullptr;
		if(SDL_Init(SDL_INIT_VIDEO)<0){
				std::cout << "napaka\n" << SDL_GetError() << "\n";
		}
		SDL_Surface *screen;
		// before making a window what version of open gl are you using
		/*
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// faster refresh
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		// 24 bit collector
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		*/
		// window = SDL_CreateWindow("jonny", 0, 0, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		window = SDL_CreateWindow("jonny", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
		/*
		 * SDL_Renderer *renderer = nullptr;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		*/
		/*
		SDL_GLContext context;
		context = SDL_GL_CreateContext(window);
		*/
		
		screen = SDL_GetWindowSurface(window);
		/*
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderPresent(renderer);	
		SDL_Delay(3000);
		*/
		SDL_Surface *image;
		image = SDL_LoadBMP("./picture/tux.bmp");
		SDL_BlitSurface(image,NULL,screen,NULL);
		SDL_FreeSurface(image);
		SDL_UpdateWindowSurface(window);

		// set up function pointers
		//     gladLoadGLLoader(SDL_GL_GetProcAddress);
		// infinite loop
		/*if(!create_map()){
				std::cout << "\nthere is a gremlin in your code get rid of it";
				return;
		}*/
		bool run_game=true;
		while(run_game){
				// make an event loop
				SDL_Event event;

				// we want to get x and y position
				int x, y;
				Uint32 button;
				button = SDL_GetMouseState(&x, &y);

				while(SDL_PollEvent(&event)){
						// handle events
						if(event.type == SDL_QUIT)
								run_game = false;
						if(event.type == SDL_KEYDOWN){
								if(event.key.keysym.sym == SDLK_w){
										std::cout << "\nw is pressed";
								}
								else{
										std::cout << "\nw not pressed";
								}
						}
						if(event.button.button == SDL_BUTTON_LEFT){
								// clear_screen(screen);
								std::cout << "\nleft click cordinates of x and y are: " << x << ", " << y << "\n";
								color_pixel(screen, x, y, 57, 255, 20);
								SDL_UpdateWindowSurface(window);
						}
				}
				/*
				glClearColor(1.0f,0.0f,0.0f,1.0f);
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
				
				SDL_GL_SwapWindow(window);
				*/
				// every time the user interacts the window updates TODO fix so user can see when he doesn't move
				SDL_UpdateWindowSurface(window);
		}

		SDL_DestroyWindow(window);
		SDL_Quit();
}

