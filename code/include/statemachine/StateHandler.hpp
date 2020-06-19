/**
 * @file statemachine/StateHandler.hpp
 * @brief Defines the Lock class
 */
#pragma once
#include <vector>
#include "switch/switch.hpp"
#include "common/graphics/graphics.hpp"

namespace id {
    namespace game {
        class GameState;

        /**
         * @brief Handles a GameState
         */
        class StateHandler {
        public:
            /**
             * @brief Destructor
             */
            virtual ~StateHandler();

            /**
             * @brief Changes the current state
             * @param state The state to enter
             * @note This calls onExit() on the current GameState before changing
             */
            void change(id::game::GameState& state);

            /**
             * @brief Pushes the given state and enters it
             * @param state The state to push
             * @note This calls onExit() on the current GameState before pushing
             */
            void push(id::game::GameState& state);

            /**
             * @brief Pops the current state and enter the previous
             * @note This calls onEntry() on the entered state
             */
            void pop();

            /**
             * @brief Updates the current GameState
             * @param renderer Tne Renderer to use
             */
            void update(id::graphics::Renderer& renderer);

        private:
            /* data */
            std::vector<id::game::GameState*> m_states;
        };
    } /* game */
} /* id */
