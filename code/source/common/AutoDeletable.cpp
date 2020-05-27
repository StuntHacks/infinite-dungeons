#include "common/AutoDeletable.hpp"

namespace id {
    bool AutoDeletable::getAutoDelete() {
        return m_autoDelete;
    }

    void AutoDeletable::setAutoDelete(bool autoDelete) {
        m_autoDelete = autoDelete;
    }
} /* id */
