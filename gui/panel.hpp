// panel.hpp
// a "window" for GUI elements. A render texture so we can render to it in one call
#pragma once
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <memory>
#include <cstdint>

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

                enum panelModifiers
                    {
                        NONE =          0,
                        HAS_TITLE =     1 << 0,
                        CAN_DRAG =      1 << 1,
                        CAN_CLOSE =     1 << 2,
                        CAN_MINIMIZE =  1 << 3
                    };

                class panel : public fe::transformable
                    {
                        private:
                            std::vector<guiElement*> m_guiElements;
                            std::vector<unsigned int> m_guiHandles;

                            sf::RenderTexture m_texture;
                            sf::Color m_panelColour;

                            sf::VertexArray m_window;
                            sf::VertexArray m_titleBar;
                            sf::Color m_titleBarColour;
                            fe::Vector2d m_size;
                            const fe::Vector2d m_minSize;

                            fe::Vector2d m_clickOffset; // offset of the click to the title bar
                            bool m_dragging; // true if we are currently dragging the window

                            fe::Vector2d m_mousePosition;
                            bool m_mousePressed;

                            const float m_buttonSize;      // size of the minimize/close buttons
                            const float m_distanceFromTop; // distance for minimize/close buttons from the top of the title bar
                            const float m_distanceFromEnd; // distance for minimize/close buttons from the right side of title bar

                            float m_windowOffset; // the offset of the window from the title bar

                            char m_title[512];  // Window title - what is displayed if active
                            bool m_canDrag;     // If we are able to drag the window
                            bool m_canClose;    // If we are able to close and destroy the window
                            bool m_canMinimize; // If we are able to minimize the window

                            bool m_isOpen;
                            bool m_isFolded;

                        public:
                            panel(fe::Vector2d size);
                            panel(fe::Vector2d size, int modifiers, const char *title = "\0");

                            // Returns false if the window requests to be closed
                            bool isOpen() const;

                            unsigned int addElement(guiElement *element);
                            guiElement *getElement(unsigned int handle);
 
                            void removeElement(unsigned int handle);

                            bool getMousePressed() const;
                            bool mouseHover(const fe::Vector2d &position, const fe::Vector2d &size) const;

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