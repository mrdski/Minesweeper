//
// Created by Matthew Dylewski on 4/18/22.
//

#include "Tile.h"
Tile::CTile Tile::GetCT() {return ct;}
Tile::TrueT Tile::GetTT() {return tt;}
void Tile::SetCT(CTile ct) {this->ct=ct;}
void Tile::SetTT(TrueT tt) {this->tt=tt;}
Tile::Tile(sf::Vector2f p, char *text, TrueT tt) {
    sprite=sf::Sprite(HelperMethods::GetTexture(text));
    sprite.setPosition(pos.x,pos.y);
    pos=p;
    ct=CTile::HIDDEN;
    this->tt=tt;
    click=true;
    flag=true;
}
void Tile::SetClick(bool c) {click=c;}
void Tile::SetFlag(bool f) {flag=f;}
void Tile::SetSprite(char *texture) {
    sprite.setTexture(HelperMethods::GetTexture(texture));
    sprite.setPosition(pos);
}
sf::Sprite& Tile::GetSprite() {return sprite;}
Tile* Tile::GetATS(unsigned int n) {return ats.at(n);}
unsigned int Tile::atsNum() {return ats.size();}
void Tile::AddAT(Tile *n) {ats.push_back(n);}
void Tile::WFlag(bool t) {
    if(flag){
        if(ct==CTile::HIDDEN){
            SetSprite("flag");
            click=false;
            ct=CTile::FLAGGED;
        }
        else if(t and tt==TrueT::MINE and ct==CTile::FLAGGED){
            SetSprite("mine");
            click=true;
            ct=CTile::HIDDEN;
        }
        else{
            SetSprite("tile_hidden");
            click=true;
            ct=CTile::HIDDEN;
        }
    }
}
bool Tile::WhatIs() {
    if(click){
        if(ct==CTile::HIDDEN){
            switch(tt){
                case TrueT::ONE:
                    SetSprite("number_1");
                    return false;
                case TrueT::TWO:
                    SetSprite("number_2");
                    break;
                case TrueT::THREE:
                    SetSprite("number_3");
                    break;
                case TrueT::FOUR:
                    SetSprite("number_4");
                    break;
                case TrueT::FIVE:
                    SetSprite("number_5");
                    break;
                case TrueT::SIX:
                    SetSprite("number_6");
                    break;
                case TrueT::SEVEN:
                    SetSprite("number_7");
                    break;
                case TrueT::EIGHT:
                    SetSprite("number_8");
                    break;
                case TrueT::MINE:
                    SetSprite("mine");
                    return true;
                    break;
                default:
                    SetSprite("tile_revealed");
                    for(int i = 0; i < atsNum();i++){
                        GetATS(i)->WhatIs();
                    }
                    break;
            }
        }
    }
    return false;
}