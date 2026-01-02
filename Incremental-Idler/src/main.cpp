#include <SFML/Graphics.hpp>
#include <iostream>
#include "Coin.h"
#include "Cafe.h"
#include "SaveSystem.h"

int main()
{
    std::cout << "Hello World!\n";

    // Setup Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Incremental Idler");
    window.setFramerateLimit(60);


    // --- Load Assets ---

    // Font
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }


    // --- Object Creation ---

    // Coin
    Coin myCoin(400.f, 300.f);

    // Cafe
    Cafe myCafe(100.f, 500.f);


    // -- Load Game ---
    
    long long score = loadGame();

    // Title Text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Coin Clicker");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = titleText.getLocalBounds(); // Centre Text
    titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    titleText.setPosition(400.f, 50.f); // Middle X, Top Y

    // Score Text
    // int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Coins: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10.f, 10.f); // Top Left corner

    // --- Game Loop ---
    while (window.isOpen())
    {
        sf::Event event;
            while (window.pollEvent(event))
        {
                if (event.type == sf::Event::Closed)
                {
                    saveGame(score);
                    window.close();
                }

                // Mouse Pressed
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        if (myCoin.isClicked(mousePos))
                        {
                            score++;
                            scoreText.setString("Coins: " + std::to_string(score));
                            myCoin.shrink();
                        }

                        if (myCafe.isClicked(mousePos))
                        {
                            score = score + 100;
                            scoreText.setString("Coins: " + std::to_string(score));
                            myCafe.shrink();
                        }
                    }
                }

                // Mouse Released
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    myCoin.resetScale();
					myCafe.resetScale();
                }
            }

        // Render
        window.clear(sf::Color::White);
        myCoin.draw(window);
		myCafe.draw(window);
        window.draw(titleText);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}