
// Implements the SearchVehicleByIdPage class used for searching vehicles by their unique ID in the vehicle rental system

#include "pages/pages.h"
#include "App.h"
#include "helpers.h"
#include "vehicles/vehicles.h"

#include <QString>
#include <QRegularExpression>

// Returns the current interaction mode
pages::SearchVehicleByIdPage::Mode pages::SearchVehicleByIdPage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::SearchVehicleByIdPage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu input for the SearchVehicleByIdPage
void pages::SearchVehicleByIdPage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else if (input == "1") {  
        setMode(Mode::enter_id);
    } else if (input == "2") {
        if (isFormEntered()) {
            const auto vehiclePointer = app.getVehiclesFile().searchVehicleById(
                fields.vehicleId
            );

            if (vehiclePointer == nullptr) {
                setStatus(
                    QString("Vehicle with id '%1' does not exist").arg(fields.vehicleId)
                );
            } else {
                setStatus(
                    QString(
R"(%1 with vehicle id '%2' =

%3)").arg(
    vehiclePointer->typeIdToPrettyQString(),
    fields.vehicleId,
    vehiclePointer->toPrettyQString()
));
            };

            fields = pages::SearchVehicleByIdPage::Fields {};

        } else {
            setStatus("Form is not fully entered");
        };

    } else {
        setStatus("\"" + input + "\" is not a valid menu option");
    };
};

// Handles input for the vehicle ID field
void pages::SearchVehicleByIdPage::handleEnterVehicleIdInput(const QString& input, App& app) {
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
 * Static UI templates for SearchVehicleByIdPage modes
 *
 * Each template defines the console layout for a specific page state:
 * - Menu view
 * - Vehicle ID entry view
 *
 * Placeholders:
 * - %1 : Current vehicle ID field value
 * - %2 : Status or search result message
 */
const QString pages::SearchVehicleByIdPage::pageModeTemplates[static_cast<int>(pages::SearchVehicleByIdPage::Mode::count)] = {

    QString(R"(
=============  SEARCH VEHICLE BY ID  =================

Options:

 1. Enter vehicle id          - %1
 2. Submit
 q. Back

--------------------------------------------------------
%2
--------------------------------------------------------
)"),

    QString(R"(
=============  SEARCH VEHICLE BY ID  =================

 q. back

  >Current id:                 %1

--------------------------------------------------------
Type new ID and press Enter
%2
--------------------------------------------------------
)")

};

// Checks whether all required form fields contain values
bool pages::SearchVehicleByIdPage::isFormEntered() const {
    return
        !fields.vehicleId.isEmpty()
    ;
};

// Updates the page state based on user input
void pages::SearchVehicleByIdPage::update(const QString& input, App& app) {

    clearStatus();

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted SearchVehicleByIdPage output
QString pages::SearchVehicleByIdPage::compose(App& app) const {

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            pages::composeField(fields.vehicleId),
            getStatus()
        )
    ;

    return outputStr;

};
