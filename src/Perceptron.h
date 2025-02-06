#include <cstdlib>
#include <time.h>
#include <iostream>
// rand function
float getRand(float minBound, float maxBound) {
    float randomNum = minBound + static_cast <float> (rand() / ( static_cast <float> (RAND_MAX)/(maxBound - minBound)));
    return randomNum;
}
int sign(float n) {
    return ((n > 0) ? 1 : -1);
}
class Perceptron {
public:

    // perceptorn class, gonna have set of 3 weights (3rd = bias, auto = 1)
    // guess: any point x, y, multiply and get sign + return
    // train: go through each point, get error, multiply by input and lr
    // yeah idk sounds fun

    const int num_of_weights = 3;
    float weights[3];
    float lr = 0.005;
    Perceptron() {
        srand(time(0));
        for (int i = 0; i < num_of_weights; i++){
            weights[i] = getRand(-1, 1);
        }

    }

    int guess(float inputs[3]) {
        float sum = 0;
        for(int i = 0; i < num_of_weights; i++){
            sum += weights[i] * inputs[i];
        }
        return sign(sum);
    }

    void train(float inputs[3], int target){
        // guess input, find error and add input * error * lr to weight
        int g = guess(inputs);
        int error = target-g ;


        for (int i = 0; i < num_of_weights; i++){
            weights[i] += error * inputs[i] * lr;
        }
    }

    float y_val_for_line(float x){
        return -(weights[0] /weights[1]) * x - weights[2]/weights[1];
    }

};