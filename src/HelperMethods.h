//
// Created by Matthew Dylewski on 4/18/22.
//

#ifndef PROJECT3_HELPERMETHODS_H
#define PROJECT3_HELPERMETHODS_H
#include <iostream>
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <fstream>
using namespace std;
class HelperMethods{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string t);
public:
    static sf::Texture& GetTexture(string texture);
    static void Clear();

    static vector<char> read(int f);
    static vector<int> digitizer(int n);
};
#endif //PROJECT3_HELPERMETHODS_H
