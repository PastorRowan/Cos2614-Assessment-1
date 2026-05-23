
#pragma once

#include <QString>

namespace pages {

    /**
     * The Id enum represents all available pages in the application
     *
     * Each value corresponds to a specific UI page used for navigation
     * within the application
     */
    enum class Id {
        AddCarPage,
        AddMotorcyclePage,
        DisplayAllVehiclesPage,
        DisplayAvailableVehiclesOnlyPage,
        HomePage,
        RentVehiclePage,
        ReturnVehiclePage,
        SearchVehicleByIdPage,
        count
    };

};
