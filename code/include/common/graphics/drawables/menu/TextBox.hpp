#pragma once

#include <functional>
#include <string>
#include <vector>

#include "common/graphics/Font.hpp"
#include "common/graphics/drawables/Text.hpp"

namespace id {
    namespace menu {
        /**
         * @todo Move special characters into an enum
         */
        class TextBox: public id::graphics::Drawable {
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

            struct QuestionOption {
                std::wstring text;
                int resultValue = -1;
            };

            virtual std::wstring getText() const;
            virtual std::wstring getDisplayedText() const;
            virtual wchar_t getCurrentChar();

            virtual int getDisplayTime();
            virtual int getPauseBefore();
            virtual int getPauseAfter();

            /**
             * @brief Displays the textbox
             * @param callback A callback to call after the textbox is finished. The single parameter is the selected choice in multi-choice boxes, or -1 otherwise
             */
            virtual void display(const std::wstring& text, bool autoProceed = false, int displayTime = 10, int pauseBefore = 0, int pauseAfter = 0, std::function<void(int)> callback = [](int){});

            /**
             * @brief Displays the textbox as a questionbox
             * @param callback A callback to call after the textbox is finished. The single parameter is the selected choice in multi-choice boxes, or -1 otherwise
             */
            virtual void displayQuestion(const std::wstring& text, std::function<void(int)> callback, std::vector<id::menu::TextBox::QuestionOption> options, int defaultOption = -1, unsigned int selected = 0, int pauseBefore = 0, int pauseAfter = 0);

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
            virtual void draw(id::graphics::Renderer& renderer, bool) = 0;

            virtual id::menu::TextBox::State getState();

        protected:
            TextBox();
            std::vector<std::wstring> split(const std::wstring& text, const std::wstring& delimeter);
            void drawCharacter();

            /* data */
            int m_displayTime, m_pauseBefore, m_pauseAfter, m_frameCounter, m_result, m_defaultOption;
            size_t m_page, m_optionsCursor;
            bool m_autoProceed, m_isQuestion;
            id::menu::TextBox::State m_state;

            std::wstring m_text;
            std::wstring::const_iterator m_cursor;

            std::vector<std::wstring> m_pages;
            std::vector<id::menu::TextBox::QuestionOption> m_options;

            std::function<void(int)> m_callback;

            id::graphics::Font m_font;
            id::graphics::Text m_textObject;
        };
    } /* menu */
} /* id */
