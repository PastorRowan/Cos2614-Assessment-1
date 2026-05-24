
// Implements the RentVehiclePage class used for renting vehicles in the vehicle rental system

#include "pages/pages.h"
#include "App.h"

#include <QString>
#include <QRegularExpression>

// Returns the current interaction mode
pages::RentVehiclePage::Mode pages::RentVehiclePage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::RentVehiclePage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu input for the RentVehiclePage
void pages::RentVehiclePage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else if (input == "1") {
        setMode(Mode::enter_id);
    } else if (input == "2") {
        if (isFormEntered()) {
            app.getVehiclesFile().rentVehicleById(
                fields.vehicleId,
                getStatusRef()
            );
            fields = pages::RentVehiclePage::Fields {};
        } else {
            setStatus("Form is not fully entered");
        };
    } else {
        setStatus("\"" + input + "\" is not a valid menu option");
    };
};

// Handles input for the vehicle ID field
void pages::RentVehiclePage::handleEnterVehicleIdInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression("^\\d+$"))) {
        setMode(Mode::menu);
        fields.vehicleId = input;
    } else {
        setStatus("\"" + input + "\" is not a positive integer (e.g 123)");
    };
};

/**
 * Static UI templates for RentVehiclePage modes
 *
 * Each template represents a console screen for a specific state:
 * - Menu view
 * - Vehicle ID input view
 *
 * Placeholders:
 * - %1 : Current vehicle ID field
 * - %2 : Status or error message
 */
const QString pages::RentVehiclePage::pageModeTemplates[static_cast<int>(pages::RentVehiclePage::Mode::count)] = {

    QString(R"(
====================  RENT VEHICLE  ====================

Options:

 1. Enter vehicle id          - %1
 2. Submit
 q. Back

--------------------------------------------------------
%2
--------------------------------------------------------
)"),

    QString(R"(
========  RENT VEHICLE - ENTER VEHICLE Id  =============

  >Current id:                 %1

 q. back

--------------------------------------------------------
Type new ID and press Enter
%2
--------------------------------------------------------
)")

};

// Checks whether all required form fields contain values
bool pages::RentVehiclePage::isFormEntered() const {
    return
        !fields.vehicleId.isEmpty()
    ;
};

// Updates the page state based on user input
void pages::RentVehiclePage::update(const QString& input, App& app) {

    clearStatus();

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted RentVehiclePage output
QString pages::RentVehiclePage::compose(App& app) const {

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            pages::composeField(fields.vehicleId),
            getStatus()
        )
    ;

    return outputStr;

};
