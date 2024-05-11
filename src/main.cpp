#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "HelperMethods.h"
#include "Board.h"
#include "Tile.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(),"Minesweeper",sf::Style::Close|sf::Style::Titlebar);
    sf::RectangleShape background(sf::Vector2f(25*32, 16*32));
    background.setFillColor(sf::Color(200, 200, 200));
    Board b = Board(25,16);
    sf::Sprite smile(HelperMethods::GetTexture("face_happy"));
    smile.setPosition(710, 790);
    sf::Sprite debug(HelperMethods::GetTexture("debug"));
    debug.setPosition(730, 790);
    sf::Sprite test1(HelperMethods::GetTexture("test_1"));
    test1.setPosition(750, 790);
    sf::Sprite test2(HelperMethods::GetTexture("test_2"));
    test2.setPosition(770, 790);
    sf::Sprite test3(HelperMethods::GetTexture("test_3"));
    test3.setPosition(790, 790);

    sf::Texture digitTexture = HelperMethods::GetTexture("digits");
    vector<sf::IntRect> digitRects;
    for (int i = 0; i < 211; i += 21)
        digitRects.push_back(sf::IntRect(i, 0, 21, 32));
    vector<int> nums = HelperMethods::digitizer(b.GetMs());
    vector<sf::Sprite> digitDisplay;
    for (int i = 0, j = 50; i < 3; i++) {
        digitDisplay.push_back(sf::Sprite(digitTexture));
        digitDisplay.at(i).setPosition(j, 512);
        j += 21;
        digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
    }
    while (window.isOpen())
    {
        // ======== Startup ======== /
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window Close Logic
            if (event.type == sf::Event::Closed)
                window.close();

                // Mouse Button Press Capture
            else if (event.type == sf::Event::MouseButtonPressed) {

                // Left Button
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    // Reveal Tile Logic
                    if (position.y < 512) {
                        Tile* currentSpot = &b.GetT(25 * (position.y / 32) + (position.x / 32));
                        b.ShowT(currentSpot);
                        b.GetEnd();
                        if (b.GetWin()) {
                            smile.setTexture(HelperMethods::GetTexture("face_win"));
                            for (int i = 0; i < 3; i++) {
                                nums.at(i) = 0;
                                digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
                            }
                        }
                        if (b.GetEnd())
                            smile.setTexture(HelperMethods::GetTexture("face_lose"));
                    }

                        // Debug Button Logic
                    else if ((position.x > 499 && position.x < 564) &&
                             (position.y > 512 && position.y < 576))
                        b.SetDebug();


                        // New Board Buttons Logic
                        // Load Board 1
                    else if ((position.x > 563 && position.x < 628)
                             && (position.y > 512 && position.y < 576)) {
                        b.Start(1);
                        smile.setTexture(HelperMethods::GetTexture("face_happy"));
                        nums = HelperMethods::digitizer(b.GetMs() - b.GetFs());
                        for (int i = 0; i < 3; i++)
                            digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
                    }
                        // Load Board 2
                    else if ((position.x > 627 && position.x < 692)
                             && (position.y > 512 && position.y < 576)) {
                        b.Start(2);
                        smile.setTexture(HelperMethods::GetTexture("face_happy"));
                        nums = HelperMethods::digitizer(b.GetMs() - b.GetFs());
                        for (int i = 0; i < 3; i++)
                            digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
                    }
                        // Load Board 3
                    else if ((position.x > 691 && position.x < 756)
                             && (position.y > 512 && position.y < 576)) {
                        b.Start(3);
                        smile.setTexture(HelperMethods::GetTexture("face_happy"));
                        nums = HelperMethods::digitizer(b.GetMs() - b.GetFs());
                        for (int i = 0; i < 3; i++)
                            digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
                    }

//                         Smiley Button Logic
                    else if ((position.x > 349 && position.x < 414)&& (position.y > 512 && position.y < 576)) {
                        b.StartRandom();    // THIS NEEDS TO BE THE REAL WAY TO START
                        smile.setTexture(HelperMethods::GetTexture("face_happy"));
                        nums = HelperMethods::digitizer(b.GetMs() - b.GetFs());
                        for (int i = 0; i < 3; i++)
                            digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
                    }
                }

                    // Right Button
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    // Flag Logic
                    if (position.y < 512) {
                        Tile* currentSpot = &b.GetT(25 * (position.y / 32) + (position.x / 32));
                        b.ShowF(currentSpot);
                        nums = HelperMethods::digitizer(b.GetMs() - b.GetFs());
                        for (int i = 0; i < 3; i++)
                            digitDisplay.at(i).setTextureRect(digitRects.at(nums.at(i)));
                    }
                }
            }
        }

        // ======== Draw ========================================== /


        // 1. Clear -- ONLY CALL ONCE!
        window.clear();

        // 2. Draw

        window.draw(background);
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.draw(smile);
        for (int i = 0; i < 3; i++)
            window.draw(digitDisplay.at(i));

        for (unsigned int i = 0; i < b.GetW()*b.GetH(); i++) {
            window.draw(b.GetT(i).GetSprite());
        }

        // 3. Display -- ONLY CALL ONCE!
        window.display();
    }

    // ======== Clean Up ========================================== /
    HelperMethods::Clear();
    return 0;
}