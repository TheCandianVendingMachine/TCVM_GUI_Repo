// SFML_TEMPLATE
// template for any SFML project
#include <SFML/Graphics.hpp>
#include "gui/panel.hpp"

int main()
    {
        sf::RenderWindow app(sf::VideoMode(1280, 720), "SFML", sf::Style::Close);
        app.setFramerateLimit(120);

        fe::gui::panel panel({ 200, 200 });
        panel.setOrigin({ 100, 100 });

        const float deltaTime = 1.f / 60.f;

        sf::Clock deltaClock;

        sf::Time currentTime = deltaClock.restart();
        float acc = 0.f;

        while (app.isOpen())
            {
                sf::Time newTime = deltaClock.getElapsedTime();
                sf::Time frameTime = newTime - currentTime;
                frameTime = frameTime > sf::milliseconds(500) ? sf::milliseconds(500) : frameTime; // make sure that the update loop will never take longer than half a second
                currentTime = newTime;

                acc += frameTime.asSeconds();

                sf::Event eve;
                while (app.pollEvent(eve))
                    {
                        switch (eve.type)
                            {
                                case sf::Event::Closed:
                                    app.close();
                                    break;
                                default:
                                    break;
                            }
                    }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        panel.setSize({ 60, 60 });
                    }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        panel.rotate(1_Deg);
                    }

                panel.setPosition(fe::Vector2d(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y));

                while (acc >= deltaTime)
                    {
                        // update
                        
                        acc -= deltaTime;
                    }

                app.clear(sf::Color::Black);
                panel.draw(app);
                app.display();
            }

        return 0;
    }