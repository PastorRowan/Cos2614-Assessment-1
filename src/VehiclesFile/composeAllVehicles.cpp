
#include "VehiclesFile.h"
#include "helpers.h"
#include "vehicles/vehicles.h"

#include <QString>
#include <QStringList>

/**
 * Converts all stored vehicles into a formatted QString table
 *
 * Vehicles are grouped by type and displayed in aligned columns
 *
 * Car fields include:
 * - Type ID
 * - Vehicle ID
 * - Brand
 * - Model
 * - Price per day
 * - Rental status
 * - Number of doors
 * - Number of seats
 *
 * Motorcycle fields include:
 * - Type ID
 * - Vehicle ID
 * - Brand
 * - Model
 * - Price per day
 * - Rental status
 * - Engine capacity
 *
 * Returns a formatted QString representation of all stored vehicles
 */
QString VehiclesFile::composeAllVehicles() const {

    QStringList allCarsQStringList;

    QStringList allMotorcyclesQStringList;

    for (int i = 0; i < vehiclesQVector.size(); i++) {
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
