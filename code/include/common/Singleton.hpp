/**
 * @file common/Singleton.hpp
 * @brief Defines the Singleton-class
 */
#pragma once

namespace id {
    /**
     * @brief Allows child-classes to only have a single shared instance.
     * @note child-classes should make their constructors protected or private to avoid multiple instances
     * @tparam T The class the Singleton should return an instance of. Child-classes should provide themselves when inheriting this class.
     */
    template <class T>
    class Singleton {
    public:
        /**
         * @brief Returns the instance of the Singleton
         * @return The instance
         */
        static T& getInstance() {
            static T instance;
            return instance;
        };
    };
} /* id */
