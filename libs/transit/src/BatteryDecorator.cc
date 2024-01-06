#include "BatteryDecorator.h"

BatteryDecorator::BatteryDecorator(IEntity* drone)
    : drone(drone), batteryPercent(100.0) {}

BatteryDecorator::~BatteryDecorator() {}

void BatteryDecorator::update(double dt) {
  if (!needsCharge()) {
    batteryPercent -= 1.25 * dt;
  }
}

void BatteryDecorator::recharge() { batteryPercent = 100.0; }

double BatteryDecorator::getBatteryPercent() const { return batteryPercent; }

bool BatteryDecorator::needsCharge() const { return batteryPercent < 10.0; }
