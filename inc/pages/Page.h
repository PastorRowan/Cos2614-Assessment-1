
#pragma once

#include <QString>

class App;

namespace pages {

    /**
     * Base interface for all application pages.
     *
     * Each page is responsible for:
     *  - Handling updates based on user input or events via update()
     *  - Producing a textual or UI representation via compose()
     */
    class Page {

        private:

            // Stores the current status or feedback message
            QString status = "";

        protected:

            // Returns a copy of the current status message
            QString getStatus() const;

            // Returns a mutable reference to the internal
            QString& getStatusRef();

            // Updates the current status message
            void setStatus(const QString newStatus);

            // Clears the current status message
            void clearStatus();

        public:

            // Updates the page state using the provided input
            virtual void update(const QString& input, App& app) = 0;

            // Generates the formatted output representation of the page
            virtual QString compose(App& app) const = 0;

    };

};
