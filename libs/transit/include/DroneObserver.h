#ifndef DRONE_OBSERVER_H_
#define DRONE_OBSERVER_H_

#include "EntityObserver.h"
#include "Drone.h"
#include "Package.h"

/**
 * @class DroneObserver
 * @brief Observer class for the drone entity. Used to send notifications
 * about the current state of the drone.
 */
class DroneObserver : public EntityObserver {
 public:
  /**
   * @brief DroneObservers are created with a drone.
   * @param drone Drone pointer of drone to be observed.
   */
  DroneObserver(Drone* drone);

  /**
   * @brief Destructor
   */
  virtual ~DroneObserver();

  /**
   * @brief Constructs notification depending on the sitution of
   * the drone and the drone's name.
   * @param situation Int used for determining what state the drone is in.
   */
  void constructMessage(int situation) override;

 private:
  Drone* drone_ = nullptr;
};

#endif
