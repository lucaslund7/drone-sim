#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntity.h"
#include "RechargeStation.h"

class BatteryDecorator : public IEntity {
 private:
  IEntity* drone;
  double batteryPercent;

 public:
  /**
   * @brief Construct a new Battery Decorator object
   *
   * @param[in] IEntity* drone - the drone to decorate with battery
   */
  BatteryDecorator(IEntity* drone);

  /**
   * @brief Deconstructor for Battery Decorator object
   *
   */
  ~BatteryDecorator();

  /**
   * @brief Updates the battery percent of the drone
   * @param[in] double dt - the delta time
   */
  void update(double dt) override;

  /**
   * @brief Recharges the battery of the drone
   */
  void recharge();

  /**
   * @brief Gets the battery percent of the drone
   * @return double - the battery percent
   */
  double getBatteryPercent() const;

  /**
   * @brief Checks if the drone needs to be charged
   * @return bool - true if more than 10%, false otherwise
   */
  bool needsCharge() const;
};

#endif  // BATTERY_DECORATOR_H_
