#include <SFML/Graphics.hpp>
#include <iostream>
#include "Coin.h"
#include "Cafe.h"
#include "SaveSystem.h"


int main()
{
    // Setup Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Incremental Idler");
    window.setFramerateLimit(60);


    // --- Load Assets ---

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) return -1;

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("assets/images/coin.png")) return -1;

    sf::Texture cafeTexture;
    if (!cafeTexture.loadFromFile("assets/images/cafe.png")) return -1;


    // --- Object Creation ---

    Coin myCoin(400.f, 300.f, coinTexture);
    Cafe myCafe(110.f, 490.f, cafeTexture);


    // -- Load Game ---
    
    // 1. Create variables to hold the loaded data
    long long score = 0;
    int loadedCafeCount = 0;

    // 2. Pass them into the loader
    loadGame(score, loadedCafeCount);

    // 3. Update the Cafe object with the loaded count
	myCafe.setOwnedCount(loadedCafeCount);


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
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Coins: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10.f, 10.f); // Top Left corner

    // Cafe Info Text (To show price/owned)
    sf::Text cafeText;
    cafeText.setFont(font);
    cafeText.setCharacterSize(18);
    cafeText.setFillColor(sf::Color::Black);
    cafeText.setPosition(50.f, 550.f); // Below the cafe sprite


    // --- PASSIVE INCOME TIMER ---
    sf::Clock passiveIncomeClock;
    float timeAccumulator = 0.0f; // Stores time passed

    // --- Game Loop ---
    while (window.isOpen())
    {
        // Calculate Time Passed
        sf::Time dt = passiveIncomeClock.restart();
        timeAccumulator += dt.asSeconds();

		// Every second, add passive income
        if (timeAccumulator >= 1.0f)
        {
            score += myCafe.getIncomePerSecond();
            timeAccumulator -= 1.0f; // Reset timer
        }
        
        sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    saveGame(score, myCafe.getOwnedCount()); 
                    window.close();
                }

                // Mouse Pressed
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // Click Coin
                        if (myCoin.isClicked(mousePos))
                        {
                            score++;
                            myCoin.shrink();
                        }

                        // Buy Cafe
                        if (myCafe.isClicked(mousePos))
                        {
                            if (score >= myCafe.getCost())
                            {
                                score -= myCafe.getCost();
                                myCafe.purchase();
                                std::cout << "Cafe Purchased!" << std::endl;
                                myCafe.shrink();
                            }
                            else
                            {
                                std::cout << "Not enough coins to purchase Cafe!" << std::endl;
							}
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

        // --- Update UI Text ---
        scoreText.setString("Coins: " + std::to_string(score));

        std::string cafeString = "Cafe (Owned: " + std::to_string(myCafe.getOwnedCount()) + ")\nCost: " + std::to_string(myCafe.getCost());
        cafeText.setString(cafeString);

        // --- Render ---
        window.clear(sf::Color::White);
        myCoin.draw(window);
		myCafe.draw(window);
        window.draw(titleText);
        window.draw(scoreText);
		window.draw(cafeText);
        window.display();
    }

    return 0;
}