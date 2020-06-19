/**
 * @file statemachine/GameState.hpp
 * @brief Defines the GameState-class
 */
#pragma once
#include "StateHandler.hpp"
#include "common/Singleton.hpp"
#include "common/graphics/graphics.hpp"

namespace id {
    namespace game {
        /**
         * @brief The base class for all gamestates
         */
        class GameState {
        public:
            /**
             * @brief Gets called on destruction
             */
            virtual void cleanup() = 0;

            /**
             * @brief Gets called on entry
             */
            virtual void onEntry() = 0;

            /**
             * @brief Gets called on exit
             */
            virtual void onExit() = 0;

            /**
             * @brief Updates the GameState
             * @param handler  The StateHandler currently responsible for this State
             * @param renderer The Renderer to use
             */
            virtual void update(id::game::StateHandler& handler, id::graphics::Renderer& renderer) = 0;
        };
    } /* game */
} /* id */
