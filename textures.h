//
// Created by Admin on 4/4/22.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

#ifndef MINESWEEPER_TEXTURES_H
#define MINESWEEPER_TEXTURES_H
//A class for tiles/spaces. The board is made up of a whole lot of these things.
//Each one of these can be a mine, have a flag, some number of adjacent tiles/mines, etc.

//You may find it helpful to create a single storage container for all of the
//sf::Texture objects, and then pass that around to any class which might need those files.

//functions like: creating sprites from textures, changing appearing disapearing things
class Textures {
    static unordered_map<string, sf::Texture> text;
public:
    static void LoadText(string file);
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};


#endif //MINESWEEPER_TEXTURES_H
