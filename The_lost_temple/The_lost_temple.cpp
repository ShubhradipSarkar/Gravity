#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include<algorithm>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ball Example");

    // Set the window's framerate limit to 60 frames per second
    window.setFramerateLimit(280);

    // Load the texture
    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/shubh/source/repos/The_lost_temple/bg.jpg"))
    {
        std::cout << "Error loading texture." << std::endl;
        return 1;
    }

    // Create a sprite for the texture
    sf::Sprite background(texture);


    // Create the ball
    sf::CircleShape ball(20);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(0, 0);

    
    // Create the font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/shubh/source/repos/The_lost_temple/lekha.ttf"))
    {
        std::cout << "Error loading font." << std::endl;
        return 1;
    }

    // Create the text for the ball speed input
    sf::Text speedText("Enter gravity (g): ", font, 20);
    speedText.setPosition(500, 10);

    // Create the text for the ball speed value
    sf::Text speedValueText("", font, 20);
    speedValueText.setPosition(speedText.getPosition().x + speedText.getLocalBounds().width + 5, 10);

   

   
    // Define the ball's speed and other variables
    float ballSpeed=9.8f;
    float falling = 0; // to identify if ball is falling
    float going_up = 0; // to identify if ball should go up
    float elastic_restitution = 0.3f;

    // Taking some inputs in command prompt
    float velocity;
    std::cout << "velocity = " << "\n";
    std::cin >> velocity;
    float angle;
    std::cout << "angle with horizon = ";
    std::cin >> angle;

    angle = 3.1419 * angle / 180;
   
    // Define time
    sf::Clock clock;
        
    // Game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        

        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                // Check if the key entered is a digit or a period
                if (std::isdigit(event.text.unicode) || event.text.unicode == '.')
                {
                    // Add the key to the ball speed string
                    std::stringstream stream;
                    stream << speedValueText.getString().toAnsiString() << static_cast<char>(event.text.unicode);
                    speedValueText.setString(stream.str());

                    // Convert the ball speed string to a float
                    std::stringstream speedStream(speedValueText.getString().toAnsiString());
                    speedStream >> ballSpeed;
                }
            }
            
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
            {
                // Set the ball's speed to fall down
                falling += 1;
               
                clock.restart();
            }
        }
        


        // Get the elapsed time since "D" was pressed
        float elapsedTime = clock.getElapsedTime().asSeconds();
        

        // Position of ball
        float pos_x = ball.getPosition().x;
        
        float pos_y = ball.getPosition().y;
        
        
        // Velocity components (displacements)
        float dwn_x = velocity* cos(angle)* elapsedTime;

        float dwn_y = velocity * sinf(angle) * elapsedTime + ballSpeed * elapsedTime * elapsedTime * 0.5;
        
       
        
        // After ball hits ground
        if (ball.getPosition().y > window.getSize().y-ball.getRadius()*2)
        {
            dwn_y = -1*abs(dwn_y);
        }
        // After 'F' is pressed
        if (falling > 0)
        {
            ball.move(dwn_x, dwn_y);
            
        }
        // Clear the window
        window.clear();

        // Draw Game State
        window.draw(background);
        window.draw(ball);
        window.draw(speedText);
        //window.draw(AngleInput);
        window.draw(speedValueText);


        // Display the window
        window.display();
    }

    return 0;
}
