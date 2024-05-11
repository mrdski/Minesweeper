//
// Created by Matthew Dylewski on 4/18/22.
//

#ifndef PROJECT3_TILE_H
#define PROJECT3_TILE_H
#include <iostream>
#include "HelperMethods.h"
#include "SFML/Graphics.hpp"
using namespace std;
class Tile{
    sf::Vector2f pos;
    vector<Tile*> ats;
    sf::Sprite sprite;
    bool click;
    bool flag;
public:
    enum class CTile{HIDDEN,REVEALED,FLAGGED};
    CTile ct;
    CTile GetCT();
    void SetCT(CTile c);
    enum class TrueT{ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,EMPTY,MINE,FLAG};
    TrueT tt;
    TrueT GetTT();
    void SetTT(TrueT ts);
    Tile(sf::Vector2f p, char* text, TrueT t);
    void SetClick(bool c);
    void SetFlag(bool f);
    void SetSprite(char* texture);
    sf::Sprite& GetSprite();
    Tile* GetATS(unsigned int n);
    bool WhatIs();
    unsigned int atsNum();
    void AddAT(Tile* n);
    void WFlag(bool t);

};
#endif //PROJECT3_TILE_H
