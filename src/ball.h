#include <SDL2/SDL.h>

class Vector {
public:
    float x, y;
		Vector();
		Vector(float x1, float y1);
		Vector operator+=(Vector&);
		Vector operator+(Vector t);
};

class Ball {
public:
    Vector poz, velocity;
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
