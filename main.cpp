
// Entry point for the Vehicle Rental Management application

#include "pages/pages.h"
#include "App.h"
#include "helpers.h"

#include <QString>
#include <QTextStream>
#include <QCoreApplication>

// Application entry point
int main(int argc, char *argv[]) {

    // Qt core application object required for Qt-based applications
    QCoreApplication qtCoreApp(argc, argv);

    /**
     * Create all application pages
     *
     * Each page is responsible for:
     * - Displaying user interface text
     * - Processing user input
     * - Updating application state
     */
    pages::AddCarPage addCarPage;
    pages::AddMotorCyclePage addMotorcyclePage;
    pages::DisplayAllVehiclesPage displayAllVehiclesPage;
    pages::DisplayAvailableVehiclesOnlyPage displayAvailableVehiclesOnlyPage;
    pages::HomePage homePage;
    pages::RentVehiclePage rentVehiclePage;
    pages::ReturnVehiclePage returnVehiclePage;
    pages::SearchVehicleByIdPage searchVehicleByIdPage;

    /**
     * Array used for fast page lookup and dispatching
     *
     * The array index corresponds directly to the numeric value of
     * `pages::Id`
     *
     * This allows the application to dynamically:
     * - Compose output for the current page
     * - Update the current page using user input
     */
    pages::Page* const pagesArray[static_cast<int>(pages::Id::count)] = {
        &addCarPage,
        &addMotorcyclePage,
        &displayAllVehiclesPage,
        &displayAvailableVehiclesOnlyPage,
        &homePage,
        &rentVehiclePage,
        &returnVehiclePage,
        &searchVehicleByIdPage
    };

    /**
     * Main application object
     *
     * Stores:
     * - Vehicle persistence file locations
     * - Current page state
     * - Application-wide state and logic
     *
     * The application starts on the HomePage
     */
    App app(
        QString("/files/vehiclesQVector.txt"),
        QString("/files/currentVehicleId.txt"),
        pages::Id::HomePage
    );

    // Reads user input from stdin
    QTextStream inp(stdin);

    // Writes application output to stdout
    QTextStream out(stdout);

    // Stores current user input
    QString input = "Input has not been assigned yet";

    // Stores current page output
    QString output = "Output has not been assigned yet";
    
    /**
     * Main application loop
     *
     * Workflow:
     * 1. Compose the current page output
     * 2. Clear the terminal screen
     * 3. Display the output
     * 4. Read user input
     * 5. Allow the current page to process the input
     *
     * The loop continues until the application enters an error state
     */
    do {

        // Generate output for the currently active page by directly indexing the pages lookup table via the current page id
        output = pagesArray[static_cast<int>(app.getCurrentPageId())]->compose(app);

        // Clear the terminal   screen before rendering updated content
        clearScreen();

        // Display the generated page output to the user
        out << output;
        out.flush();

        // Read a full line of user input from the console
        input = inp.readLine();

        // Allow the current page to process user input and update application state
        pagesArray[static_cast<int>(app.getCurrentPageId())]->update(input, app);

    } while(!app.isErrorState());

    // Terminate the application
    return qtCoreApp.exec();

};
