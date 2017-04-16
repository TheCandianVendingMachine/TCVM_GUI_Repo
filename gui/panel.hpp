// panel.hpp
// a "window" for GUI elements. A render texture so we can render to it in one call
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <memory>

#include "../transformable.hpp"

namespace sf
    {
        class RenderTarget;
        class Event;
    }

namespace fe
    {
        namespace gui
            {
                class guiElement;

                class panel : public fe::transformable
                    {
                        private:
                            std::vector<guiElement*> m_guiElements;

                            sf::RenderTexture m_texture;
                            sf::Color m_panelColour;

                            sf::VertexArray m_window;
                            fe::Vector2d m_size;

                            fe::Vector2d m_mousePosition;
                            bool m_mousePressed;

                        public:
                            panel(fe::Vector2d size);

                            void addElement(guiElement *element);
                            void removeElement(guiElement *element);

                            bool getMousePressed() const;
                            bool mouseHover(const fe::Vector2d &position, const fe::Vector2d &size);

                            void setSize(fe::Vector2d size);
                            fe::Vector2d getSize() const;

                            void handleEvent(const sf::Event &event);
                            void update();
                            void draw(sf::RenderTarget &target);

                            void destroy();
                            ~panel();

                    };
            }
    }