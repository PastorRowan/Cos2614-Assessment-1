
#include "pages/pages.h"

#include <QString>

// Returns a copy of the current page status message
QString pages::Page::getStatus() const {
    return status;
};

// Returns a mutable reference to the status message
QString& pages::Page::getStatusRef() {
    return status;
};

// Updates the current page status message
void pages::Page::setStatus(const QString newStatus) {
    status = newStatus;
};

// Clears the current page status message
void pages::Page::clearStatus() {
    status = "";
};
