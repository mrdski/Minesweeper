//
// Created by Matthew Dylewski on 4/18/22.
//

#ifndef PROJECT3_RANDOM_H
#define PROJECT3_RANDOM_H
#include <random>

class Random
{
public:
    static int Int(int min, int max);
    static float Float(float min, float max);
private:
    static std::mt19937 random;
};
#endif //PROJECT3_RANDOM_H
