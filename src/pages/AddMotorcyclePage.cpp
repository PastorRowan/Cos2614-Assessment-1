
// Implements the AddMotorCyclePage class used for adding motorcycles to the vehicle rental system

#include "pages/pages.h"
#include "App.h"

#include <QString>
#include <QRegularExpression>

// Returns the current interaction mode
pages::AddMotorCyclePage::Mode pages::AddMotorCyclePage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::AddMotorCyclePage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu-mode input for the AddMotorCyclePage
void pages::AddMotorCyclePage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else if (input == "1") {
        setMode(Mode::enter_brand);
    } else if (input == "2") {
        setMode(Mode::enter_model);
    } else if (input == "3") {
        setMode(Mode::enter_pricePerDay);
    } else if (input == "4") {
        setMode(Mode::enter_engineCapacityCC);
    } else if (input == "5") {
        if (isFormEntered()) {
            app.getVehiclesFile().addMotorcycle(
                fields.brand,
                fields.model,
                fields.pricePerDay.toDouble(),
                fields.engineCapacityCC.toInt(),
                getStatusRef()
            );
            fields = pages::AddMotorCyclePage::Fields {};
        } else {
            setStatus("Form is not fully entered");
        };
    } else {
        setStatus("\"" + input + "\" is not a valid menu option");
    };
};

// Handles input for the motorcycle brand field
void pages::AddMotorCyclePage::handleEnterBrandInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else {
        fields.brand = input;
        setMode(Mode::menu);
    };
};

// Handles input for the motorcycle model field
void pages::AddMotorCyclePage::handleEnterModelInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else {
        fields.model = input;
        setMode(Mode::menu);
    };
};

// Handles input for the rental price-per-day field
void pages::AddMotorCyclePage::handleEnterPricePerDayInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression(R"(^[+]?\d+(\.\d+)?$)"))) {
        fields.pricePerDay = input;
        setMode(Mode::menu);
    } else {
        setStatus("\"" + input + "\" is not a postive decimal number (e.g 123.45)");
    };
};

// Handles input for the engine-capacity field
void pages::AddMotorCyclePage::handleEnterEngineCapacityCC(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression(R"(^\d+$)"))) {
        fields.engineCapacityCC = input;
        setMode(Mode::menu);
    } else {
        setStatus("\"" + input + "\" is not a positive integer (e.g 123)");
    };
};

/**
 * @brief Static page templates for all AddMotorCyclePage modes
 *
 * Each template represents a different screen layout depending
 * on the currently active input mode.
 *
 * Templates use QString::arg() placeholders for:
 * - Brand
 * - Model
 * - Price per day
 * - Engine capacity (CC)
 * - Status/error messages
 */
const QString pages::AddMotorCyclePage::pageModeTemplates[static_cast<int>(pages::AddMotorCyclePage::Mode::count)] = {

    QString(R"(
=================   ADD MOTOR Cycle   ====================

Options:

 1. Enter brand                    - %1
 2. Enter model                    - %2
 3. Enter price per day            - %3
 4. Enter engine capacity (CC)     - %4
 5. Submit vehicle
 q. Home

--------------------------------------------------------
%5
--------------------------------------------------------
)"),

    QString(R"(
========= ADD MOTOR CYCLE - ENTER BRAND =================



  >Current brand:                   %1
 Current model:                     %2
 Current price per day:             %3
 Current engine capacity (CC):      %4

 q. Back

--------------------------------------------------------
Type new ID and press Enter
%5
--------------------------------------------------------
)"),

QString(R"(
========== ADD MOTOR CYCLE - ENTER MODEL  =================



 Current brand:                     %1
  >Current model:                   %2
 Current price per day:             %3
 Current engine capacity (CC):      %4

 q. Back

--------------------------------------------------------
Type new 'model' and press Enter
%5
--------------------------------------------------------
)"),

QString(R"(
=======  ADD MOTOR CYCLE - PRICE PER DAY   =============



 Current brand:                      %1
 Current model:                      %2
  >Current price per day:            %3
 Current engine capacity (CC):       %4

 q. Back

--------------------------------------------------------
Type new 'price per day' and press Enter
%5
--------------------------------------------------------
)"),

QString(R"(
======== ADD MOTOR CYCLE - NUMBER OF DOORS  =============



 Current brand:                      %1
 Current model:                      %2
 Current price per day:              %3
  >Current engine Capacity (CC):     %4

 q. Back

--------------------------------------------------------
Type new 'Engine Capacity' and press Enter
%5
--------------------------------------------------------
)")

};

// Checks whether all required form fields contain values
bool pages::AddMotorCyclePage::isFormEntered() const {
    return
        !fields.brand.isEmpty() &&
        !fields.model.isEmpty() &&
        !fields.pricePerDay.isEmpty() &&
        !fields.engineCapacityCC.isEmpty()
    ;
};

// Updates the page state using the provided user input
void pages::AddMotorCyclePage::update(const QString& input, App& app) {

    clearStatus();

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

// Generates the formatted page output string
QString pages::AddMotorCyclePage::compose(App& app) const {

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            pages::composeField(fields.brand),
            pages::composeField(fields.model),
            pages::composeField(fields.pricePerDay),
            pages::composeField(fields.engineCapacityCC),
            getStatus()
        )
    ;

    return outputStr;

};
