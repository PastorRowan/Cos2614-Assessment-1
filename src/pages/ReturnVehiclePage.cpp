
// Implements the ReturnVehiclePage class used for returning vehicles

#include "pages/pages.h"
#include "App.h"

#include <QString>
#include <QRegularExpression>

// Returns the current interaction mode
pages::ReturnVehiclePage::Mode pages::ReturnVehiclePage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::ReturnVehiclePage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu input for the ReturnVehiclePage
void pages::ReturnVehiclePage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else if (input == "1") {  
        setMode(Mode::enter_id);
    } else if (input == "2") {
        if (isFormEntered()) {
            app.getVehiclesFile().returnVehicleById(
                fields.vehicleId,
                status
            );
            fields = pages::ReturnVehiclePage::Fields {};
        } else {
            status = "Form is not fully entered";
        };
    } else {
        status = "\"" + input + "\" is invalid input";
    };
};

// Handles input for the vehicle ID field
void pages::ReturnVehiclePage::handleEnterVehicleIdInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression("^\\d+$"))) {
        setMode(Mode::menu);
        fields.vehicleId = input;
    } else {
        status = "\"" + input + "\" is invalid input";
    };
};

/**
 * Static UI templates for ReturnVehiclePage modes
 *
 * Each template defines the console layout for a specific page state:
 * - Menu view
 * - Vehicle ID entry view
 *
 * Placeholders:
 * - %1 : Current vehicle ID field value
 * - %2 : Status or error message
 */
const QString pages::ReturnVehiclePage::pageModeTemplates[static_cast<int>(pages::ReturnVehiclePage::Mode::count)] = {

    QString(R"(
==================  RETURN VEHICLE  ===================

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

 q. back

  >Current id:                 %1

--------------------------------------------------------
Type new ID and press Enter
%2
--------------------------------------------------------
)"),

};

// Checks whether all required form fields contain values
bool pages::ReturnVehiclePage::isFormEntered() const {
    return
        !fields.vehicleId.isEmpty()
    ;
};

// Updates the page state based on user input
void pages::ReturnVehiclePage::update(const QString& input, App& app) {

    status = "";

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted ReturnVehiclePage output
QString pages::ReturnVehiclePage::compose(App& app) const {

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            pages::composeField(fields.vehicleId),
            status
        )
    ;

    return outputStr;

};

