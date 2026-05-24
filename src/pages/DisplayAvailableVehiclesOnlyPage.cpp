
// Implements the DisplayAvailableVehiclesOnlyPage class used for displaying vehicles that are currently available for rent

#include "pages/pages.h"
#include "App.h"

#include <QString>

// Returns the current interaction mode
pages::DisplayAvailableVehiclesOnlyPage::Mode pages::DisplayAvailableVehiclesOnlyPage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::DisplayAvailableVehiclesOnlyPage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu input for the DisplayAvailableVehiclesOnlyPage
void pages::DisplayAvailableVehiclesOnlyPage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else {
        setStatus("\"" + input + "\" is not a valid menu option");
    };
};

/**
 * Static page templates for DisplayAvailableVehiclesOnlyPage modes
 *
 * Each template represents a formatted console layout
 * for a specific page mode
 *
 * Template placeholders:
 * - %1 : List of available vehicles
 * - %2 : Status or error message
 */
const QString pages::DisplayAvailableVehiclesOnlyPage::pageModeTemplates[static_cast<int>(pages::DisplayAvailableVehiclesOnlyPage::Mode::count)] = {

    QString(R"(
======   Display Available Vehicles Only Page   =======

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
void pages::DisplayAvailableVehiclesOnlyPage::update(const QString& input, App& app) {

    clearStatus();

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted page output
QString pages::DisplayAvailableVehiclesOnlyPage::compose(App& app) const {

    const QString allAvailableVehiclesTable = app.getVehiclesFile().composeAvailableVehiclesOnly();

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            (allAvailableVehiclesTable.isEmpty()
                ? "No available vehicles in the system"
                : allAvailableVehiclesTable
            ),
            getStatus()
        )
    ;

    return outputStr;

};
