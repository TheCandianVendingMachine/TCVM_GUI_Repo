#include "button.hpp"
#include "panel.hpp"

fe::gui::button::button(const fe::Vector2d &size, const std::function<void()> &callback) : m_callback(callback)
    {
        m_shape.setPrimitiveType(sf::PrimitiveType::Quads);
        m_shape.resize(4);

        m_size = size;
        setSize(size);
        m_shape[0].color = sf::Color::Red;
        m_shape[1].color = sf::Color::Red;
        m_shape[2].color = sf::Color::Red;
        m_shape[3].color = sf::Color::Red;
    }

void fe::gui::button::handleEvent(const sf::Event &event)
    {
    }

void fe::gui::button::update()
    {
        if (m_parentPanel->mouseHover(getPosition(), m_size) && m_parentPanel->getMousePressed())
            {
                m_callback();
            }
    }

void fe::gui::button::draw(sf::RenderTarget &target)
    {
        fe::matrix3d matrix = getMatrix();
        if (m_parentElement)
            {
                matrix *= m_parentElement->getMatrix();
            }

        m_shape[0].position = matrix.transformPoint({0.f, 0.f}).convertToSfVec2();
        m_shape[1].position = matrix.transformPoint({m_size.x, 0.f}).convertToSfVec2();
        m_shape[2].position = matrix.transformPoint({m_size.x, m_size.y}).convertToSfVec2();
        m_shape[3].position = matrix.transformPoint({0.f, m_size.y}).convertToSfVec2();

        target.draw(m_shape);
    }
