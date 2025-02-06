#include <iostream>
// line inits 
float m = 2;
float b = 0.1;

float f(float x){
    float y = m * x + b;
    return y;
}
class Point {
public:
    float x, y;
    float radius;
    float bias=1;
    int label;
    int guess;
    Point(float x, float y, float radius=10) {
        this->x = x;
        this->y = y;
        this->radius = radius;
        this-> label = (y > f(x)) ? 1 : -1;
    }
    void setGuess(int g){
        guess = g;
    }

};

