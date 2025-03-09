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
    /*Ball operator+=(Ball &h) {
				poz = poz + h.velocity;
        return *this;
    }*/
};

class Line {
public:
		int x1, y1, x2, y2;
		Line(int, int, int, int);
		void draw(SDL_Renderer *t)const;
};

Vector::Vector(){
		x=0;
		y=0;
}	

Vector::Vector(float x1, float y1){
		x=x1;
		y=y1;
}

Vector Vector::operator+=(Vector &od){
		od.x*=0.95;
		od.y*=0.95;
		*this=*this+od;	
		return *this;
}

Vector Vector::operator+(Vector t){
		x+=t.x;
		y+=t.y;
		return *this;
}

Line::Line(int in_x1=0, int in_y1=0, int in_x2=0, int in_y2=0){
		x1=in_x1;	
		y1=in_y1;	
		x2=in_x2;	
		y2=in_y2;	
}

void Line::draw(SDL_Renderer *t) const {
		SDL_SetRenderDrawColor(t, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(t, x1, y1, x2, y2);
}
