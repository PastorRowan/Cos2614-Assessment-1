
#pragma once

#include "pages/pages.h"
#include "VehiclesFile.h"

// Main application interface for the vehicle rental system
class App {

    private:

        // Stores the current application error code
        int errorCode = 0;

        // Identifier for the currently active application page
        pages::Id currentPageId;

        // Gets the current error code
        int getErrorCode() const;

        // Handles vehicle file storage and management
        VehiclesFile vehiclesFile;

    public:

        /**
         * Constructs the application controller.
         *
         * Initializes the application state, file management system,
         * and starting page.
         *
         * vehiclesFileLocationP - Path to the vehicles data file
         * currentVehicleIdFileLocationP - Path to the current vehicle ID file
         * currentPageIdP - Initial application page identifier
         * ok - Indicates whether initialization was successful
         */
        App(
            const QString vehiclesFileLocationP,
            const QString currentVehicleIdFileLocationP,
            const pages::Id currentPageIdP,
            bool ok = false
        );

        // Gets the current active page identifier
        pages::Id getCurrentPageId() const;

        // Sets the current active page
        void setCurrentPageId(pages::Id id);

        // Provides access to the vehicles file manager
        VehiclesFile& getVehiclesFile();

        // Sets the application error code.
        void setErrorCode(int e);

        /**
          * Checks whether the application is currently in an error state
          * Returns True if an error exists, otherwise false
          */
        bool isErrorState();

        // Exits the application safely.
        void appExit(const int errorCode, const char* exitMsg = "");

};
