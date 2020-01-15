#include "common/menu/TextBoxManager.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/graphics/drawables/menu/textboxes/textboxes.hpp"

namespace id {
    namespace menu {
        id::menu::TextBoxManager& TextBoxManager::getInstance() {
            static id::menu::TextBoxManager instance;
            return instance;
        }

        void TextBoxManager::addTextBox(id::menu::TextBoxManager::BoxType type, const std::wstring& text, bool autoProceed, int displayTime, int pauseBefore, int pauseAfter, std::function<void(int)> callback) {
            m_boxStack.push_back({
                type,
                text,
                displayTime,
                pauseBefore,
                pauseAfter,
                autoProceed,
                callback
            });

            if (m_boxStack.size() == 1 && m_cursor == 0) {
                display();
            }
        }

        void TextBoxManager::addQuestionBox(id::menu::TextBoxManager::BoxType type, const std::wstring& text, std::function<void(int)> callback, std::vector<id::menu::TextBox::QuestionOption> options, int defaultOption, unsigned int selected, int pauseBefore, int pauseAfter) {
            m_boxStack.push_back({
                type,
                text,
                0,
                pauseBefore,
                pauseAfter,
                false,
                callback,
                true,
                defaultOption,
                selected,
                options
            });

            if (m_boxStack.size() == 1 && m_cursor == 0) {
                display();
            }
        }

        void TextBoxManager::pause(bool pause) {
            m_pause = pause;
        }

        bool TextBoxManager::proceed() {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                if (m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->getState() == id::menu::TextBox::State::Finished) {
                    m_cursor++;
                    return true;
                }
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
        TextBoxManager::TextBoxManager() : m_pause(false), m_cursor(0) {
            m_boxes.push_back(&id::menu::TransparentTextBox::getInstance());
        }

        TextBoxManager::~TextBoxManager() {

        }

        void TextBoxManager::display() {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                if (m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->getState() == id::menu::TextBox::State::Finished) {
                    if (!m_boxStack[m_cursor].isQuestion) {
                        m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->display(
                            m_boxStack[m_cursor].text,
                            m_boxStack[m_cursor].autoProceed,
                            m_boxStack[m_cursor].displayTime,
                            m_boxStack[m_cursor].pauseBefore,
                            m_boxStack[m_cursor].pauseAfter,
                            std::bind(&id::menu::TextBoxManager::callback, this, std::placeholders::_1)
                        );
                    } else {
                        m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->displayQuestion(
                            m_boxStack[m_cursor].text,
                            std::bind(&id::menu::TextBoxManager::callback, this, std::placeholders::_1),
                            m_boxStack[m_cursor].options,
                            m_boxStack[m_cursor].defaultOption,
                            m_boxStack[m_cursor].selected
                        );
                    }
                }
            }
        }

        void TextBoxManager::update() {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]->update();
            }
        }

        void TextBoxManager::draw(id::graphics::Renderer& renderer) {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                renderer.draw2d(*m_boxes[static_cast<int>(m_boxStack[m_cursor].type)]);
            } else if (m_boxStack.size() > 0) {
                clear();
            }
        }

        void TextBoxManager::callback(int result) {
            if (m_cursor < m_boxStack.size() && m_boxStack.size() > 0) {
                m_boxStack[m_cursor].callback(result);
            }

            proceed();
            display();
        }
    } /* menu */
} /* id */
