
// Implements the HomePage class, which serves as the main
#include "pages/pages.h"
#include "App.h"

#include <QString>

// Returns the current interaction mode
pages::HomePage::Mode pages::HomePage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::HomePage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles user input in the HomePage menu
void pages::HomePage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.appExit(0);
    } else if (input == "1") {
        app.setCurrentPageId(pages::Id::AddCarPage);
    } else if (input == "2") {
        app.setCurrentPageId(pages::Id::AddMotorcyclePage);
    } else if (input == "3") {
        app.setCurrentPageId(pages::Id::SearchVehicleByIdPage);
    } else if (input == "4") {
        app.setCurrentPageId(pages::Id::DisplayAllVehiclesPage);
    } else if (input == "5") {
        app.setCurrentPageId(pages::Id::DisplayAvailableVehiclesOnlyPage);
    } else if (input == "6") {
        app.setCurrentPageId(pages::Id::RentVehiclePage);
    } else if (input == "7") {
        app.setCurrentPageId(pages::Id::ReturnVehiclePage);
    } else {
        status = "\'" + input + "\' Input is invalid";
    };
};

/**
 * Static template for rendering the HomePage UI
 *
 * This template defines the main menu layout and includes a
 * placeholder for status or error messages
 *
 * Placeholder:
 * - %1 : Status message
 */
const QString pages::HomePage::pageModeTemplates[static_cast<int>(pages::HomePage::Mode::count)] = {

    QString(R"(
====================     HOME     ====================

Options:

 1. Add Car
 2. Add Motorcycle
 3. Search vehicle by ID
 4. Display all vehicles
 5. Display available vehicles only
 6. Rent vehicle
 7. Return vehicle
 q. Exit


--------------------------------------------------------
%1
--------------------------------------------------------
)")

};

// Updates the HomePage state based on user input
void pages::HomePage::update(const QString& input, App& app) {

    status = "";

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted HomePage output string
QString pages::HomePage::compose(App& app) const {

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(status);
    ;

    return outputStr;

};
