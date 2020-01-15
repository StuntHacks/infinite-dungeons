#pragma once

#include <vector>
#include "common/graphics/drawables/menu/TextBox.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/Application.hpp"

namespace id {
    namespace menu {
        class TextBoxManager {
        friend class id::Application;
        friend class id::graphics::Renderer;
        friend class id::menu::TextBox;
        public:
            enum class BoxType {
                Transparent = 0,
                // Speech,
                // Thought,
                // Information,
                // Freeform
            };

            static id::menu::TextBoxManager& getInstance();

            /**
             * @param callback See id::menu::TextBox::display()
             */
            void addTextBox(id::menu::TextBoxManager::BoxType type, const std::wstring& text, bool autoProceed = false, int displayTime = 0, int pauseBefore = 0, int pauseAfter = 0, std::function<void(int)> callback = [](int){});

            /**
             * @param callback See id::menu::TextBox::display()
             */
            void addQuestionBox(id::menu::TextBoxManager::BoxType type, const std::wstring& text, std::function<void(int)> callback, std::vector<id::menu::TextBox::QuestionOption> options, int defaultOption = -1, unsigned int selected = 0, int pauseBefore = 0, int pauseAfter = 0);

            void pause(bool pause = true);

            /**
             * @brief Proceeds to the next textbox, if the manager is paused
             */
            bool proceed();

            /**
             * @brief Skips the current textbox
             */
            void skip();

            /**
             * @brief Clears the textbox-stack
             */
            void clear();

        private:
            TextBoxManager();
            ~TextBoxManager();

            void display();
            void update();
            void draw(id::graphics::Renderer& renderer);

            void callback(int result);

            struct BoxData {
                BoxType type;
                std::wstring text;
                int displayTime, pauseBefore, pauseAfter;
                bool autoProceed;
                std::function<void(int)> callback;
                bool isQuestion = false;
                int defaultOption = 0;
                unsigned int selected = 0;
                std::vector<id::menu::TextBox::QuestionOption> options;
            };

            /* data */
            bool m_pause;
            unsigned int m_cursor;
            std::vector<BoxData> m_boxStack;
            std::vector<TextBox*> m_boxes;
        };
    } /* menu */
} /* id */
