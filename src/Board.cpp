//
// Created by Matthew Dylewski on 4/18/22.
//

#include "Board.h"
#include "Random.h"
Board::Board(unsigned int w, unsigned int h){
    this->w=w;
    this->h=h;
}
void Board::Start(unsigned int s){
    string filename = "boards/testboard"+to_string(s)+".brd";
    vector<char> mines;
    ifstream f(filename);
    char n;
    for(int i=0;i<16;i++){
        for(int k=0;k<25;k++){
            f.get(n);
            mines.push_back(n);
        }
    }
    f.close();
    for(unsigned int i=0;i<h;i++){
        for(unsigned int k=0;k<w;k++){
            Tile::TrueT tt;
            sf::Vector2f pos = sf::Vector2f(k*32,i*32);
            switch(mines.at(w*i+k)){
                case '1':
                    tt=Tile::TrueT::MINE;
                    ms++;
                    break;
                default:
                    tt=Tile::TrueT::EMPTY;
                    break;
            }
            if(debug and tt==Tile::TrueT::MINE){
                board.push_back(Tile(pos,"mine",tt));
            }
            else{
                board.push_back(Tile(pos,"tile_hidden",tt));
            }
        }
    }
    SetATSs();
    SetNums();
}
Tile& GetT(unsigned int t);
unsigned int Board::GetW(){
    return w;
}
unsigned int Board::GetH(){
    return h;
}
bool Board::GetEnd(){
    return end;
}
bool Board::GetWin(){
    return win;
}
unsigned int Board::GetMs(){
    return ms;
}
unsigned int Board::GetFs(){
    for(unsigned int i=0; i<w*h;i++){
        if(board.at(i).GetCT()==Tile::CTile::FLAGGED){fs++;}
    }
    return fs;
}
void Board::SetEnd(bool e){
    end=e;
}
void Board::SetWin(bool w){
    win=w;
}
void Board::ShowT(Tile* t){
    if(t->WhatIs()){ SetEnd(true);}
}
void Board::ShowF(Tile* t){
    t->SetFlag(debug);
}
void Board::SetATSs(){
    for (unsigned int i = 0; i < board.size(); i++) {
        // Corners - 3 Neighbors ----------------------//
        // Top Left
        if (i == 0) {
            board.at(i).AddAT(&board.at(1));
            board.at(i).AddAT(&board.at(w));
            board.at(i).AddAT(&board.at(w + 1));
        }
            // Top Right
        else if (i == w - 1) {
            board.at(i).AddAT(&board.at(i - 2));
            board.at(i).AddAT(&board.at(i * 2));
            board.at(i).AddAT(&board.at((i * 2) + 1));
        }
            // Bottom Left
        else if (i == (w * h) - w) {
            board.at(i).AddAT(&board.at(i - w));
            board.at(i).AddAT(&board.at(i - w + 1));
            board.at(i).AddAT(&board.at(i + 1));
        }
            // Bottom Right
        else if (i == (w * h) - 1) {
            board.at(i).AddAT(&board.at(i - w));
            board.at(i).AddAT(&board.at(i - w - 1));
            board.at(i).AddAT(&board.at(i - 1));
        }

            // Edges - 5 Neighbors ----------------------//
            // Top Edge
        else if (i > 0 && i < w - 1) {
            board.at(i).AddAT(&board.at(i - 1));
            board.at(i).AddAT(&board.at(i + 1));
            board.at(i).AddAT(&board.at(i + w - 1));
            board.at(i).AddAT(&board.at(i + w));
            board.at(i).AddAT(&board.at(i + w + 1));
        }
            // Bottom Edge
        else if (i > (w * h) - w && i < (w * h) - 1) {
            board.at(i).AddAT(&board.at(i - w - 1));
            board.at(i).AddAT(&board.at(i - w));
            board.at(i).AddAT(&board.at(i - w + 1));
            board.at(i).AddAT(&board.at(i - 1));
            board.at(i).AddAT(&board.at(i + 1));
        }
            // Left Edge
        else if (i % w == 0) {
            board.at(i).AddAT(&board.at(i + 1));
            board.at(i).AddAT(&board.at(i + 1 - w));
            board.at(i).AddAT(&board.at(i + 1 + w));
            board.at(i).AddAT(&board.at(i + w));
            board.at(i).AddAT(&board.at(i - w));
        }
            // Right Edge
        else if ((i + 1) % w == 0) {
            board.at(i).AddAT(&board.at(i - 1));
            board.at(i).AddAT(&board.at(i - w));
            board.at(i).AddAT(&board.at(i + w));
            board.at(i).AddAT(&board.at(i - 1 - w));
            board.at(i).AddAT(&board.at(i - 1 + w));
        }

            // All Others - 8 Neighbors ----------------------//
        else {
            board.at(i).AddAT(&board.at(i - 1));
            board.at(i).AddAT(&board.at(i - 1 + w));
            board.at(i).AddAT(&board.at(i - 1 - w));
            board.at(i).AddAT(&board.at(i + 1));
            board.at(i).AddAT(&board.at(i + 1 + w));
            board.at(i).AddAT(&board.at(i + 1 - w));
            board.at(i).AddAT(&board.at(i + w));
            board.at(i).AddAT(&board.at(i - w));
        }
    }
}
void Board::SetNums(){
    for (unsigned int i = 0; i < board.size(); i++) {

        // Check if not mine
        if (board.at(i).GetTT() != Tile::TrueT::MINE) {
            int count = 0;

            // Check each neighbor for mines, incrementing count
            for (unsigned int j = 0; j < board.at(i).atsNum(); j++) {
                Tile* t = board.at(i).GetATS(j);
                if (t->GetTT() == Tile::TrueT::MINE)
                    count++;
            }

            // Set numbers
            if (count == 1)
                board.at(i).SetTT(Tile::TrueT::ONE);
            else if (count == 2)
                board.at(i).SetTT(Tile::TrueT::TWO);
            else if (count == 3)
                board.at(i).SetTT(Tile::TrueT::THREE);
            else if (count == 4)
                board.at(i).SetTT(Tile::TrueT::FOUR);
            else if (count == 5)
                board.at(i).SetTT(Tile::TrueT::FIVE);
            else if (count == 6)
                board.at(i).SetTT(Tile::TrueT::SIX);
            else if (count == 7)
                board.at(i).SetTT(Tile::TrueT::SEVEN);
            else if (count == 8)
                board.at(i).SetTT(Tile::TrueT::EIGHT);

                // Else, set to empty
            else
                board.at(i).SetTT(Tile::TrueT::EMPTY);
        }
    }
}
void Board::SetDebug(){
    if (debug)
        debug = false;
    else
        debug = true;
    if (!end && !win) {
        for (unsigned int i = 0; i < GetW()*GetH(); i++) {
            if (debug && board.at(i).GetTT() == Tile::TrueT::MINE)
                board.at(i).SetSprite("mine");
            else if (!debug && board.at(i).GetCT() == Tile::CTile::FLAGGED)
                board.at(i).SetSprite("flag");
            else if (!debug && board.at(i).GetTT() == Tile::TrueT::MINE)
                board.at(i).SetSprite("tile_hidden");
        }
    }
}
Tile& Board::GetT(unsigned int t){
    return board.at(t);
}
void Board::StartRandom() {

    // Generate random mine positions
    vector<int> randoMines;
    randoMines.push_back(Random::Int(0, 399));
    while (randoMines.size() < 50) {
        int x = Random::Int(0,399);
        bool dup = false;
        for (unsigned int i = 0; i < randoMines.size(); i++) {
            if (x == randoMines.at(i)) {
                dup = true;
                break;
            }
        }
        if (dup == false)
            randoMines.push_back(x);
    }

    // Initialize Board
    end = false;
    win = false;
    board.clear();
    ms = 0;
    fs = 0;

    // Create board vector of tiles. Each tile 32x32
    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < w; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32);
            Tile::TrueT tt = Tile::TrueT::EMPTY;
            board.push_back(Tile(position, "tile_hidden", tt));
        }
    }

    // Set Bombs from Random List
    for (unsigned int i = 0; i < randoMines.size(); i++) {
        board.at(randoMines.at(i)).SetTT(Tile::TrueT::MINE);
        ms++;
        if (debug)
            board.at(randoMines.at(i)).SetSprite("mine");
    }

    // Utilize Neighbor and Number Methods
    SetATSs();
    SetNums();
}