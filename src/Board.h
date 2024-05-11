//
// Created by Matthew Dylewski on 4/18/22.
//

#ifndef PROJECT3_BOARD_H
#define PROJECT3_BOARD_H
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Board{
    unsigned int ms=0;
    unsigned int fs=0;
    unsigned int w;
    unsigned int h;
    vector<Tile> board;
    bool end = false;
    bool win = false;
    bool debug = false;
public:
    Board(unsigned int w, unsigned int h);
    void Start(unsigned int s);
    void StartRandom();
    Tile& GetT(unsigned int t);
    unsigned int GetW();
    unsigned int GetH();
    bool GetEnd();
    bool GetWin();
    unsigned int GetMs();
    unsigned int GetFs();
    void SetEnd(bool e);
    void SetWin(bool w);
    void ShowT(Tile* t);
    void ShowF(Tile* t);
    void SetATSs();
    void SetNums();
    void SetDebug();
};
#endif //PROJECT3_BOARD_H
