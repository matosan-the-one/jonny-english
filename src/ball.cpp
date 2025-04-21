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
			
		
};

class Ball {
public:
    Vector_m poz, velocity;
    Ball() : poz(0, 0), velocity(0, 0) { }
	void bounce(Line L);	
    /*Ball operator+=(Ball &h) {
				poz = poz + h.velocity;
        return *this;
    }*/
};

Vector_m::Vector_m(){
		x=0;
		y=0;
}	

Vector_m::Vector_m(float x1, float y1){
		x=x1;
		y=y1;
}

Vector_m Vector_m::operator+=(Vector_m &od){
		od.x*=0.95;
		od.y*=0.95;
		*this=*this+od;	
		return *this;
}

Vector_m Vector_m::operator+(Vector_m t){
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

void Vector_m::reflect(float angle){
	float xr, yr;
	xr=x*cos(2*angle)+y*sin(2*angle);
	yr=x*sin(2*angle)-y*cos(2*angle);
  x=xr;
	y=yr;
}


float Line::get_angle(){
	return (float)atan((y2-y1)/(x2-x1));

} 

void Ball::bounce(Line L){
	velocity.reflect(L.get_angle());

}	
