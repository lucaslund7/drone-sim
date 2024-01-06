#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_

#include <vector>

#include "BatteryDecorator.h"
#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class RechargeStation : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the recharge stations information
   */
  RechargeStation(JsonObject& obj);
  /**
   * @brief Deconstructor
   */
  ~RechargeStation();
  /**
   * @brief Updates the recharge station
   * 
   * @param dt difference in time since last update
  */
  void update(double dt);
};

#endif
