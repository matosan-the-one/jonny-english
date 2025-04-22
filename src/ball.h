#include <SDL2/SDL.h>

class Vector_m {
public:
    float x, y;
		Vector_m();
		Vector_m(float x1, float y1);
		Vector_m operator+=(Vector_m &);
		Vector_m operator+(Vector_m t);
		void reflect(float angle);
};

class Line {
public:
		int x1, y1, x2, y2;
		Line(int, int, int, int);
		void draw(SDL_Renderer *t)const;
		float get_angle(); 
			
		void draw1(SDL_Renderer *t)const;
		
};

class Ball {
public:
    Vector_m poz, velocity;
    Ball() : poz(0, 0), velocity(0, 0) { }
    /*Ball operator+=(Ball &h) {
				poz = poz + h.velocity;
        return *this;
    }*/
};


