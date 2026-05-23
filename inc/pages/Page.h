
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

        public:

            virtual void update(const QString& input, App& app) = 0;
            virtual QString compose(App& app) const = 0;

    };

};
