#pragma once

#include "global/graphics/Font.hpp"
#include "global/graphics/drawables/Text.hpp"
#include <vector>
#include <string>

namespace ta {
    namespace menu {
        /**
         * @todo Move special characters into an enum
         */
        class TextBox: public ta::graphics::Drawable {
        public:
            enum class State {
                PauseBefore,
                Drawing,
                Interrupted,
                Displaying,
                DisplayingFinal,
                PauseAfter,
                Finished
            };

            virtual std::wstring getText() const;
            virtual std::wstring getDisplayedText() const;
            virtual wchar_t getCurrentChar();

            virtual int getDisplayTime();
            virtual int getPauseBefore();
            virtual int getPauseAfter();

            /**
             * @brief Displays the textbox
             */
            virtual void display(const std::wstring& text, bool autoProceed = false, int displayTime = 0, int pauseBefore = 0, int pauseAfter = 0);

            /**
             * @brief Interrupts the drawing process
             */
            virtual void interrupt();

            /**
             * @brief Skips to the end of the textbox drawing loop
             */
            virtual void finish();

            /**
             * @brief Discards the textbox no matter it's state
             */
            virtual void skip();

            virtual void update();
            virtual void draw(ta::graphics::Renderer& renderer, bool) = 0;

            virtual ta::menu::TextBox::State getState();

        protected:
            TextBox();
            std::vector<std::wstring> split(const std::wstring& text, const std::wstring& delimeter);
            void drawCharacter();

            /* data */
            int m_displayTime, m_pauseBefore, m_pauseAfter, m_frameCounter;
            size_t m_page;
            bool m_autoProceed;
            std::wstring m_text;
            std::wstring::const_iterator m_cursor;
            std::vector<std::wstring> m_pages;
            ta::menu::TextBox::State m_state;

            ta::graphics::Font m_font;
            ta::graphics::Text m_textObject;
        };
    } /* menu */
} /* ta */
