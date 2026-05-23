
// Implementation of simple helper functions

#include "helpers.h"

#include <cstdlib>
#include <QStringList>
#include <QVector>

/**
 * Clears the console screen.
 *
 * This function executes a system command to clear the terminal output,
 * adapting to the underlying operating system:
 *
 * - On Windows (_WIN32): executes "cls"
 * - On Unix/Linux/macOS: executes "clear"
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
};

/**
 * Composes a formatted text table from pipe-separated row data.
 *
 * This helper function takes a list of rows where each row contains
 * pipe-separated (`|`) values, then formats them into a neatly aligned
 * text table using the provided headings and column spacing rules.
 *
 * Example:
 *
 * Input:
 *   pipeSeparatedValues:
 *     {
 *       "Alice|24|Developer",
 *       "Bob|31|Designer"
 *     }
 *
 *   headings:
 *     {
 *       "Name",
 *       "Age",
 *       "Occupation"
 *     }
 *
 *   columnGap:
 *     {
 *       4,
 *       4,
 *       2
 *     }
 *
 * Output:
 *   Name     Age  Occupation
 *   Alice    24   Developer
 *   Bob      31   Designer
 */
QString composePipeSeparatedValuesToTable(
    const QStringList& pipeSeparatedValues,
    const QStringList& headings,
    const QVector<int>& columnGap
) {

    if (
        pipeSeparatedValues.size() == 0 ||
        headings.size() == 0 ||
        columnGap.size() == 0
    ) {
        return QString("");
    };

    const int NUMBER_OF_FIELDS = headings.size();

    if (NUMBER_OF_FIELDS != columnGap.size()) {
        return QString("Error: headings size must be equal to columnGap size");
    };

    QVector<int> largestFields(NUMBER_OF_FIELDS, 0);

    for (int i = 0; i < NUMBER_OF_FIELDS; i++) {
        largestFields[i] = headings[i].trimmed().length();
    };

    for (int i = 0; i < pipeSeparatedValues.size(); i++) {

        const QStringList fields = pipeSeparatedValues[i].split("|");

        if (NUMBER_OF_FIELDS != fields.size()) {
            return QString("Error: field size was incorrect");
        };

        QString trimmedField;
        for (int j = 0; j < NUMBER_OF_FIELDS; j++) {
            trimmedField = fields[j].trimmed();
            if (largestFields[j] < trimmedField.length()) {
                largestFields[j] = trimmedField.length();
            };
        };

    };

    QString outputStr = "";

    QString lineWithPlaceHolders = "";

    for (int i = 1; i <= NUMBER_OF_FIELDS; i++) {
        lineWithPlaceHolders += "%" + QString::number(i);
    };

    QString line = lineWithPlaceHolders;

    for (int i = 0; i < NUMBER_OF_FIELDS; i++) {
        line = line.arg(headings[i].trimmed(), -(largestFields[i] + columnGap[i]));
    };

    line += '\n';

    outputStr += line;

    for (int i = 0; i < pipeSeparatedValues.size(); i++) {

        const QStringList fields = pipeSeparatedValues[i].split("|");

        line = lineWithPlaceHolders;

        for (int j = 0; j < NUMBER_OF_FIELDS; j++) {
            line = line.arg(fields[j].trimmed(), -(largestFields[j] + columnGap[j]));
        };

        line += '\n';

        outputStr += line;

    };

    return outputStr;

};
