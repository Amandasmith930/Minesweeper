////
//// Created by Admin on 4/4/22.
////
//
#include "board.h"
#include "textures.h"
#include "Random.h"

//read in configuration file to get columns, rows and mines
void Board::readConfig(const char *config) {

    string currentValue;
    ifstream file;
    file.open("config.cfg");

    getline(file, currentValue);
    this->columns = stoi(currentValue);

    getline(file, currentValue);
    this->rows = stoi(currentValue);

    getline(file, currentValue);
    this->mines = stoi(currentValue);

    file.close();

    vector<vector<Tile>> board(rows, vector<Tile>(columns));
    this->boardVector = board;
}

int Board::GetColumn() const {
    return this->columns;
}

int Board::GetRows() const {
    return this->rows;
}
//load the board (test board 1, 2, 3 or any board loaded in and get mines)
void Board::loadBoard(const string &loadedBoard) {
    fstream stream;
    stream.open(loadedBoard);
    int r = 0;
    mines = 0;

    while (!stream.eof()) {
        string currentRow;
        getline(stream, currentRow);
        for (int c = 0; c < columns; c++) {
            //boardVector[r][c].adjMinesCount = 0;
            if (currentRow.at(c) == '1') {
                boardVector[r][c].minePresent = true;
                mines++;
            }
        }
        r++;
    }
}

void Board::createBoard() {
    vector<Tile> tiles;
    for (int i = 0; i < columns; i++) {
        tiles.clear();
        for (int j = 0; j < rows; j++) {
            tiles.push_back(Tile());
        }
        boardVector.push_back(tiles);
    }
}
//tile constructor
Board::Tile::Tile(int columnVector, int rowVector, bool minesOnBoard) {
    this->columnVector = columnVector;
    this->vectorRow = rowVector;
    this->minePresent = false;
    this->flagged = false;
    this->isHidden = true;
    this->adjMinesCount = 0;
}
//sets position of sprites
void Board::Tile::setPosition(float x, float y) {
    tileHidden.setPosition(x, y);
    tileRevealed.setPosition(x, y);
    tileFlagged.setPosition(x, y);
    tileMine.setPosition(x, y);
    one.setPosition(x, y);
    two.setPosition(x, y);
    three.setPosition(x, y);
    four.setPosition(x, y);
    five.setPosition(x, y);
    six.setPosition(x, y);
    seven.setPosition(x, y);
    eigth.setPosition(x, y);
}
//draws the board
void Board::draw(sf::RenderWindow &window) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            boardVector[i][j].setPosition(j * 32, i * 32);
            boardVector[i][j].drawTile(window, debugging);
            if (!playGame) {
                window.draw(faceLose);
                if(boardVector[i][j].minePresent ){
                    boardVector[i][j].isHidden = false;
                }
            }
            else if(win){
                window.draw(faceWin);
                boardVector[i][j].debugging1 = false;
            }
        }
    }
    faceWin.setPosition(sf::Vector2f((window.getSize().x / 2.0f) - 32, rows * 32));
//    window.draw(faceWin);
    faceLose.setPosition(sf::Vector2f((window.getSize().x / 2.0f) - 32, rows * 32));
//    window.draw(faceLose);
    smile.setPosition(sf::Vector2f((window.getSize().x / 2.0f) - 32, rows * 32));
    window.draw(smile);
    debug.setPosition(sf::Vector2f((window.getSize().x / 2.0f) + 96, rows * 32));
    window.draw(debug);
    test1.setPosition(sf::Vector2f((window.getSize().x / 2.0f) + 160, rows * 32));
    window.draw(test1);
    test2.setPosition(sf::Vector2f((window.getSize().x / 2.0f) + 224, rows * 32));
    window.draw(test2);
    test3.setPosition(sf::Vector2f((window.getSize().x / 2.0f) + 288, rows * 32));
    window.draw(test3);

    if (!playGame) {
        faceLose.setPosition(sf::Vector2f((window.getSize().x / 2.0f) - 32, rows * 32));
        window.draw(faceLose);

    }
    if (win) {
        faceWin.setPosition(sf::Vector2f((window.getSize().x / 2.0f) - 32, rows * 32));
        window.draw(faceWin);
    }
    digitsCounter();
    leftoverMines();

    for(sf::Sprite digit : count){
        window.draw(digit);
    }
}
//restarts the board when boards is renewed
void Board:: restart(){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                boardVector[i][j].adjMinesCount = 0;
                boardVector[i][j].adjMines1 = false;
                boardVector[i][j].adjMines2 = false;
                boardVector[i][j].adjMines3 = false;
                boardVector[i][j].adjMines4 = false;
                boardVector[i][j].adjMines5 = false;
                boardVector[i][j].adjMines6 = false;
                boardVector[i][j].adjMines7 = false;
                boardVector[i][j].adjMines8 = false;
                boardVector[i][j].flagged = false;
                boardVector[i][j].minePresent = false;
                boardVector[i][j].adjMinesCount = 0;
                boardVector[i][j].isHidden = true;
                boardVector[i][j].neighbors.clear();
        }
    }
        findNeighbors();
}
//draws the sprites based on the conditional
void Board::Tile::drawTile(sf::RenderWindow &window, bool debug) {
    if (isHidden) {
        window.draw(tileHidden);
    }
    if (flagged && isHidden) {
        window.draw(tileFlagged);
    }
    if (minePresent && !isHidden) {
        window.draw(tileMine);
    }
    if(debugging1 && minePresent){
        window.draw(tileMine);
    }
    if (!isHidden ) {
        window.draw(tileRevealed);
        if (minePresent) {
            window.draw(tileMine);
        }
    }
//    if(!flagged && minePresent && isHidden && isWin){
//        window.draw(tileFlagged);
//    }
    if (debugging1) {
        if (minePresent) {
            window.draw(tileMine);
        }
    }
    if (!minePresent && !flagged && !isHidden && adjMinesCount >= 0) {
        if (adjMines1) {
            adjMinesCount = 1;
        } else if (adjMines2) {
            adjMinesCount = 2;
        } else if (adjMines3) {
            adjMinesCount = 3;
        } else if (adjMines4) {
            adjMinesCount = 4;
        } else if (adjMines5) {
            adjMinesCount = 5;
        } else if (adjMines6) {
            adjMinesCount = 6;
        } else if (adjMines7) {
            adjMinesCount = 7;
        } else if (adjMines8) {
            adjMinesCount = 8;
        }
        if (adjMinesCount == 1) {
            window.draw(tileRevealed);
            window.draw(one);
        } else if (adjMinesCount == 2) {
            window.draw(tileRevealed);
            window.draw(two);
        } else if (adjMinesCount == 3) {
            window.draw(tileRevealed);
            window.draw(three);
        } else if (adjMinesCount == 4) {
            window.draw(tileRevealed);
            window.draw(four);
        } else if (adjMinesCount == 5) {
            window.draw(tileRevealed);
            window.draw(five);
        } else if (adjMinesCount == 6) {
            window.draw(tileRevealed);
            window.draw(six);
        } else if (adjMinesCount == 7) {
            window.draw(tileRevealed);
            window.draw(seven);
        } else if (adjMinesCount == 8) {
            window.draw(tileRevealed);
            window.draw(eigth);
        }
    }
}
//random board created
void Board::getRandomBoard() {
    bool debugging1 = false;
    if (debugging) {
        debugging1 = true;
    }
    readConfig("config.cfg");
    int count = mines;
    while (count > 0) {
        int randomX = Random::Int(0, rows - 1);
        int randomY = Random::Int(0, columns - 1);
        if (!boardVector[randomX][randomY].minePresent) {
            boardVector[randomX][randomY].minePresent = true;
            boardVector[randomX][randomY].debugging1 = debugging1;
//            boardVector[randomX][randomY].isHidden = false;
            count--;
        }
    }
    findNeighbors();
    adjMines();
}
//gets teh number of adjacent mines adn follows the conditionals based on that
void Board::adjMines() {
    //findNeighbors();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!boardVector[i][j].flagged && !boardVector[i][j].minePresent && boardVector[i][j].isHidden) {
                int count = 0;
                for (int k = 0; k < boardVector[i][j].neighbors.size(); k++) {
                    //count how many neighbors are mines
                    if (boardVector[i][j].neighbors[k]->minePresent) {
                        count++;
                        boardVector[i][j].adjMinesCount++;
                    }
                }
                if (count == 0) {
                    boardVector[i][j].adjMinesCount = 0;
                }
               else if (count == 1) {
                    boardVector[i][j].adjMinesCount = 1;
                    boardVector[i][j].adjMines1 = true;
                }
              else  if (count == 2) {
                    boardVector[i][j].adjMinesCount = 2;
                    boardVector[i][j].adjMines2 = true;
                }
               else if (count == 3) {
                    boardVector[i][j].adjMinesCount = 3;
                    boardVector[i][j].adjMines3 = true;
                }
               else if (count == 4) {
                    boardVector[i][j].adjMinesCount = 4;
                    boardVector[i][j].adjMines4 = true;
                }
              else  if (count == 5) {
                    boardVector[i][j].adjMinesCount = 5;
                    boardVector[i][j].adjMines5 = true;
                }
             else if (count == 6) {
                    boardVector[i][j].adjMinesCount = 6;
                    boardVector[i][j].adjMines6 = true;
                }
                else if (count == 7) {
                    boardVector[i][j].adjMinesCount = 7;
                    boardVector[i][j].adjMines7 = true;
                }
                else if (count == 8) {
                    boardVector[i][j].adjMinesCount = 8;
                    boardVector[i][j].adjMines8 = true;
                }
            }
        }
    }
}
//recursive reveal
void Board::recursive(vector<Tile*> neighbors) {
    for (int i = 0; i < neighbors.size(); i++) {
        if (neighbors.at(i) != nullptr) {
            if (!neighbors.at(i)->minePresent && neighbors.at(i)->adjMinesCount > 0 && neighbors.at(i)->isHidden &&
                !neighbors.at(i)->flagged && !neighbors.at(i)->flagged) {
                neighbors.at(i)->isHidden = false;
            } else if (!neighbors.at(i)->minePresent && neighbors.at(i)->adjMinesCount == 0 &&
                       neighbors.at(i)->isHidden && !neighbors.at(i)->flagged) {
                neighbors.at(i)->isHidden = false;
                recursive(neighbors.at(i)->neighbors);
            }
        }
    }
}
//click function, gets the mouse position and bounds of sprites
void Board::click(sf::RenderWindow &window, int x, int y, bool left) {
    playGame = true;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (left) {
                if (boardVector[i][j].tileHidden.getGlobalBounds().contains(x, y) && playGame) {
                    if (!boardVector[i][j].flagged && !boardVector[i][j].minePresent) {
                        adjMines();
                        if (boardVector[i][j].adjMinesCount == 0) {
                            recursive(boardVector[i][j].neighbors);
                        }
                        if (boardVector[i][j].minePresent && !boardVector[i][j].isHidden) {
                            playGame = false;
                          //  cout << "here";
                        }
                    }
                    if (!boardVector[i][j].flagged) {
                        boardVector[i][j].isHidden = false;

                        if (boardVector[i][j].minePresent) {
                            playGame = false;
                            boardVector[i][j].adjMinesCount = 0;
                           // cout << "false";
                        }
                    }
                }
                if (debug.getGlobalBounds().contains(x, y)) {
                    boardVector[i][j].debugging1 = !boardVector[i][j].debugging1;
                    debugging = !debugging;
                }
            }
            if (!left) {
                if (boardVector[i][j].tileHidden.getGlobalBounds().contains(x, y)) {
                    if(boardVector[i][j].isHidden && !win){
                        boardVector[i][j].flagged = !boardVector[i][j].flagged;
                        if(boardVector[i][j].flagged){
                            flagsPlaced++;
                            cout << flagsPlaced;
                        }
                       if(!boardVector[i][j].flagged){
                           flagsPlaced--;
                       }
                    }

                }
            }
        }
    }
}
//checks if the game is won
void Board::checkWin() {
    tilesRevealed = 0;
    mineCount = 0;
    tileCount = rows*columns;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(!boardVector[i][j].isHidden && !boardVector[i][j].minePresent){
                tilesRevealed++;
            }
           if(boardVector[i][j].minePresent){
               mineCount++;
           }
        }
    }
//   cout <<tilesRevealed<< endl;
//   cout << tileCount << endl;
//
//   cout << flagsPlaced << endl;
//   cout <<tilesRevealed - mineCount;
       if(tileCount == tilesRevealed + flagsPlaced || tilesRevealed - mineCount == tileCount){
       win = true;
       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < columns; j++) {
               if (boardVector[i][j].minePresent) {
                   boardVector[i][j].flagged = true;
                   boardVector[i][j].debugging1 = false;
                   boardVector[i][j].adjMinesCount = 0;
               }
           }
       }
   }
}
//find the adjacent tiles
void Board::findNeighbors() {
            playGame = true;
            win = false;
            tileCount = rows * columns;
            tilesRevealed = 0;
            flagsPlaced = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //for a tile with adjacent mines on all sides, not on edge
            if (i > 0 && j > 0 && i < rows - 1 && j < columns - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j]);
                //tile with one edge top
            } else if (i == 0 && j != 0 && j != columns - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j]);
                //tile with one edge on sides
            } else if (i == rows - 1 && j != 0 && j != columns - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j + 1]);
                //tile with edge side
            } else if (i > 0 && j == 0 && i < rows - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j]);

            } else if (j == columns - 1 && i > 0 && i < rows - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j]);
                //corner tile, (0,0)
            } else if (j == 0 && i == 0) {
                boardVector[i][j].neighbors.push_back(&boardVector[i][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j]);
                //tile is in last column and top row
            } else if (j == columns - 1 && i == 0) {
                boardVector[i][j].neighbors.push_back(&boardVector[i][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i + 1][j]);
                //first column and last row
            } else if (j == 0 && i == rows - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j + 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j + 1]);
                //second to last column and second to last row
            } else if (j == columns - 1 && i == rows - 1) {
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i][j - 1]);
                boardVector[i][j].neighbors.push_back(&boardVector[i - 1][j]);
            }
        }
    }
}
//sets the texture for the digit strip counter
void Board::digitsCounter() {
    for(int i = 0; i < 11; i++) {
        digitStrip[i].setTexture(Textures::GetTexture("digits"));
        digitStrip[i].setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
    }
}
//gets the leftover mines
void Board::leftoverMines() {
    count.clear();
    int leftOverMines = mines - flagsPlaced;

    if (leftOverMines < 0) {
        count.push_back(digitStrip[10]);
    }

    int one = abs(leftOverMines/100) % 10;
    int two = abs(leftOverMines/10) % 10;
    int three = abs(leftOverMines) % 10;

    addDigit(one);
    addDigit(two);
    addDigit(three);

    for(int i = 0; i < count.size(); i++) {
        count[i].setPosition(sf::Vector2f(i * 21, rows * 32));
    }
}
//appends a digit to the strip
void Board::addDigit(int digit) {
    count.push_back(digitStrip[digit]);
}
