#include "common/graphics/drawables/menu/CircleSelect.hpp"
#include "common/settings/Settings.hpp"
#include "common/Console.hpp"
#include "common/InputManager.hpp"

#include <cmath>

namespace id {
    namespace menu {
        std::wstring CircleSelect::getTitle() const {
            return m_title;
        }

        int CircleSelect::getSelectedID() const {
            return m_result;
        }

        std::vector<id::menu::CircleSelect::Item> CircleSelect::getOptions() const {
            return m_options;
        }

        void CircleSelect::display(std::vector<id::menu::CircleSelect::Item> options, const std::string& input, std::function<void(int)> callback, const std::wstring& title) {
            if (m_state == id::menu::CircleSelect::State::Finished) {
                m_frameCounter = 0;
                m_cursor = 0;
                m_title = title;
                m_input = input;
                m_state = id::menu::CircleSelect::State::FadingIn;
                m_options = options;
                m_callback = callback;
            }
        }

        void CircleSelect::close(bool dismiss) {
            m_frameCounter = 0;

            if (dismiss) {
                m_result = -1;
            }

            m_state = id::menu::CircleSelect::State::FadingOut;
        }

        void CircleSelect::update() {
            using namespace id::events;

            if (m_state == State::FadingIn || m_state == State::Displaying) {
                if (id::InputManager::getInstance().getCachedInputState(m_input) == PressEvent::State::Release) {
                    m_state = id::menu::CircleSelect::State::FadingOut;
                }
            }

            // Fading in and out is up to the implementing classes
            switch (m_state) {
            case id::menu::CircleSelect::State::Displaying:
                {
                    float angle = id::InputManager::getInstance().getJoystickPolar(id::InputManager::Joystick::Left).u;
                    float weight = id::InputManager::getInstance().getJoystickPolar(id::InputManager::Joystick::Left).v;

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
            case id::menu::CircleSelect::State::CleanUp:
                {
                    m_frameCounter = 0;
                    m_cursor = 0;

                    m_options.clear();
                    m_title = L"";
                    m_input = "";

                    m_state = id::menu::CircleSelect::State::Finished;

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

        id::menu::CircleSelect::State CircleSelect::getState() {
            return m_state;
        }

        // protected methods
        CircleSelect::CircleSelect() :
        m_cursor(-1),
        m_result(-1),
        m_frameCounter(0),
        m_state(id::menu::CircleSelect::State::Finished),
        m_title(L""),
        m_input(""),
        m_callback([](int){}),
        m_font(id::settings::DefaultFontPath),
        m_textObject(m_font) { /* do nothing */ }
    } /* menu */
} /* id */
