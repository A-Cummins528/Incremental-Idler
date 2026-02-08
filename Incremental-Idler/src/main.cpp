#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Coin.h"
#include "Cafe.h"
#include "Mine.h"
#include "Bank.h"
#include "SaveSystem.h"
#include "FloatingText.h"
#include "Utils.h"


int main()
{
    // Setup Window
    sf::RenderWindow window(sf::VideoMode(800, 700), "Incremental Idler");
    window.setFramerateLimit(60);


    // --- LOAD ASSETS ---
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) return -1;

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("assets/images/coin.png")) return -1;

    // TO DO: load these directly into the vector creation
    sf::Texture cafeTexture, mineTexture, bankTexture;
    if (!cafeTexture.loadFromFile("assets/images/cafe.png")) return -1;
    if (!mineTexture.loadFromFile("assets/images/mine.png")) return -1;
    if (!bankTexture.loadFromFile("assets/images/bank.png")) return -1;


	// --- AUDIO ---
    sf::SoundBuffer coinBuffer, purchaseBuffer;
    if (!coinBuffer.loadFromFile("assets/audio/coin.mp3")) return -1;
    if (!purchaseBuffer.loadFromFile("assets/audio/purchase.mp3")) return -1;

    sf::Sound coinSound, purchaseSound;
    coinSound.setBuffer(coinBuffer);
    coinSound.setVolume(50.f);
    purchaseSound.setBuffer(purchaseBuffer);
    purchaseSound.setVolume(50.f);


    // --- OBJECTS ---
    Coin myCoin(400.f, 300.f, coinTexture);

    // The Shop List
    std::vector<std::unique_ptr<Building>> shop;
    shop.push_back(std::make_unique<Cafe>(110.f, 490.f, cafeTexture));
    shop.push_back(std::make_unique<Mine>(310.f, 490.f, mineTexture));
    shop.push_back(std::make_unique<Bank>(510.f, 490.f, bankTexture));

    // --- LOAD GAME ---
    long long score = 0;
    loadGame(score, shop);


    // --- UI TEXT SETUP ---
    
    // Title Text
    sf::Text titleText("Coin Clicker", font, 36);
    titleText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    titleText.setPosition(400.f, 50.f);

    // Score Text
    sf::Text scoreText("Coins: 0", font, 24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10.f, 10.f);

	// Passive Income Text
    sf::Text incomeText("Coins per second: 0", font, 24);
    incomeText.setFillColor(sf::Color::Black);
    incomeText.setPosition(10.f, 34.f);
    
    // Dynamic Shop Texts (One for each building)
    std::vector<sf::Text> shopLabels;
    for (size_t i = 0; i < shop.size(); i++) {
        sf::Text t("", font, 18);
        t.setFillColor(sf::Color::Black);
        // Position it below the specific building (assuming Y=490 is center)
        // Offset Y by +60 to be under the sprite
        t.setPosition(shop[i]->getSpritePosition().x - 50, 490.f + 60.f);
        shopLabels.push_back(t);
    }

    std::vector<FloatingText> floatingTexts;
    sf::Clock passiveIncomeClock;
    sf::Clock frameClock; // For floating text updates
    float timeAccumulator = 0.0f; // Stores time passed
    long long incomePerSecond = 0;


    // --- Game Loop ---
    while (window.isOpen())
    {
        // Calculate Time Passed
        sf::Time frameTime = frameClock.restart();
        float dt = frameTime.asSeconds();
        
        // Calculate Income Per Second
        incomePerSecond = 0;
        for (const auto& building : shop) {
            incomePerSecond += building->getIncomePerSecond();
        }

        // Passive Income Timer
        timeAccumulator += dt;
        if (timeAccumulator >= 1.0f)
        {
            score += incomePerSecond;
            timeAccumulator -= 1.0f;
        }
        
		// Update Floating Text
        for (int i = 0; i < floatingTexts.size(); i++) {
            if (!floatingTexts[i].update(dt)) {
                floatingTexts.erase(floatingTexts.begin() + i);
                i--;
            }
        }

        // Events
        sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    saveGame(score, shop);
                    window.close();
                }

                // Mouse Pressed
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // Coin Clicked
                        if (myCoin.isClicked(mousePos))
                        {
                            score++;
                            myCoin.shrink();
                            coinSound.play();
                            floatingTexts.push_back(FloatingText(mousePos.x, mousePos.y, "+1", font));
                        }

						// --- Building Click ---
                        for (auto& building : shop) 
                        {
                            if (building->isClicked(mousePos)) 
                            {
                                building->shrink();

                                if (score >= building->getCost()) 
                                {
                                    long long cost = building->getCost();
                                    score -= cost;
                                    building->purchase();
                                    purchaseSound.play();

                                    std::string costString = "-" + std::to_string(cost);
                                    floatingTexts.push_back(FloatingText(mousePos.x, mousePos.y, costString, font, sf::Color::Red, 50.0f));
                                }
                                else 
                                {
                                    std::cout << "Not enough coins for " << building->getClassName() << "!" << std::endl;
                                }                           
                            }
						}                       
                    }
                }
                        
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    myCoin.resetScale();                           
                    for (const auto& building : shop) 
                    {
                        building->resetScale();
                    }                                                
                }                         
            }

        // --- UPDATE TEXTS ---
        scoreText.setString("Coins: " + Utils::formatNumber(score));
        incomeText.setString("Coins/s: " + Utils::formatNumber(incomePerSecond));

        // Update the label for each building in the loop
        for (size_t i = 0; i < shop.size(); i++) {
            std::string s = shop[i]->getClassName() + 
                            "\nOwned: " + std::to_string(shop[i]->getOwnedCount()) + 
                            "\nCost: " + Utils::formatNumber(shop[i]->getCost());
            shopLabels[i].setString(s);
        }

        // --- RENDER ---
        window.clear(sf::Color::White);

        // Draw Buildings
        for (auto& building : shop) {
            building->draw(window);
        }

        window.draw(titleText);
        window.draw(scoreText);
		window.draw(incomeText);

        for (auto& label : shopLabels) {
            window.draw(label);
        }

        myCoin.draw(window);

        for (auto& txt : floatingTexts) {
            txt.draw(window);
        }

        window.display();
    }
    return 0;
}