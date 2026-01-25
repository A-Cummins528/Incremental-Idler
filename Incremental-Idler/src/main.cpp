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

	sf::Texture mineTexture;
	if (!mineTexture.loadFromFile("assets/images/mine.png")) return -1;

    sf::Texture bankTexture;
    if (!bankTexture.loadFromFile("assets/images/bank.png")) return -1;


	// --- AUDIO SETUP ---

    // 1. Coin Click
    sf::SoundBuffer coinBuffer;
    if (!coinBuffer.loadFromFile("assets/audio/coin.mp3")) return -1;

    sf::Sound coinSound;
    coinSound.setBuffer(coinBuffer);
    coinSound.setVolume(50.f);

	// 2. Purchase Sound
    sf::SoundBuffer purchaseBuffer;
    if (!purchaseBuffer.loadFromFile("assets/audio/purchase.mp3")) return -1;

    sf::Sound purchaseSound; 
    purchaseSound.setBuffer(purchaseBuffer);
    purchaseSound.setVolume(50.f);



    // --- Object Creation ---

   // Coin myCoin(400.f, 300.f, coinTexture);
  //  Cafe myCafe(110.f, 490.f, cafeTexture);
	//Mine myMine(310.f, 490.f, mineTexture);
	//Bank myBank(510.f, 490.f, bankTexture);


    // The Shop List
    std::vector<std::unique_ptr<Building>> shop;

    shop.push_back(std::make_unique<Cafe>(110.f, 490.f, cafeTexture));
    shop.push_back(std::make_unique<Mine>(310.f, 490.f, mineTexture));
    shop.push_back(std::make_unique<Bank>(510.f, 490.f, bankTexture));

    // -- Load Game ---
    
    // 1. Create variables to hold the loaded data
    long long score = 0;
	long long incomePerSecond = 0;
    int loadedCafeCount = 0;
	long long loadedCafeCost = 1000; // Default cost if no save exists
	int loadedMineCount = 0;
	long long loadedMineCost = 10000; // Default cost if no save exists
	int loadedBankCount = 0;
	long long loadedBankCost = 100000; // Default cost if no save exists

    // 2. Pass them into the loader
    loadGame(score, loadedCafeCount, loadedCafeCost, loadedMineCount, loadedMineCost, loadedBankCount, loadedBankCost);

    // 3. Update the Cafe object with the loaded count
	myCafe.setOwnedCount(loadedCafeCount);
	myCafe.setCost(loadedCafeCost);
	myMine.setOwnedCount(loadedMineCount);
	myMine.setCost(loadedMineCost);
	myBank.setOwnedCount(loadedBankCount);
	myBank.setCost(loadedBankCost);


    // --- TEXT MANAGER ---
    std::vector<FloatingText> floatingTexts;  // To store all active "+1"s

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

	// Passive Income Text
    sf::Text incomeText;
    incomeText.setFont(font);
    incomeText.setString("Coins per second: " + std::to_string(incomePerSecond));
    incomeText.setCharacterSize(24);
    incomeText.setFillColor(sf::Color::Black);
    incomeText.setPosition(10.f, 34.f); // Top Left corner

    // Cafe Info Text
    sf::Text cafeText;
    cafeText.setFont(font);
    cafeText.setCharacterSize(18);
    cafeText.setFillColor(sf::Color::Black);
    cafeText.setPosition(50.f, 550.f); // Below the cafe sprite

	// Mine Info Text
	sf::Text mineText;
	mineText.setFont(font);
	mineText.setCharacterSize(18);
	mineText.setFillColor(sf::Color::Black);
	mineText.setPosition(250.f, 550.f); // Below the mine sprite

	// Bank Info Text
	sf::Text bankText;
	bankText.setFont(font);
	bankText.setCharacterSize(18);
	bankText.setFillColor(sf::Color::Black);
	bankText.setPosition(450.f, 550.f); // Below the bank sprite


    // --- CLOCKS ---
    sf::Clock passiveIncomeClock;
	sf::Clock frameClock; // For floating text updates
    float timeAccumulator = 0.0f; // Stores time passed

    // --- Game Loop ---
    while (window.isOpen())
    {
		// Calculate Income Per Second
        incomePerSecond = 0;
        incomePerSecond = myCafe.getIncomePerSecond() + myMine.getIncomePerSecond() + myBank.getIncomePerSecond();

        // Calculate Time Passed
        sf::Time frameTime = frameClock.restart();
		float dt = frameTime.asSeconds();

        timeAccumulator += dt;
        if (timeAccumulator >= 1.0f) { /*...*/ }

		// Every second, add passive income
        if (timeAccumulator >= 1.0f)
        {
            score += incomePerSecond; // Add the rate to the score
            timeAccumulator -= 1.0f; // Reset timer
        }
        
		// --- Update Floating Texts ---
		// Loop backwards to allow safe removal
        for (int i = 0; i < floatingTexts.size(); i++)
        {
			// Update returns 'false' if text has faded out
            if (!floatingTexts[i].update(dt))
            {
                // Remove from vector
                floatingTexts.erase(floatingTexts.begin() + i);
                i--; // Adjust index after removal
            }
        }

        sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    saveGame(score, myCafe.getOwnedCount(), myCafe.getCost(), myMine.getOwnedCount(), myMine.getCost(), myBank.getOwnedCount(), myBank.getCost());
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
                            coinSound.play();

                            // Create Floating Text at mouse position
                            floatingTexts.push_back(FloatingText(mousePos.x, mousePos.y, "+1", font));
                        }

                        // Buy Cafe
                        if (myCafe.isClicked(mousePos))
                        {
                            myCafe.shrink();
                            if (score >= myCafe.getCost())
                            {
                                // Capture the cost before purchase
                                long long cost = myCafe.getCost();

                                score -= myCafe.getCost();
                                myCafe.purchase();
                                purchaseSound.play();

                                std::string costString = "-" + std::to_string(cost);

                                floatingTexts.push_back(FloatingText(mousePos.x, mousePos.y, costString, font, sf::Color::Red, 50.0f));

                                std::cout << "Cafe Purchased!" << std::endl;
                            }
                            else
                            {
                                std::cout << "Not enough coins to purchase Cafe!" << std::endl;
                            }
                        }

                        // Buy Mine
                        if (myMine.isClicked(mousePos))
                        {
                            myMine.shrink();
                            if (score >= myMine.getCost())
                            {
                                long long cost = myMine.getCost();

                                score -= myMine.getCost();
                                myMine.purchase();
                                purchaseSound.play();

                                std::string costString = "-" + std::to_string(cost);

                                floatingTexts.push_back(FloatingText(mousePos.x, mousePos.y, costString, font, sf::Color::Red, 50.0f));

                                std::cout << "Mine Purchased!" << std::endl;
                            }
                            else
                            {
                                std::cout << "Not enough coins to purchase Mine!" << std::endl;
                            }
                        }

                        // Buy Bank
                        if (myBank.isClicked(mousePos))
                        {
                            myBank.shrink();
                            if (score >= myBank.getCost())
                            {
                                long long cost = myBank.getCost();
                                score -= myBank.getCost();
                                myBank.purchase();
                                purchaseSound.play();

                                std::string costString = "-" + std::to_string(cost);

                                floatingTexts.push_back(FloatingText(mousePos.x, mousePos.y, costString, font, sf::Color::Red, 50.0f));

                                std::cout << "Bank Purchased!" << std::endl;
                            }
                            else
                            {
                                std::cout << "Not enough coins to purchase Bank!" << std::endl;
                            }
                        }


                    }

                }
                        // Mouse Released
                        if (event.type == sf::Event::MouseButtonReleased)
                        {
                            myCoin.resetScale();
                            myCafe.resetScale();
                            myMine.resetScale();
                            myBank.resetScale();
                        }

                    

                
            }

        // --- Update UI Text ---
        scoreText.setString("Coins: " + std::to_string(score));

		incomeText.setString("Coins per second: " + std::to_string(incomePerSecond));

        std::string cafeString = "Cafe (Owned: " + std::to_string(myCafe.getOwnedCount()) + ")\nCost: " + std::to_string(myCafe.getCost());
        cafeText.setString(cafeString);

		std::string mineString = "Mine (Owned: " + std::to_string(myMine.getOwnedCount()) + ")\nCost: " + std::to_string(myMine.getCost());
		mineText.setString(mineString);

		std::string bankString = "Bank (Owned: " + std::to_string(myBank.getOwnedCount()) + ")\nCost: " + std::to_string(myBank.getCost());
		bankText.setString(bankString);

        // --- Render ---
        window.clear(sf::Color::White);

       // myCoin.draw(window);
		//myCafe.draw(window);
		//myMine.draw(window);
		//myBank.draw(window);

        for (auto& building : shop) {
            building->draw(window);
        }

        window.draw(titleText);
        window.draw(scoreText);
		window.draw(incomeText);
		window.draw(cafeText);
		window.draw(mineText);
		window.draw(bankText);

        // Draw the floating texts
        for (auto& txt : floatingTexts)
        {
            txt.draw(window);
        }

        window.display();
    }

    return 0;
}