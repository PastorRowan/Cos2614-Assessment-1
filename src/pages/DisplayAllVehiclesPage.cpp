
// Implements the DisplayAllVehiclesPage class used for viewing all vehicles in the rental system

#include "pages/pages.h"
#include "App.h"

#include <QString>

// Returns the current interaction mode
pages::DisplayAllVehiclesPage::Mode pages::DisplayAllVehiclesPage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::DisplayAllVehiclesPage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu input for the DisplayAllVehiclesPage
void pages::DisplayAllVehiclesPage::handleMenuInput(const QString& input, App& app) {

    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else {
        status = "\"" + input + "\" is invalid input";
    };

};

/**
 * @brief Static page templates for DisplayAllVehiclesPage modes
 *
 * Each template represents the formatted console output
 * for a specific page mode.
 *
 * Template placeholders:
 * - %1 : Formatted vehicle list
 * - %2 : Status or error message
 */
const QString pages::DisplayAllVehiclesPage::pageModeTemplates[static_cast<int>(pages::DisplayAllVehiclesPage::Mode::count)] = {

    QString(R"(
=========   Display All Vehicles Page   =================

Options:

 q. Back

--------------------------------------------------------
%1
--------------------------------------------------------
%2
--------------------------------------------------------
)")

};

// Updates the page state using the provided user input
void pages::DisplayAllVehiclesPage::update(const QString& input, App& app) {

    status = "";

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted page output
QString pages::DisplayAllVehiclesPage::compose(App& app) const {

    const QString allVehiclesTable = app.getVehiclesFile().composeAllVehicles();

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            (allVehiclesTable.isEmpty()
                ? "No vehicles in the system"
                : allVehiclesTable
            ),
            status
        )
    ;

    return outputStr;

};
