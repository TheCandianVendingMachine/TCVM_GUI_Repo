#include "panel.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

fe::gui::panel::panel(fe::Vector2d size)
    {
        m_window.setPrimitiveType(sf::PrimitiveType::Quads);
        m_window.resize(4);

        m_size = size;
        m_panelColour = sf::Color(255, 255, 255);
        setSize(size);
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
        m_size = size;
    }

fe::Vector2d fe::gui::panel::getSize() const
    {
        return m_size;
    }

void fe::gui::panel::handleEvent(const sf::Event &event)
    {
        
    }

void fe::gui::panel::update()
    {
        
    }

void fe::gui::panel::draw(sf::RenderTarget &target)
    {
        auto &matrix = getMatrix();

        m_window[0].position = matrix.translatePoint({ 0.f, 0.f }).convertToSfVec2();
        m_window[1].position = matrix.translatePoint({ m_size.x, 0.f }).convertToSfVec2();
        m_window[2].position = matrix.translatePoint({ m_size.x, m_size.y }).convertToSfVec2();
        m_window[3].position = matrix.translatePoint({ 0.f, m_size.y }).convertToSfVec2();

        m_texture.clear(m_panelColour);
        
        m_texture.display();

        sf::RenderStates state;
        state.texture = &m_texture.getTexture();

        target.draw(m_window, state);
    }
