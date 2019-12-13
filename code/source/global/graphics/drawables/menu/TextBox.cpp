#include "global/graphics/drawables/menu/TextBox.hpp"
#include "global/settings/settings.hpp"
#include "switch/input.hpp"

namespace ta {
    namespace menu {
        std::wstring TextBox::getText() const {
            return m_text;
        }

        std::wstring TextBox::getDisplayedText() const {
            return std::wstring(m_pages[m_page].begin(), m_cursor);
        }

        wchar_t TextBox::getCurrentChar() {
            return *m_cursor;
        }

        int TextBox::getDisplayTime() {
            return m_displayTime;
        }

        int TextBox::getPauseBefore() {
            return m_pauseBefore;
        }

        int TextBox::getPauseAfter() {
            return m_pauseAfter;
        }

        void TextBox::display(const std::wstring& text, bool autoProceed, int displayTime, int pauseBefore, int pauseAfter) {
            if (m_state == ta::menu::TextBox::State::Finished) {
                m_text = text;
                m_autoProceed = autoProceed;
                m_displayTime = displayTime;
                m_pauseBefore = pauseBefore;
                m_pauseAfter = pauseAfter;

                m_pages = split(m_text, L"\\p");
                m_page = 0;

                m_cursor = m_pages[m_page].begin();
                m_textObject.setText(L"");

                m_frameCounter = 0;
                m_state = ta::menu::TextBox::State::PauseBefore;
            }
        }

        void TextBox::interrupt() {
            m_frameCounter = 0;
            m_state = ta::menu::TextBox::State::Interrupted;
        }

        void TextBox::finish() {
            while (m_cursor != m_pages[m_page].end()) {
                drawCharacter();
            }

            m_frameCounter = 0;
            m_state = ta::menu::TextBox::State::Displaying;
        }

        void TextBox::skip() {
            m_state = ta::menu::TextBox::State::Finished;
        }

        void TextBox::update() {
            if (m_state == ta::menu::TextBox::State::PauseBefore) {
                if (m_frameCounter >= m_pauseBefore) {
                    m_frameCounter = 0;
                    m_state = ta::menu::TextBox::State::Drawing;
                    return;
                }

                m_frameCounter++;
            } else if (m_state == ta::menu::TextBox::State::Drawing) {
                if (m_cursor == m_pages[m_page].end()) {
                    m_frameCounter = 0;

                    if (m_page < m_pages.size() - 1) {
                        m_state = ta::menu::TextBox::State::Displaying;
                    } else {
                        m_state = ta::menu::TextBox::State::DisplayingFinal;
                    }

                    return;
                } else {
                    if (ta::Input::buttonDown(ta::Input::Button::B)) {
                        finish();
                        return;
                    }

                    if (m_frameCounter % ta::settings::TextSpeed == 0) {
                        drawCharacter();
                    }
                }

                m_frameCounter++;
            } else if (m_state == ta::menu::TextBox::State::Interrupted) {
                if (ta::Input::buttonPressed(ta::Input::Button::A) || ta::Input::buttonPressed(ta::Input::Button::B)) {
                    m_frameCounter = 0;
                    m_state = ta::menu::TextBox::State::Drawing;
                    return;
                }

                m_frameCounter++;
            } else if (m_state == ta::menu::TextBox::State::Displaying) {
                if (ta::Input::buttonPressed(ta::Input::Button::A) || ta::Input::buttonPressed(ta::Input::Button::B) || (m_autoProceed && m_frameCounter >= m_displayTime)) {
                    m_frameCounter = 0;
                    m_page++;

                    m_textObject.setText(L"");
                    m_cursor = m_pages[m_page].begin();

                    m_state = ta::menu::TextBox::State::Drawing;
                    return;
                }

                m_frameCounter++;
            } else if (m_state == ta::menu::TextBox::State::DisplayingFinal) {
                if (ta::Input::buttonPressed(ta::Input::Button::A) || ta::Input::buttonPressed(ta::Input::Button::B) || (m_autoProceed && m_frameCounter >= m_displayTime)) {
                    m_frameCounter = 0;
                    m_state = ta::menu::TextBox::State::PauseAfter;
                    return;
                }

                m_frameCounter++;
            } else if (m_state == ta::menu::TextBox::State::PauseAfter) {
                if (m_frameCounter >= m_pauseAfter) {
                    m_frameCounter = 0;
                    m_displayTime = 0;
                    m_pauseBefore = 0;
                    m_pauseAfter = 0;

                    m_text = L"";
                    m_cursor = m_text.begin();

                    m_pages.clear();
                    m_page = 0;

                    m_autoProceed = false;
                    m_state = ta::menu::TextBox::State::Finished;
                    return;
                }

                m_frameCounter++;
            }
        }

        ta::menu::TextBox::State TextBox::getState() {
            return m_state;
        }

        // protected methods
        TextBox::TextBox() :
        m_displayTime(0),
        m_pauseBefore(0),
        m_pauseAfter(0),
        m_frameCounter(0),
        m_page(0),
        m_autoProceed(false),
        m_text(L""),
        m_state(ta::menu::TextBox::State::Finished),
        m_font(ta::settings::DefaultFontPath),
        m_textObject(m_font) {
            m_cursor = m_text.begin();
        }

        std::vector<std::wstring> TextBox::split(const std::wstring& text, const std::wstring& delimeter) {
             std::vector<std::wstring> splittedString;
             size_t startIndex = 0;
             size_t endIndex = 0;

             while ((endIndex = text.find(delimeter, startIndex)) < text.size()) {
                 std::wstring val = text.substr(startIndex, endIndex - startIndex);
                 splittedString.push_back(val);
                 startIndex = endIndex + delimeter.size();
             }

             if (startIndex < text.size()) {
                 std::wstring val = text.substr(startIndex);
                 splittedString.push_back(val);
             }

             return splittedString;
        }

        void TextBox::drawCharacter() {
            bool nextValid = std::next(m_cursor) != m_pages[m_page].end();
            bool secondNextValid = std::next(std::next(m_cursor)) != m_pages[m_page].end();

            if (*m_cursor == '\\' && nextValid) {
                switch (*std::next(m_cursor)) {
                case 'i':
                    m_cursor++;

                    if (secondNextValid) {
                        m_cursor++;
                    }

                    interrupt();
                    return;
                default:
                    m_textObject.appendText(*m_cursor);
                    m_cursor++;
                    m_textObject.appendText(*m_cursor);

                    if (secondNextValid) {
                        m_cursor++;
                        m_textObject.appendText(*m_cursor);
                    }

                    break;
                }
            } else {
                m_textObject.appendText(*m_cursor);

                if ((*m_cursor == ' ' || *m_cursor == '\n' || *m_cursor == '\r') && nextValid) {
                    m_cursor++;
                    m_textObject.appendText(*m_cursor);
                }
            }

            m_cursor++;
        }
    } /* menu */
} /* ta */
