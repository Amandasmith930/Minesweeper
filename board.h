//
// Created by Admin on 4/4/22.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "textures.h"
#include "Random.h"
using namespace std;

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

class Board {
    struct Tile{
        bool minePresent = false;
        int columnVector{};
        int vectorRow{};
        bool isWin = false;
        bool adjMines1 = false;
        bool adjMines2 = false;
        bool adjMines3 = false;
        bool adjMines4 = false;
        bool adjMines5 = false;
        bool adjMines6 = false;
        bool adjMines7 = false;
        bool adjMines8 = false;
        int adjMinesCount = 0;
        bool flagged = false;
        bool debugging1 = false;
        void setPosition(float x, float y);
        bool getHidden();
        bool isHidden = true;
        int mouseX{};
        int mouseY{};
        sf:: Sprite GetTiles();
        sf:: Sprite tileHidden;
        sf:: Sprite tileRevealed;
        sf:: Sprite tileMine;
        sf:: Sprite tileFlagged;
        sf :: Sprite one;
        sf :: Sprite two;
        sf :: Sprite three;
        sf :: Sprite four;
        sf :: Sprite five;
        sf :: Sprite six;
        sf :: Sprite seven;
        sf :: Sprite eigth;
        void drawTile(sf::RenderWindow& window, bool debug);
        Tile(){
            tileHidden.setTexture(Textures::GetTexture("tile_hidden"));
            tileRevealed.setTexture(Textures::GetTexture("tile_revealed"));
            tileFlagged.setTexture(Textures::GetTexture("flag"));
            tileMine.setTexture(Textures::GetTexture("mine"));
            one.setTexture(Textures::GetTexture("number_1"));
            two.setTexture(Textures::GetTexture("number_2"));
            three.setTexture(Textures::GetTexture("number_3"));
            four.setTexture(Textures::GetTexture("number_4"));
            five.setTexture(Textures::GetTexture("number_5"));
            six.setTexture(Textures::GetTexture("number_6"));
            seven.setTexture(Textures::GetTexture("number_7"));
            eigth.setTexture(Textures::GetTexture("number_8"));
        }
        Tile(int columnVector, int rowVector, bool minesOnBoard);
        vector<Tile*> neighbors;
    };
public:
    sf:: Sprite debug;
    sf:: Sprite smile;
    sf:: Sprite faceWin;
    sf:: Sprite faceLose;
    sf:: Sprite test1;
    sf:: Sprite test2;
    sf:: Sprite test3;
    sf:: Sprite digits;


    Board(){
        this -> columns = 0;
        this -> rows = 0;
        this -> mines = 0;
        debug.setTexture(Textures::GetTexture("debug"));
        smile.setTexture(Textures::GetTexture("face_happy"));
        faceWin.setTexture(Textures::GetTexture("face_win"));
        faceLose.setTexture(Textures::GetTexture("face_lose"));
      //  debug.setPosition(sf::Vector2f((columns*32/ 2.0f) + 96, rows * 32));
        test1.setTexture(Textures::GetTexture("test_1"));
        test2.setTexture(Textures::GetTexture("test_2"));
        test3.setTexture(Textures::GetTexture("test_3"));
        digits.setTexture(Textures::GetTexture("digits"));
    }
    vector<vector <Tile>> boardVector;
    int width;
    int height;
    int columns=0;
    int rows=0;
    int mines=0;

    bool debugging = false;
    bool playGame = true;
    bool win = false;

    int GetColumn() const;
    int GetRows() const;
    int GetMines() const;
    void readConfig(const char* config);
    void getRandomBoard();
    void loadBoard(const string& loadedBoard);
    void createBoard();
    void adjMines();
    void draw(sf::RenderWindow& window);
    void click(sf::RenderWindow& window, int x, int y, bool left);
    void findNeighbors();
    void recursive(vector<Tile *> neighbors);
    void checkWin();
    void restart();

    int tileCount = 0;
    int tilesRevealed =0;
    int mineCount = 0;
    int flagsPlaced;

    sf::Sprite digitStrip[11];
    vector<sf::Sprite> count;
    void digitsCounter();
    void addDigit(int num);
    void leftoverMines();
};




#endif //MINESWEEPER_BOARD_H
