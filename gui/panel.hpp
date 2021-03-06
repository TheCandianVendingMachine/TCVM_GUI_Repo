// panel.hpp
// a "window" for GUI elements. A render texture so we can render to it in one call
#pragma once
#define FLAT_ENGINE_EXPORT
#include "../flatEngineExport.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <memory>
#include <cstdint>

#include "../entity/transformable.hpp"

namespace sf
    {
        class RenderTarget;
        class Event;
        class Font;
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

                            sf::Text m_title;
                            fe::Vector2d m_titlePosition;

                            bool m_canDrag;     // If we are able to drag the window
                            bool m_canClose;    // If we are able to close and destroy the window
                            bool m_canMinimize; // If we are able to minimize the window
                            bool m_hasTitle;    // If the panel has the title modifer

                            bool m_isOpen;
                            bool m_isFolded;

                        public:
                            FLAT_ENGINE_API panel(fe::Vector2d size = {50, 50}, int modifiers = 0, const char *title = "\0", sf::Font *font = nullptr);

                            FLAT_ENGINE_API void setModifiers(int modifiers);

                            FLAT_ENGINE_API void setTitle(const char *title, sf::Font &font);
                            FLAT_ENGINE_API std::string getTitle() const;

                            FLAT_ENGINE_API void setPanelBarColour(sf::Color colour);
                            FLAT_ENGINE_API void setPanelClearColour(sf::Color colour);

                            FLAT_ENGINE_API sf::Color getPanelBarColour() const;
                            FLAT_ENGINE_API sf::Color getPanelClearColour() const;

                            // Returns false if the window requests to be closed
                            FLAT_ENGINE_API bool isOpen() const;

                            FLAT_ENGINE_API unsigned int addElement(guiElement *element);
                            FLAT_ENGINE_API guiElement *getElement(unsigned int handle);
 
                            FLAT_ENGINE_API void removeElement(unsigned int handle);

                            FLAT_ENGINE_API bool getMousePressed() const;
                            FLAT_ENGINE_API bool mouseHover(const fe::Vector2d &position, const fe::Vector2d &size) const;

                            FLAT_ENGINE_API void setSize(fe::Vector2d size);
                            FLAT_ENGINE_API fe::Vector2d getSize() const;

                            FLAT_ENGINE_API void handleEvent(const sf::Event &event);
                            FLAT_ENGINE_API void update();
                            FLAT_ENGINE_API void draw(sf::RenderTarget &target);

                            FLAT_ENGINE_API void destroy();
                            FLAT_ENGINE_API ~panel();

                    };
            }
    }