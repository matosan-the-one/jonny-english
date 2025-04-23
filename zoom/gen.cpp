#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void zoom(SDL_Renderer* ren, vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
    // Define the zoom area in map coordinates
		
		int g, k;
		
    SDL_GetMouseState(&g, &k);

    int zoomX = g-150; // top-left corner X of the zoom rectangle
    int zoomY = k-150; // top-left corner Y
    int zoomW = 300; // width of the zoom area
    int zoomH = 300; // height

    // Calculate scaling factors to fit the zoom area into the window
    float scaleX = (float)WINDOW_WIDTH / zoomW;
    float scaleY = (float)WINDOW_HEIGHT / zoomH;

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    for (int i = 0; i < a.size(); i++) {
        // Convert map coordinates to screen coordinates
        int x1 = (a[i] - zoomX) * scaleX;
        int y1 = (b[i] - zoomY) * scaleY;
        int x2 = (c[i] - zoomX) * scaleX;
        int y2 = (d[i] - zoomY) * scaleY;
				
        // Only draw if within zoomed area bounds
        SDL_RenderDrawLine(ren, x1, y1, x2, y2);
    }

    SDL_RenderPresent(ren);
}


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
				return -1;
    }
    SDL_Window* win = SDL_CreateWindow("SDL2 Line Drawer", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    ifstream data("map1.txt");
    int x1, y1, x2, y2;
    SDL_Event e;
    int quit = 0;

    vector<int> a, b, c, d;
        while (data >> x1 >> y1 >> x2 >> y2) {
            a.push_back(x1);
            b.push_back(y1);
            c.push_back(x2);
            d.push_back(y2);
    } 
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // black background
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // white lines
        
        if (keystate[SDL_SCANCODE_X]) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            cout << "Mouse at: " << mouseX << " " << mouseY << endl;
        }
				if (keystate[SDL_SCANCODE_G]) {
					 zoom(ren, a, b, c, d);	
					// zoom(ren);
				}
				else {
						for(int i=0; i<a.size()-1; i++){
								SDL_RenderDrawLine(ren, a[i], b[i], c[i], d[i]);
						}
						SDL_RenderPresent(ren);
				}
        SDL_Delay(10);
    }

    data.close();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
