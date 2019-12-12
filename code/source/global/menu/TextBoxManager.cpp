#include "global/menu/TextBoxManager.hpp"
#include "global/graphics/Renderer.hpp"
#include "global/graphics/drawables/menu/textboxes/textboxes.hpp"
#include "global/Console.hpp"

namespace ta {
    namespace menu {
        ta::menu::TextBoxManager& TextBoxManager::getInstance() {
            static ta::menu::TextBoxManager instance;
            return instance;
        }

        void TextBoxManager::addTextBox(ta::menu::TextBoxManager::BoxType type, const std::wstring& text, bool autoProceed, int displayTime, int pauseBefore, int pauseAfter) {
            m_boxStack.push_back({
                type,
                text,
                displayTime,
                pauseBefore,
                pauseAfter,
                autoProceed
            });
        }

        void TextBoxManager::pause(bool pause) {
            m_pause = pause;
        }

        bool TextBoxManager::proceed() {
            if (m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->getState() == ta::menu::TextBox::State::Finished && m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                m_cursor++;
                return true;
            }

            return false;
        }

        void TextBoxManager::skip() {
            if (m_cursor < m_boxStack.size()) {
                m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->skip();

                if (m_boxStack.size() > 0) {
                    m_cursor++;
                }
            }
        }

        void TextBoxManager::clear() {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->skip();
            }

            if (m_boxStack.size() > 0) {
                m_boxStack.clear();
            }

            m_cursor = 0;
        }

        // private methods
        TextBoxManager::TextBoxManager() : m_pause(false), m_displaying(false), m_cursor(0) {
            m_boxes.push_back(&ta::menu::TransparentTextBox::getInstance());
        }

        TextBoxManager::~TextBoxManager() {

        }

        void TextBoxManager::update() {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->update();

                if (m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->getState() == ta::menu::TextBox::State::Finished && m_displaying) {
                    m_displaying = false;

                    if (!m_pause) {
                        proceed();
                    }
                }
            }
        }

        void TextBoxManager::draw(ta::graphics::Renderer& renderer) {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                if (!m_displaying) {
                    m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->display(
                        m_boxStack[m_cursor].text,
                        m_boxStack[m_cursor].autoProceed,
                        m_boxStack[m_cursor].displayTime,
                        m_boxStack[m_cursor].pauseBefore,
                        m_boxStack[m_cursor].pauseAfter
                    );

                    m_displaying = true;
                }

                if (m_displaying) {
                    renderer.draw2d(*m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]);
                }
            } else if (m_boxStack.size() > 0) {
                clear();
            }
        }
    } /* menu */
} /* ta */
