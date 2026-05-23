
// Implementation of formatted display for available (non-rented) vehicles

#include "VehiclesFile.h"
#include "helpers.h"
#include "vehicles/vehicles.h"

#include <QString>
#include <QStringList>

/**
 * Builds a formatted table of all available vehicles
 *
 * This function iterates through the internal vehicle collection and
 * produces a structured text table containing only vehicles whose
 * rental status is false
 *
 * Vehicles are separated by type:
 * - Cars are listed first with full attributes (doors, seats)
 * - Motorcycles are listed second with engine capacity
 *
 * Formatting details:
 * - Uses fixed-width columns for readability
 * - Converts rental status into "Yes"/"No"
 * - Parses vehicle string representation using '|' delimiter
 * Returns A formatted QString containing all available vehicles
 */
QString VehiclesFile::composeAvailableVehiclesOnly() const {

    QStringList allCarsQStringList;

    QStringList allMotorcyclesQStringList;

    for (int i = 0; i < vehiclesQVector.size(); i++) {

        if (vehiclesQVector[i]->getIsRented()) {
            continue;
        };

        switch (vehiclesQVector[i]->getTypeId()) {
            case vehicles::TypeId::car:
                allCarsQStringList.push_back(vehiclesQVector[i]->toQString());
                break;
            case vehicles::TypeId::motorCycle:
                allMotorcyclesQStringList.push_back(vehiclesQVector[i]->toQString());
                break;
            default:
                break;
        };

    };

    QString allCarsQString = composePipeSeparatedValuesToTable(
        allCarsQStringList,
        vehicles::Car::fieldNames,
        { 2, 2, 2, 2, 2, 2, 2, 2 }
    );

    QString allMotorCyclesQString = composePipeSeparatedValuesToTable(
        allMotorcyclesQStringList,
        vehicles::Motorcycle::fieldNames,
        { 2, 2, 2, 2, 2, 2, 2 }
    );

    allCarsQString += "\n\n";

    QString outputStr = allCarsQString + allMotorCyclesQString;

    return outputStr;

};
