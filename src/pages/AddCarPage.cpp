
// Implements the AddCarPage class used for adding cars to the vehicle rental system

#include "pages/pages.h"
#include "App.h"

#include <QString>
#include <QRegularExpression>

// Returns the current interaction mode
pages::AddCarPage::Mode pages::AddCarPage::getMode() const {
    return mode;
};

// Updates the current interaction mode
void pages::AddCarPage::setMode(const Mode newMode) {
    mode = newMode;
};

// Handles menu-mode user input
void pages::AddCarPage::handleMenuInput(const QString& input, App& app) {
    if (input == "q") {
        app.setCurrentPageId(pages::Id::HomePage);
    } else if (input == "1") {
        setMode(Mode::enter_brand);
    } else if (input == "2") {
        setMode(Mode::enter_model);
    } else if (input == "3") {
        setMode(Mode::enter_pricePerDay);
    } else if (input == "4") {
        setMode(Mode::enter_numberOfDoors);
    } else if (input == "5") {
        setMode(Mode::enter_numberOfSeats);
    } else if (input == "6") {
        if (isFormEntered()) {
            app.getVehiclesFile().addCar(
                fields.brand,
                fields.model,
                fields.pricePerDay.toDouble(),
                fields.numberOfDoors.toInt(),
                fields.numberOfSeats.toInt(),
                getStatusRef()
            );
            fields = pages::AddCarPage::Fields {};
        } else {
            setStatus("Form is not fully entered");
        };
    } else {
        setStatus("\"" + input + "\" is not a valid menu option");
    };
};

// Handles input for the brand field
void pages::AddCarPage::handleEnterBrandInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else {
        fields.brand = input;
        setMode(Mode::menu);
    };
};

// Handles input for the model field.
void pages::AddCarPage::handleEnterModelInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else {
        fields.model = input;
        setMode(Mode::menu);
    };
};

// Handles input for the rental price-per-day field.
void pages::AddCarPage::handleEnterPricePerDayInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression(R"(^[+]?\d+(\.\d+)?$)"))) {
        fields.pricePerDay = input;
        setMode(Mode::menu);
    } else {
        setStatus("\"" + input + "\" is not a postive decimal number (e.g 123.45)");
    };
};

// Handles input for the number-of-doors field
void pages::AddCarPage::handleEnterNumberOfDoorsInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression(R"(^\d+$)"))) {
        fields.numberOfDoors = input;
        setMode(Mode::menu);
    } else {
        setStatus("\"" + input + "\" is not a positive integer (e.g 123)");
    };
};

// Handles input for the number-of-seats field
void pages::AddCarPage::handleEnterNumberOfSeatsInput(const QString& input, App& app) {
    if (input == "q") {
        setMode(Mode::menu);
    } else if (input.contains(QRegularExpression(R"(^\d+$)"))) {
        fields.numberOfSeats = input;
        setMode(Mode::menu);
    } else {
        setStatus("\"" + input + "\" is not a positive integer (e.g 123)");
    };
};

/**
 * Static UI templates for each AddCarPage mode
 *
 * Each template represents a different screen layout depending
 * on the active input mode
 *
 * Templates use QString::arg() placeholders for:
 * - Brand
 * - Model
 * - Price per day
 * - Number of doors
 * - Number of seats
 * - Status/error messages
 */
const QString pages::AddCarPage::pageModeTemplates[static_cast<int>(pages::AddCarPage::Mode::count)] = {


    QString(R"(
=================     ADD CAR     ====================

Options:

 1. Enter brand             - %1
 2. Enter model             - %2
 3. Enter price per day     - %3
 4. Enter number of doors   - %4
 5. Enter number of seats   - %5
 6. Submit vehicle
 q. Home

--------------------------------------------------------
%6
--------------------------------------------------------
)"),


    QString(R"(
=========    ADD CAR - ENTER BRAND   =================



  >Current brand:              %1
 Current model:                %2
 Current price per day:        %3
 Current number of doors:      %4
 Current number of seats:      %5

 q. Back

--------------------------------------------------------
Type new ID and press Enter
%6
--------------------------------------------------------
)"),


QString(R"(
============   ADD CAR - ENTER MODEL  =================



 Current brand:                %1
  >Current model:              %2
 Current price per day:        %3
 Current number of doors:      %4
 Current number of seats:      %5

 q. Back

--------------------------------------------------------
Type new 'model' and press Enter
%6
--------------------------------------------------------
)"),

QString(R"(
========     ADD CAR - PRICE PER DAY   =============



 Current brand:                %1
 Current model:                %2
  >Current price per day:      %3
 Current number of doors:      %4
 Current number of seats:      %5

 q. Back

--------------------------------------------------------
Type new 'price per day' and press Enter
%6
--------------------------------------------------------
)"),

QString(R"(
===========  ADD CAR - NUMBER OF DOORS  =============



 Current brand:                %1
 Current model:                %2
 Current price per day:        %3
  >Current number of doors:    %4
 Current number of seats:      %5

 q. Back

--------------------------------------------------------
Type new 'number of doors' and press Enter
%6
--------------------------------------------------------
)"),

QString(R"(
=========== ADD CAR - NUMBER OF DOORS ================



 Current brand:                %1
 Current model:                %2
 Current price per day:        %3
 Current number of doors:      %4
  >Current number of seats:    %5

 q. Back

--------------------------------------------------------
Type new 'number of seats' and press Enter
%6
--------------------------------------------------------
)")

};

// Checks whether all required form fields contain values
bool pages::AddCarPage::isFormEntered() const {
    return
        !fields.brand.isEmpty() &&
        !fields.model.isEmpty() &&
        !fields.pricePerDay.isEmpty() &&
        !fields.numberOfDoors.isEmpty() &&
        !fields.numberOfSeats.isEmpty()
    ;
};

/**
 * Updates the page state using user input
 *
 * Clears the current status message and dispatches the input
 * to the handler associated with the current mode
 */
void pages::AddCarPage::update(const QString& input, App& app) {

    clearStatus();

    (this->*handlers[static_cast<int>(mode)])(input, app);

};

/**
 * Composes the current page view as a formatted QString
 *
 * Inserts current field values and status messages into the
 * active page template
 */
QString pages::AddCarPage::compose(App& app) const {

    QString
        outputStr = pageModeTemplates[static_cast<int>(mode)]
        .arg(
            pages::composeField(fields.brand),
            pages::composeField(fields.model),
            pages::composeField(fields.pricePerDay),
            pages::composeField(fields.numberOfDoors),
            pages::composeField(fields.numberOfSeats),
            getStatus()
        )
    ;

    return outputStr;

};
