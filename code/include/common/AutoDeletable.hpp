#pragma once

namespace id {
    class AutoDeletable {
    public:
        AutoDeletable() { /* do nothing */ };
        virtual ~AutoDeletable() { /* do nothing */ };

        /**
         * @brief Returns whether the object should automatically delete itself
         * @return `true` if autoDelete is enabled, `false` otherwise
         */
        bool getAutoDelete();

        /**
         * @brief Sets whether the object should automatically delete itself
         * @param autoDelete Whether to automatically delete or not
         */
        void setAutoDelete(bool autoDelete);

        /**
         * @brief Deletes the object
         */
        virtual void deleteThis() = 0;

    protected:
        /* data */
        bool m_autoDelete;
    };
} /* id */
