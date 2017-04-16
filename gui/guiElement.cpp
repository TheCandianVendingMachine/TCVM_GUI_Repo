#include "guiElement.hpp"

fe::gui::guiElement::guiElement() : m_parentPanel(nullptr), m_parentElement(nullptr)
    {
    }

fe::gui::guiElement::guiElement(guiElement *parent) : m_parentPanel(nullptr), m_parentElement(nullptr)
    {
    }

void fe::gui::guiElement::setParent(const panel *attached)
    {
        m_parentPanel = attached;
    }

void fe::gui::guiElement::setSize(const fe::Vector2d &size)
    {
        scale({ size.x / m_size.x, size.y / m_size.y });
        m_size = size;
    }

const fe::Vector2d &fe::gui::guiElement::getSize() const
    {
        return m_size;
    }
