
#pragma once

#include "Page.h"
#include <QString>

class App;

namespace pages {

    // Page responsible for interactively adding a car
    class AddCarPage : public Page {

        private:

            // Modes represent the current input and output state of the page
            enum class Mode {
                menu,
                enter_brand,
                enter_model,
                enter_pricePerDay,
                enter_numberOfDoors,
                enter_numberOfSeats,
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

            // User entered values collected while building the Car object
            struct Fields {
                QString
                    brand = "",
                    model = "",
                    pricePerDay = "",
                    numberOfDoors = "",
                    numberOfSeats = ""
                ;
            } fields;

            // Checks whether all required form fields have been entered
            bool isFormEntered() const;

            // Handles input for each respective state
            void handleMenuInput(const QString& input, App& app);
            void handleEnterBrandInput(const QString& input, App& app);
            void handleEnterModelInput(const QString& input, App& app);
            void handleEnterPricePerDayInput(const QString& input, App& app);
            void handleEnterNumberOfDoorsInput(const QString& input, App& app);
            void handleEnterNumberOfSeatsInput(const QString& input, App& app);

            using Handler = void (AddCarPage::*)(const QString& input, App& app);

            /**
             * Static Lookup table mapping each Mode to its handler
             *
             * Removes the need for large switch statements
             * Allows dispatching handlers dynamically based on mode
             */
            static inline const Handler handlers[static_cast<int>(Mode::count)] = {
                &AddCarPage::handleMenuInput,
                &AddCarPage::handleEnterBrandInput,
                &AddCarPage::handleEnterModelInput,
                &AddCarPage::handleEnterPricePerDayInput,
                &AddCarPage::handleEnterNumberOfDoorsInput,
                &AddCarPage::handleEnterNumberOfSeatsInput
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
