#include <cmath>
#include "switch/input.hpp"
#include "opengl.hpp"

#define DPAD_TO_LETTER(mask, direction, letter) \
    if (mask & direction) {          \
        mask &= ~direction;          \
        mask &= letter;              \
    }

namespace id {
    id::nx::InputData Input::m_inputData;

    void Input::scanInput() {
        hidScanInput();

        JoystickPosition posLeft, posRight;
        u32 keysDown, keysHeld, keysUp;

        m_inputData.pressedButtons  = 0;
        m_inputData.downButtons     = 0;
        m_inputData.releasedButtons = 0;

        for(short int i = 0; i < (short int) id::nx::Player::All; ++i) {
            if (isPlayerConnected((id::nx::Player) i)) {
                keysDown = hidKeysDown((HidControllerID) i);
                keysHeld = hidKeysHeld((HidControllerID) i);
                keysUp   = hidKeysUp((HidControllerID) i);

                hidJoystickRead(&posLeft, (HidControllerID) i, JOYSTICK_LEFT);
                hidJoystickRead(&posRight, (HidControllerID) i, JOYSTICK_RIGHT);

                m_inputData.playerData[i].joystickCartesian[static_cast<int>(id::nx::Joystick::Left)] = { posLeft.dx, posLeft.dy };
                m_inputData.playerData[i].joystickCartesian[static_cast<int>(id::nx::Joystick::Right)] = { posRight.dx, posRight.dy };

                // float angleLeft = glm::degrees(atan(abs(posLeft.dy) / abs(posLeft.dx)));
                // float angleRight = glm::degrees(atan(abs(posRight.dy) / abs(posRight.dx)));
                float angleLeft, angleRight;

                if (posLeft.dx == 0 && posLeft.dy == 0) {
                    angleLeft = 0.0f;
                } else {
                    angleLeft = 180.0f - (glm::degrees(atan2(0.0f - posLeft.dy, 0.0f - posLeft.dx)) * -1.0f);
                    angleRight = 180.0f - (glm::degrees(atan2(0.0f - posRight.dy, 0.0f - posRight.dx)) * -1.0f);
                }

                if (posRight.dx == 0 && posRight.dy == 0) {
                    angleRight = 0.0f;
                } else {
                    angleRight = 180.0f - (glm::degrees(atan2(0.0f - posRight.dy, 0.0f - posRight.dx)) * -1.0f);
                }

                m_inputData.playerData[i].joystickPolar[static_cast<int>(id::nx::Joystick::Left)] = { angleLeft, static_cast<float>(sqrt(pow(abs(posLeft.dx), 2) + pow(abs(posLeft.dy), 2))) };
                m_inputData.playerData[i].joystickPolar[static_cast<int>(id::nx::Joystick::Right)] = { angleRight, static_cast<float>(sqrt(pow(abs(posRight.dx), 2) + pow(abs(posRight.dy), 2))) };

                // since there are only d-pad buttons on the left Joy-Con, we need to convert those to A/B/X/Y-presses
                if (hidGetControllerType((HidControllerID) i) == TYPE_JOYCON_LEFT) {
                    // Y
                    DPAD_TO_LETTER(keysDown, id::nx::Button::DPadLeft, id::nx::Button::Y)
                    DPAD_TO_LETTER(keysHeld, id::nx::Button::DPadLeft, id::nx::Button::Y)
                    DPAD_TO_LETTER(keysUp, id::nx::Button::DPadLeft, id::nx::Button::Y)

                    // A
                    DPAD_TO_LETTER(keysDown, id::nx::Button::DPadRight, id::nx::Button::A)
                    DPAD_TO_LETTER(keysHeld, id::nx::Button::DPadRight, id::nx::Button::A)
                    DPAD_TO_LETTER(keysUp, id::nx::Button::DPadRight, id::nx::Button::A)

                    // X
                    DPAD_TO_LETTER(keysDown, id::nx::Button::DPadUp, id::nx::Button::X)
                    DPAD_TO_LETTER(keysHeld, id::nx::Button::DPadUp, id::nx::Button::X)
                    DPAD_TO_LETTER(keysUp, id::nx::Button::DPadUp, id::nx::Button::X)

                    // B
                    DPAD_TO_LETTER(keysDown, id::nx::Button::DPadDown, id::nx::Button::B)
                    DPAD_TO_LETTER(keysHeld, id::nx::Button::DPadDown, id::nx::Button::B)
                    DPAD_TO_LETTER(keysUp, id::nx::Button::DPadDown, id::nx::Button::B)
                }

                m_inputData.playerData[i].controllerData.connected = true;
            } else {
                keysDown = 0;
                keysHeld = 0;
                keysUp   = 0;

                m_inputData.playerData[i].joystickCartesian[static_cast<int>(id::nx::Joystick::Left)] = { 0, 0 };
                m_inputData.playerData[i].joystickCartesian[static_cast<int>(id::nx::Joystick::Right)] = { 0, 0 };

                m_inputData.playerData[i].joystickPolar[static_cast<int>(id::nx::Joystick::Left)] = { 0.0f, 0.0f };
                m_inputData.playerData[i].joystickPolar[static_cast<int>(id::nx::Joystick::Right)] = { 0.0f, 0.0f };

                m_inputData.playerData[i].controllerData.connected = false;
            }

            m_inputData.pressedButtons  |= keysDown;
            m_inputData.downButtons     |= keysHeld;
            m_inputData.releasedButtons |= keysUp;

            m_inputData.playerData[i].pressedButtons  = keysDown;
            m_inputData.playerData[i].downButtons     = keysHeld;
            m_inputData.playerData[i].releasedButtons = keysUp;
        }
    }
} /* id */
