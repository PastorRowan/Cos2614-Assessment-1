
// Contains utility helper functions used throughout the application

#pragma once

#include <QString>
#include <QStringList>
#include <QVector>

// Clears the console screen
void clearScreen();

/**
 * Creates a formatted text table from pipe-separated row data
 *
 * This helper function converts a collection of pipe-separated
 * strings into a neatly aligned table using the provided
 * column headings and spacing configuration
 */
QString composePipeSeparatedValuesToTable(
    const QStringList& pipeSeparatedValues,
    const QStringList& headings,
    const QVector<int>& columnGap
);
