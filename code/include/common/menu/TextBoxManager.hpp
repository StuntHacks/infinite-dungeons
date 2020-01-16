/**
 * @file common/menu/TextBoxManager.hpp
 * @brief Defines the TextBoxManager-class
 */
#pragma once

#include <vector>
#include "common/graphics/drawables/menu/TextBox.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/Application.hpp"
#include "common/Singleton.hpp"

namespace id {
    namespace menu {
        /**
         * @brief Handles the global TextBox-queue
         */
        class TextBoxManager: public id::Singleton<TextBoxManager> {
        friend class id::Application;
        friend class id::graphics::Renderer;
        friend class id::menu::TextBox;
        friend class id::Singleton<TextBoxManager>;
        public:
            /**
             * @brief Defines different TextBox-types
             */
            enum class BoxType {
                Transparent = 0, ///< id::TransparentTextBox
                // Speech,          ///< id::SpeechTextBox
                // Thought,         ///< id::ThoughtTextBox
                // Information,     ///< id::InformationTextBox
                // Freeform         ///< id::FreeformTextBox
            };

            /**
             * @brief Adds a QuestionBox to the textbox-queue
             * @param type          The type of the QuestionBox
             * @param text          The text to display
             * @param autoproceed   Whether the textbox should proceed automatically without player input
             * @param displayTime   The time the box should pause at interrupts or the end, when autoProceed is enabled or the user holds B/Esc
             * @param pauseBefore   The pause in frames before displaing the box
             * @param pauseAfter    The pause in frames after displaying the box
             * @param callback      See id::menu::TextBox::display()
             */
            void addTextBox(id::menu::TextBoxManager::BoxType type, const std::wstring& text, bool autoProceed = false, int displayTime = 0, int pauseBefore = 0, int pauseAfter = 0, std::function<void(int)> callback = [](int){});

            /**
             * @brief Adds a QuestionBox to the textbox-queue
             * @param type          The id of the desired type
             * @param text          The text to display
             * @param autoproceed   Whether the textbox should proceed automatically without player input
             * @param displayTime   The time the box should pause at interrupts or the end, when autoProceed is enabled or the user holds B/Esc
             * @param pauseBefore   The pause in frames before displaing the box
             * @param pauseAfter    The pause in frames after displaying the box
             * @param callback      See id::menu::TextBox::display()
             */
            void addTextBox(unsigned int type, const std::wstring& text, bool autoProceed = false, int displayTime = 0, int pauseBefore = 0, int pauseAfter = 0, std::function<void(int)> callback = [](int){});

            /**
             * @brief Adds a QuestionBox to the textbox-queue
             * @param type          The type of the QuestionBox
             * @param text          The text to display
             * @param callback      See id::menu::TextBox::display()
             * @param options       The question options
             * @param defaultOption The option to use when pressing B/Esc. Set this to -1 for no default option (this disables pressing B/Esc)
             * @param selected      The option selected by default
             * @param pauseBefore   The pause in frames before displaing the box
             * @param pauseAfter    The pause in frames after displaying the box
             */
            void addQuestionBox(id::menu::TextBoxManager::BoxType type, const std::wstring& text, std::function<void(int)> callback, std::vector<id::menu::TextBox::QuestionOption> options, int defaultOption = -1, unsigned int selected = 0, int pauseBefore = 0, int pauseAfter = 0);

            /**
             * @brief Adds a QuestionBox to the textbox-queue
             * @param type          The id of the desired type
             * @param text          The text to display
             * @param callback      See id::menu::TextBox::display()
             * @param options       The question options
             * @param defaultOption The option to use when pressing B/Esc. Set this to -1 for no default option (this disables pressing B/Esc)
             * @param selected      The option selected by default
             * @param pauseBefore   The pause in frames before displaing the box
             * @param pauseAfter    The pause in frames after displaying the box
             */
            void addQuestionBox(unsigned int type, const std::wstring& text, std::function<void(int)> callback, std::vector<id::menu::TextBox::QuestionOption> options, int defaultOption = -1, unsigned int selected = 0, int pauseBefore = 0, int pauseAfter = 0);

            /**
             * @brief Pauses or unpauses the queue-progression
             * @param pause Whether to pause or not
             */
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

            /**
             * @brief Registers a TextBox-class to use
             * @param  instance The instance to register
             * @return          The id of the registered instance. Pass this to the display-methods as the `type`-parameter
             */
            unsigned int registerTextBox(id::menu::TextBox& instance);

        private:
            TextBoxManager();
            ~TextBoxManager();

            void display();
            void update();
            void draw(id::graphics::Renderer& renderer);

            void callback(int result);

            struct BoxData {
                unsigned int type;
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
