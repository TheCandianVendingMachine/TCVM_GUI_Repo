#include "panel.hpp"
#include "guiElement.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>

fe::gui::panel::panel(fe::Vector2d size) : m_mousePressed(false), m_size(size), m_panelColour(255, 255, 255)
    {
        m_window.setPrimitiveType(sf::PrimitiveType::Quads);
        m_window.resize(4);

        setSize(size);
    }

unsigned int fe::gui::panel::addElement(guiElement *element)
    {
        m_guiElements.emplace_back(element);
        m_guiHandles.push_back(m_guiElements.size() - 1);
        element->setParent(this);

        return m_guiHandles.size() - 1;
    }

fe::gui::guiElement *fe::gui::panel::getElement(unsigned int handle)
    {
        if (handle >= m_guiHandles.size())
            {
                return nullptr;
            }
        return m_guiElements[m_guiHandles[handle]];
    }

void fe::gui::panel::removeElement(unsigned int handle)
    {
        if (m_guiHandles.begin() + handle < m_guiHandles.end())
            {
                delete *(m_guiElements.begin() + m_guiHandles[handle]);
                m_guiElements.erase(m_guiElements.begin() + m_guiHandles[handle]);
                for (auto it = m_guiHandles.begin() + handle; it != m_guiHandles.end(); ++it) { (*it) -= 1; };
            }
    }

bool fe::gui::panel::getMousePressed() const
    {
        return m_mousePressed;
    }

bool fe::gui::panel::mouseHover(const fe::Vector2d &position, const fe::Vector2d &size) const
    {
        return m_mousePosition.x - getPosition().x > position.x          && m_mousePosition.y - getPosition().y > position.y &&
               m_mousePosition.x - getPosition().x < position.x + size.x && m_mousePosition.y - getPosition().y < position.y + size.y;
    }

void fe::gui::panel::setSize(fe::Vector2d size)
    {
        m_texture.create(size.x, size.y);

        m_window[0].texCoords = fe::Vector2d(0.f, 0.f).convertToSfVec2();
        m_window[1].texCoords = fe::Vector2d(size.x, 0.f).convertToSfVec2();
        m_window[2].texCoords = fe::Vector2d(size.x, size.y).convertToSfVec2();
        m_window[3].texCoords = fe::Vector2d(0.f, size.y).convertToSfVec2();

        // example of how to scale gui elements
        //test.scale(size.x / m_size.x, size.y / m_size.y);
        for (auto &element : m_guiElements)
            {
                element->setSize(size - element->getSize());
            }
        m_size = size;
    }

fe::Vector2d fe::gui::panel::getSize() const
    {
        return m_size;
    }

void fe::gui::panel::handleEvent(const sf::Event &event)
    {
        switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    m_mousePressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    m_mousePressed = false;
                    break;
                case sf::Event::MouseMoved:
                    m_mousePosition = m_texture.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
                    break;
                default:
                    break;
            }

        for (auto &element : m_guiElements)
            {
                element->handleEvent(event);
            }
    }

void fe::gui::panel::update()
    {
        for (auto &element : m_guiElements)
            {
                element->update();
            }
    }

void fe::gui::panel::draw(sf::RenderTarget &target)
    {
        auto &matrix = getMatrix();

        m_window[0].position = matrix.transformPoint({ 0.f, 0.f }).convertToSfVec2();
        m_window[1].position = matrix.transformPoint({ m_size.x, 0.f }).convertToSfVec2();
        m_window[2].position = matrix.transformPoint({ m_size.x, m_size.y }).convertToSfVec2();
        m_window[3].position = matrix.transformPoint({ 0.f, m_size.y }).convertToSfVec2();

        m_texture.clear(m_panelColour);
        for (auto &element : m_guiElements)
            {
                element->draw(m_texture);
            }
        m_texture.display();

        sf::RenderStates state;
        state.texture = &m_texture.getTexture();

        target.draw(m_window, state);
    }

void fe::gui::panel::destroy()
    {
        while(m_guiElements.size() > 0)
            {
                delete m_guiElements.back();
                m_guiElements.pop_back();
            }
    }

fe::gui::panel::~panel()
    {
        destroy();
    }
