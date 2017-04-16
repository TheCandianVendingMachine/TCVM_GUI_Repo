// guiElement.hpp
// base class for all GUI elements
#pragma once

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
                class panel;

                class guiElement : public fe::transformable
                    {
                        protected:
                            panel *m_parentPanel; // the panel this gui element is attached to.

                        public:
                            guiElement(panel &attached) : m_parentPanel(&attached) {}

                            virtual void draw(sf::RenderTarget &target) = 0;
                            virtual void update() = 0;
                            virtual void handleEvent(const sf::Event &event) = 0;
                    };
            }
    }