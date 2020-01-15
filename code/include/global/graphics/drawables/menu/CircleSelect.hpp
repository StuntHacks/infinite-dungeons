#pragma once

#include <functional>
#include <string>
#include <vector>

#include "switch/input.hpp"
#include "global/graphics/Font.hpp"
#include "global/graphics/Texture.hpp"
#include "global/graphics/drawables/Text.hpp"

namespace id {
    namespace menu {
        class CircleSelect: public id::graphics::Drawable {
        public:
            enum State {
                FadingIn,
                Displaying,
                FadingOut,
                CleanUp,
                Finished
            };

            struct Item {
                std::wstring title;
                id::graphics::Texture* icon;
                std::vector<std::wstring> data;
            };

            virtual std::wstring getTitle() const;
            virtual int getSelectedID() const;
            virtual std::vector<id::menu::CircleSelect::Item> getOptions() const;

            /**
             * @brief Displays the Selection
             * @param callback A callback to call after a selection is done. The single parameter is the selected choice, or -1 if nothing was selected
             */
            virtual void display(std::vector<id::menu::CircleSelect::Item> options, id::Input::Button button, std::function<void(int)> callback = [](int){}, const std::wstring& title = L"");

            /**
             * @brief Closes the selection
             * @param dismiss Whether to dismiss the current selection
             */
            virtual void close(bool dismiss = true);

            virtual void update();
            virtual void draw(id::graphics::Renderer& renderer, bool) = 0;

            virtual id::menu::CircleSelect::State getState();

        protected:
            CircleSelect();

            /* data */
            int m_cursor, m_result, m_frameCounter;
            id::menu::CircleSelect::State m_state;
            std::wstring m_title;
            std::vector<id::menu::CircleSelect::Item> m_options;
            id::Input::Button m_button;

            std::function<void(int)> m_callback;

            id::graphics::Font m_font;
            id::graphics::Text m_textObject;
        };
    } /* menu */
} /* id */
