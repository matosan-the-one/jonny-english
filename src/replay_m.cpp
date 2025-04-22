#include <fstream>

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
    ifstream data0 ("./player_log/replay/replay1.txt");
    ifstream data1 ("file_dump/map1.txt");
       
    SDL_Window *window = nullptr;
           if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                   return -1;
           }
           int win_size_x = 1920, win_size_y = 1080;
    window = SDL_CreateWindow("jonny", 100, 100, win_size_x, win_size_y, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

SDL_Rect player;
           player.x = 50;
           player.y = 100;
           player.w = 20;
           player.h = 20;

SDL_RenderFillRect( renderer, &player );

               SDL_RenderPresent(renderer);
               SDL_Delay(10);


               for(auto &line : tab_l){
                 line.draw(renderer);
               }


}
