#include "global/graphics/drawables/menu/CircleSelect.hpp"
#include "global/settings/settings.hpp"
#include "switch/input.hpp"
#include "global/Console.hpp"

#include <cmath>

namespace ta {
    namespace menu {
        std::wstring CircleSelect::getTitle() const {
            return m_title;
        }

        int CircleSelect::getSelectedID() const {
            return m_result;
        }

        std::vector<ta::menu::CircleSelect::Item> CircleSelect::getOptions() const {
            return m_options;
        }

        ta::menu::CircleSelect::Item CircleSelect::getSelectedOption() const {
            if (m_result > -1 && m_result < static_cast<int>(m_options.size())) {
                return m_options[m_result];
            } else {
                return { L"" };
            }
        }

        void CircleSelect::display(std::vector<ta::menu::CircleSelect::Item> options, ta::Input::Button button, std::function<void(int)> callback, const std::wstring& title) {
            if (m_state == ta::menu::CircleSelect::State::Finished) {
                m_frameCounter = 0;
                m_cursor = 0;
                m_title = title;
                m_button = button;
                m_state = ta::menu::CircleSelect::State::FadingIn;
                m_options = options;
                m_callback = callback;
            }
        }

        void CircleSelect::close(bool dismiss) {
            m_frameCounter = 0;

            if (dismiss) {
                m_result = -1;
            }

            m_state = ta::menu::CircleSelect::State::FadingOut;
        }

        void CircleSelect::update() {
            if (m_state == ta::menu::CircleSelect::State::FadingIn || m_state == ta::menu::CircleSelect::State::Displaying) {
                if (!ta::Input::buttonDown(m_button)) {
                    m_state = ta::menu::CircleSelect::State::FadingOut;
                }
            }

            // Fading in and out is up to the implementing classes
            switch (m_state) {
            case ta::menu::CircleSelect::State::Displaying:
                {
                    float angle = ta::Input::getJoystickPolar(ta::Input::Joystick::Right, ta::Input::Player::P1).u;
                    float weight = ta::Input::getJoystickPolar(ta::Input::Joystick::Right, ta::Input::Player::P1).v;

                    if (angle < 0.0f) {
                        angle = 360.0f + angle;
                    }

                    if (weight <= 0.0f) {
                        m_result = -1;
                    } else {
                        m_result = 0;

                        // TODO: Optimize this?
                        float usedAngle = (angle - 90.0f + ((360.0f / m_options.size()) / 2.0f) < 0.0f ? angle - 90.0f + ((360.0f / m_options.size()) / 2.0f) + 360.0f : angle - 90.0f + ((360.0f / m_options.size()) / 2.0f));

                        while (usedAngle > (360.0f / m_options.size())) {
                            m_result++;
                            usedAngle -= (360.0f / m_options.size());
                        }

                        if (m_result >= static_cast<int>(m_options.size())) {
                            m_result = -1;
                        }
                    }
                }

                break;
            case ta::menu::CircleSelect::State::CleanUp:
                {
                    m_frameCounter = 0;
                    m_cursor = 0;

                    m_options.clear();
                    m_title = L"";
                    m_button = ta::Input::None;

                    m_state = ta::menu::CircleSelect::State::Finished;

                    std::function<void(int)> callback = m_callback;
                    m_callback = [](int){};
                    callback(m_result);
                    m_result = -1;
                }

                return;
            default:
                /* do nothing */
                break;
            }

            m_frameCounter++;
        }

        ta::menu::CircleSelect::State CircleSelect::getState() {
            return m_state;
        }

        // protected methods
        CircleSelect::CircleSelect() :
        m_cursor(-1),
        m_result(-1),
        m_frameCounter(0),
        m_state(ta::menu::CircleSelect::State::Finished),
        m_title(L""),
        m_button(ta::Input::None),
        m_callback([](int){}),
        m_font(ta::settings::DefaultFontPath),
        m_textObject(m_font) { /* do nothing */ }
    } /* menu */
} /* ta */
