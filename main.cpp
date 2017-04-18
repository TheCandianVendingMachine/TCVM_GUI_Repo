// SFML_TEMPLATE
// template for any SFML project
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gui/panel.hpp"
#include "gui/button.hpp"
#include "gui/label.hpp"

int main()
    {
        sf::RenderWindow app(sf::VideoMode(1280, 720), "SFML", sf::Style::Close);
        app.setFramerateLimit(120);

        sf::Font abc;
        abc.loadFromFile("Roboto-Regular.ttf");
        fe::gui::panel panel({ 550, 200 },
                            fe::gui::CAN_CLOSE | fe::gui::CAN_MINIMIZE | fe::gui::CAN_DRAG | fe::gui::HAS_TITLE,
                            "abc", &abc);

        panel.setPosition({ 100, 100 });

        auto handle = panel.addElement(new fe::gui::button({ 50, 50 }, []() { std::cout << "Pressed!\n"; }));
        auto text = panel.addElement(new fe::gui::label(abc, "Abc BB"));

        panel.getElement(text)->setParent(panel.getElement(handle));

        panel.getElement(handle)->setPosition({ 550 / 2, 200 / 2 });

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

                        panel.handleEvent(eve);
                    }

                panel.update();
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