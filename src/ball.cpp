class Vector {
public:
    float x, y;

    // Constructor
    Vector(float x = 0, float y = 0) : x(x), y(y) { }

    // Operator+
    Vector operator+(const Vector &other) const {
        return Vector(x + other.x, y + other.y);
    }

    // Operator+=
    Vector &operator+=(const Vector &other) { // Now takes const reference
        x += other.x * 0.98; // Apply scaling here
        y += other.y * 0.98;
        return *this;
    }
};


class Ball {
public:
    Vector poz, hitrost;

    // Default constructor for Ball
    Ball() : poz(0, 0), hitrost(0, 0) { }

    // Operator+= adds the positions and velocities of two Balls.
    Ball &operator+=(const Ball &h) {
        poz += h.poz;
        hitrost += h.hitrost;
        return *this;
    }
};


