//
// Created by Matthew Dylewski on 4/18/22.
//

#include "HelperMethods.h"
unordered_map<string, sf::Texture> HelperMethods::textures;
void HelperMethods::LoadTexture(string t) {
    string p = "images/";
    p = p + t + ".png";
    textures[t].loadFromFile((p));
}
sf::Texture& HelperMethods::GetTexture(string t) {
    if(textures.find(t)==textures.end()){
        LoadTexture(t);
    }
    return textures[t];
}
void HelperMethods::Clear() {
    textures.clear();
}
vector<int> HelperMethods::digitizer(int number) {
    vector<int> nums;

    // Can't handle < -99
    if (number < -99) {
        nums.push_back(10);
        nums.push_back(9);
        nums.push_back(9);
    }

        // -99 to -10
    else if (number < -9) {
        nums.push_back(10);
        int temp = (number * -1) / 10;
        nums.push_back(temp);
        temp = (number * -1) % 10;
        nums.push_back(temp);
    }

        // - 9 to -1
    else if (number < 0) {
        nums.push_back(10);
        nums.push_back(0);
        nums.push_back(number * -1);
    }

        // 0 to 9
    else if (number < 10) {
        nums.push_back(0);
        nums.push_back(0);
        nums.push_back(number);
    }

        // 10 to 99
    else if (number < 100) {
        nums.push_back(0);
        int temp = number / 10;
        nums.push_back(temp);
        temp = number % 10;
        nums.push_back(temp);
    }

        // 100 to 999 <- In our version, max is 400
    else if (number < 1000) {
        int temp = number / 100;
        nums.push_back(temp);
        temp = number % 100;
        temp /= 10;
        nums.push_back(temp);
        temp = number % 10;
        nums.push_back(temp);
    }

        // Unnecessary for our game but just in case, max at 999
    else if (number > 999) {
        nums.push_back(9);
        nums.push_back(9);
        nums.push_back(9);
    }

    return nums;
}