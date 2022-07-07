//
// Created by Admin on 4/14/22.
//

#ifndef MINESWEEPER_RANDOM_H
#define MINESWEEPER_RANDOM_H

#include <random>
    class Random {
    static std:: mt19937 random;

    public:
        static int Int(int min, int max);
        static float Float(float min, float max);
    };


#endif //MINESWEEPER_RANDOM_H
