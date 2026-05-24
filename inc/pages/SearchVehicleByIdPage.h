
#pragma once

#include "page.h"

#include <QString>

class App;

namespace pages {

    // Page responsible for interactively searching for a vehicle
    class SearchVehicleByIdPage : public Page {

        private:

            // Modes represent the current input and output state of the page
            enum class Mode {
                menu,
                enter_id,
                count
            } mode = Mode::menu;

            // Gets the current page mode
            Mode getMode() const;

            // Updates the current page mode
            void setMode(const Mode newMode);

            /**
             * Static Lookup table mapping each Mode to its page template
             *
             * Removes the need for large switch statements
             * Allows selecting pages dynamically based on mode
             */
            static const QString pageModeTemplates[static_cast<int>(Mode::count)];

            // User entered values collected to search for a car
            struct Fields {
                QString
                    vehicleId = ""
                ;
            } fields;

            // Checks whether all required form fields have been entered
            bool isFormEntered() const;

            // Handles input for each respective state
            void handleMenuInput(const QString& input, App& app);
            void handleEnterVehicleIdInput(const QString& input, App& app);
            
            using Handler = void (SearchVehicleByIdPage::*)(const QString& input, App& app);

            /**
             * Static Lookup table mapping each Mode to its handler
             *
             * Removes the need for large switch statements
             * Allows dispatching handlers dynamically based on mode
             */
            static inline const Handler handlers[static_cast<int>(Mode::count)] = {
                &SearchVehicleByIdPage::handleMenuInput,
                &SearchVehicleByIdPage::handleEnterVehicleIdInput
            };

        public:

            // Processes user input for the current mode
            void update(const QString& input, App& app) override;

            /**
             * Builds the current page UI string
             *
             * Combines the current mode template, entered field values,
             * and status messages into a renderable page string
             *
             * @param app Reference to the main application interface
             * @return Fully composed page text
             */
            QString compose(App& app) const override;

    };

};
