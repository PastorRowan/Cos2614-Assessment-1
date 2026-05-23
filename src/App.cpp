
// Implementation of the main application interface

#include "App.h"
#include "pages/pages.h"
#include "VehiclesFile.h"

#include <cstdlib>
#include <QDebug>

// Constructs the main application instance
App::App(
    const QString vehiclesFileLocationP,
    const QString currentVehicleIdFileLocationP,
    const pages::Id currentPageIdP,
    bool ok
):
    vehiclesFile(
        vehiclesFileLocationP,
        currentVehicleIdFileLocationP,
        ok
    ),
    currentPageId(currentPageIdP) {

    if (!ok) {
        appExit(1, "Faled to initialise app");
        return;
    };

};

// Gets the current application error code
int App::getErrorCode() const {
    return errorCode;
};

// Sets the application error code
void App::setErrorCode(int e) {
    errorCode = e;
};

// Checks whether the application is in an error state
bool App::isErrorState() {
    return errorCode != 0;
};

// Retrieves the current active page ID
pages::Id App::getCurrentPageId() const {
    return currentPageId;
};

// Sets the current active page
void App::setCurrentPageId(pages::Id id) {
    currentPageId = id;
};

// Provides access to the VehiclesFile subsystem
VehiclesFile& App::getVehiclesFile() {
    return vehiclesFile;
};

// Terminates the application immediately
void App::appExit(const int errorCode, const char* exitMsg) {
    qDebug() << exitMsg;
    std::exit(errorCode);
};
