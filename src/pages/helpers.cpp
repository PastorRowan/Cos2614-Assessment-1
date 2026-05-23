
// Implementation of utility helper functions used across page modules

#include "pages/pages.h"

#include <QString>

// Formats a field for display in the UI
QString pages::composeField(const QString& field) {
    return field.isEmpty() ? QString("________") : field;
};
