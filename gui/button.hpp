// button.hpp
// Can be clicked, and when clicked a callback is called
#pragma once
#define FLAT_ENGINE_EXPORT
#include "../flatEngineExport.hpp"

#include "guiElement.hpp"
#include <functional>
#include <SFML/Graphics/VertexArray.hpp>

namespace fe
    {
        namespace gui
            {
                class panel;
                class button : public guiElement
                    {
                        private:
                            std::function<void()> m_callback;
                            sf::VertexArray m_shape;

                            FLAT_ENGINE_API void drawElement(sf::RenderTarget &target, const fe::matrix3d &matrix);

                        public:
                            FLAT_ENGINE_API button(const fe::Vector2d &size, const std::function<void()> &callback);

                            FLAT_ENGINE_API void handleEvent(const sf::Event &event);
                            FLAT_ENGINE_API void update();

                    };
            }
    }