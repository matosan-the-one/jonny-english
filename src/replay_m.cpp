#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include "ball.h"

void replay(int x, int y) {
    static int g , l;
    std::ofstream data("./player_log/replay/replay.txt", std::ios::app);
    if(g!=x || l!=y) {
        data << x << " " << y << "\n";
    }
    data.close();
    g=x;
    l=y;
}

void replay_save(int i){
    if(i==0)
        std::rename("./player_log/replay/replay.txt", "./player_log/replay/replay1.txt");
    else if(i==1)
        std::rename("./player_log/replay/replay.txt", "./player_log/replay/replay2.txt");
    else
        std::rename("./player_log/replay/replay.txt", "./player_log/replay/replay3.txt");
}

void give_me_replay() {
    std::ifstream data0 ("./player_log/replay/replay1.txt");
    std::ifstream data1 ("file_dump/map1.txt");
    std::vector<Line> tab_l ;
    std::vector<int> x_p, y_p;
    int len1, len2, len3;
    int ux, uy;
    while(data0>>ux>>uy){
        x_p.push_back(ux);
        y_p.push_back(uy);
    }
    len1=x_p.size(); 
    data0.close();
    data0.open("./player_log/replay/replay2.txt");
    while(data0>>ux>>uy){
        x_p.push_back(ux);
        y_p.push_back(uy);
    }
    len2=x_p.size()-len1;
    data0.close();
    data0.open("./player_log/replay/replay3.txt");
    while(data0>>ux>>uy){
        x_p.push_back(ux);
        y_p.push_back(uy);
    }
    data0.close(); 
    len3=x_p.size()-len2-len1;
    
    if(1){ 
        int x1, x2, y1, y2;
        while(data1>>x1>>y1>>x2>>y2){
            tab_l.emplace_back(x1, y1, x2, y2);
        }
        data1.close();
    }
    SDL_Window *window = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
       return ;
    }
    int win_size_x = 1920, win_size_y = 1080;
    window = SDL_CreateWindow("jonny", 100, 100, win_size_x, win_size_y, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool run=1;

    int count=0, i=0;
    SDL_Rect player;
    player.x = 50;
    player.y = 50; 
    player.w = 20;
    player.h = 20;
    while(run){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
             if (event.type == SDL_QUIT){
                 run = 0;
             }
        }
        if(i==len1){
            int x1, x2, y1, y2; 
            tab_l.clear();
            data1.open ("file_dump/map2.txt");
            while(data1>>x1>>y1>>x2>>y2){
                tab_l.emplace_back(x1, y1, x2, y2);
            }
            data1.close();
        }
        if(i==len1+len2){
           int x1, x2, y1, y2; 
            tab_l.clear();
            data1.open ("file_dump/map3.txt");
            while(data1>>x1>>y1>>x2>>y2){
                tab_l.emplace_back(x1, y1, x2, y2);
            }
            data1.close();

        }
        if(i==len1+len2+len3)
            run=0;
        if(count==5){
            count=0;
            i++;
            player.x=x_p[i];
            player.y=y_p[i];
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &player);
        for(auto &line : tab_l){
            line.draw1(renderer);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        SDL_RenderClear(renderer);

        count++;
    }
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();

}
