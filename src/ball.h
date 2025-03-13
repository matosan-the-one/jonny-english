#include <SDL2/SDL.h>

class Vector_m {
public:
    float x, y;
		Vector_m();
		Vector_m(float x1, float y1);
		Vector_m operator+=(Vector_m&);
		Vector_m operator+(Vector_m t);
};

class Ball {
public:
    Vector_m poz, velocity;
    Ball() : poz(0, 0), velocity(0, 0) { }
    Ball operator+=(Ball &h) {
        poz += h.poz;
        return *this;
    }
};

class Line {
public:
		int x1, y1, x2, y2;
		Line(int, int, int, int);
		void draw(SDL_Renderer *t)const;
};
