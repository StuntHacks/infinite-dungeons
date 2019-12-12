#pragma once

#include <vector>
#include "global/graphics/drawables/menu/TextBox.hpp"
#include "global/graphics/Renderer.hpp"
#include "global/Application.hpp"

namespace ta {
    namespace menu {
        class TextBoxManager {
        friend class ta::Application;
        friend class ta::graphics::Renderer;
        public:
            enum class BoxType {
                Transparent = 0,
                // Speech,
                // Thought,
                // Information
            };

            static ta::menu::TextBoxManager& getInstance();

            void addTextBox(ta::menu::TextBoxManager::BoxType type, const std::wstring& text, bool autoProceed = false, int displayTime = 0, int pauseBefore = 0, int pauseAfter = 0);

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

            void update();
            void draw(ta::graphics::Renderer& renderer);

            struct BoxData {
                BoxType type;
                std::wstring text;
                int displayTime, pauseBefore, pauseAfter;
                bool autoProceed;
            };

            /* data */
            bool m_pause, m_displaying;
            unsigned int m_cursor;
            std::vector<BoxData> m_boxStack;
            std::vector<TextBox*> m_boxes;
        };
    } /* menu */
} /* ta */
