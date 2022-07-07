#include <SFML/Graphics.hpp>
#include <iostream>

#include "board.h"
#include "textures.h"

using namespace std;

int main() {
    Board board;
    board.readConfig("config.cfg");
    cout << board.columns << endl;
    board.width = board.columns * 32;
    board.height = (board.rows * 32) + 100;
    //board.getRandomBoard();
    sf::RenderWindow window(sf::VideoMode(board.width, board.height), "Board set!");
   board.getRandomBoard();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf :: Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    bool right = false;
                    if(board.playGame){
                        board.click(window, x, y, right);
                    }
                    board.checkWin();
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.checkWin();
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    bool left = true;
                    if(board.playGame) {
                        board.click(window, x, y, left);
                    }
                    bool test1Clicked = false;
                    bool test2Clicked = false;
                    bool test3Clicked = false;
                    if( board.test1.getGlobalBounds().contains(x, y)){
                        test1Clicked = true;
                        board.restart();
                    }
                    else if( board.test2.getGlobalBounds().contains(x, y)){
                        test2Clicked = true;
                        board.restart();
                    }
                   else if( board.test3.getGlobalBounds().contains(x, y)){
                        test3Clicked = true;
                        board.restart();
                    }
                   else if(board.smile.getGlobalBounds().contains(x, y)){
                       board.restart();
                       board.getRandomBoard();
                      // board.debugging = true;
                   }
                        if(test1Clicked){
                            board.loadBoard("boards/testBoard1.brd");
                        }
                        if(test2Clicked) {
                            board.loadBoard("boards/testBoard2.brd");
                        }
                        if(test3Clicked){
                            board.loadBoard("boards/testBoard3.brd");
                        }
                    if(!board.playGame){
                        if(board.smile.getGlobalBounds().contains(x, y) || board.test1.getGlobalBounds().contains(x, y)
                        || board.test2.getGlobalBounds().contains(x, y) || board.test3.getGlobalBounds().contains(x, y)){
                            window.draw(board.faceLose);
                            board.click(window, x, y, left);
                        }
                    }
                    if(board.win){
                        if(board.smile.getGlobalBounds().contains(x, y) || board.test1.getGlobalBounds().contains(x, y)
                           || board.test2.getGlobalBounds().contains(x, y) || board.test3.getGlobalBounds().contains(x, y)){
                            window.draw(board.faceWin);
                            board.click(window, x, y, left);
                        }
                    }

                }
            }
        }
////get global bounds outside of the for loops
////do actions and reset baord in the for loops
////call loadboard outisde the for loops after checking if it is clicked
        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
    }

