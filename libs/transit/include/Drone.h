#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;
class DroneObserver;
class BatteryDecorator;
class RechargeStation;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Sends situation to observer to print corresponding message
   * @param situation an int representing what message switch case to trigger
   */
  void notify(int situation);

  /**
   * @brief Gets the linked package of the drone
   * @return a pointer to the drone's current package
   */
  Package* getPackage();



  /**
   * @brief finds the nearest recharge station to the drone
   */
  void findRechargeStation();

  /**
   * @brief Calculates the shortest distance from the drone to one of the recharge stations
   * @return a double representing the clostest distance to a recharge station
   */
  double calculateDistance(const Vector3& pos1, const Vector3& pos2) const;

 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  DroneObserver* observer_ = nullptr;
  BatteryDecorator* battery = nullptr;
  IStrategy* toRechargeStation = nullptr;
};

#endif
