#include "includefiles.h"

// global init bounds
float boundsX[2] = {0, 800};
float boundsY[2] = {0, 800};
float pointBounds[2] = {0, 1};

// PI
# define M_PI           3.14159265358979323846


// return sf vector of function
sf::Vector2f vectorize(float x, float y){
    return sf::Vector2f(x, y);
} 



/* 
    1. Calculate points of either side of rect
    2. Calculate direction vector
    3. Create rectangle with thickness/length
    4. Get rotation angle and apply
*/
void drawThickLine(sf::RenderWindow& window, float x1, float y1, float x2, float y2, float thickness, sf::Color color) {
    sf::Vector2f point1(x1, y1);
    sf::Vector2f point2(x2, y2);

    // Compute the direction vector
    sf::Vector2f direction = point2 - point1;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Create a rectangle with thickness as width and length as height
    sf::RectangleShape line(sf::Vector2f(length, thickness));
    line.setOrigin(vectorize(0, thickness / 2)); // Center it on thickness
    line.setPosition(point1); // Start at (x1, y1)

    // Calculate the rotation angle in radians
    float angleInRadians = atan2(direction.y, direction.x); 

    // Create an sf::Angle object from the radians
    sf::Angle angle = sf::radians(angleInRadians); 

    // Set the rotation of the line using the sf::Angle object
    line.setRotation(angle);  // Set rotation using sf::Angle

    line.setFillColor(color); // Set color

    window.draw(line);
}

/*
    Map function -> needs multiple things
    Take one bound, transform into another bound, take points and transform them
    Point from [-1, 1] transforms to [0, 800]
    normalized = (point val - minBound) / (maxBound - minBound) -> transforms to [0, 1]
    normalized *= (maxBound2 - minBound2)
    normalized += minBound2

    normalized = (val - min1) / (max1 - min1) * (max2 - min2) + min2
*/
float normalizeVal(float value, float currentBounds[2], float futureBounds[2] ){
    float normalized = (value - currentBounds[0]) / (currentBounds[1] - currentBounds[0]) * (futureBounds[1] - futureBounds[0]) + futureBounds[0];
    return normalized;
}


// draw any Point* point onto the Window* window
void draw(Point* point, sf::RenderWindow& window) {
    sf::CircleShape circle(point->radius);

    float transformedX = normalizeVal(point->x, pointBounds, boundsX);
    float transformedY = boundsY[1] - normalizeVal(point->y, pointBounds, boundsY);  // Invert y-axis to match SFML screen coordinates

    circle.setPosition(vectorize(transformedX - point->radius, transformedY - point->radius));
    circle.setFillColor((point->guess == 1) ? sf::Color::Red : sf::Color::Blue);
    window.draw(circle);
}

int main(){
     // init random
    sf::RenderWindow window(sf::VideoMode({boundsX[1], boundsY[1]}), "SFML Points");

    Perceptron perceptron = Perceptron();
    int guess; // init here just for speed or whatever i dont want to init the same variable 100t imes
    float inputs[3]; // same thing here
    // create points
    std::vector<Point> points;
    for (int i = 0; i < 100; i++){
        points.emplace_back(getRand(pointBounds[0], pointBounds[1]), getRand(pointBounds[0], pointBounds[1]));
    }
    while (window.isOpen()) {
        while(const std::optional event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }

            if(event->is<sf::Event::MouseButtonPressed>()) {
                for (auto& point: points) {
                    inputs[0] = point.x; inputs[1] = point.y; inputs[2] = point.bias;
                    perceptron.train(inputs, point.label);
                }
            } // we train on mouse click
        }

        window.clear();
        // draw the points
        for (auto& point: points) {
            inputs[0] = point.x; inputs[1] = point.y;
            guess = perceptron.guess(inputs);
            point.setGuess(guess);
            draw(&point, window);
        }
    
        // draw the bounding line
        drawThickLine(
            window, 
            boundsX[0], normalizeVal((pointBounds[1] - f(pointBounds[0])), pointBounds, boundsY), 
            boundsY[1], normalizeVal((pointBounds[1] - f(pointBounds[1])), pointBounds, boundsY), 
            5, sf::Color::White);
        drawThickLine(
            window, 
            boundsX[0], normalizeVal((pointBounds[1] - perceptron.y_val_for_line(pointBounds[0])), pointBounds, boundsY), 
            boundsY[1], normalizeVal((pointBounds[1] - perceptron.y_val_for_line(pointBounds[1])), pointBounds, boundsY), 
            5, sf::Color::White);
        window.display();

    }
    
}