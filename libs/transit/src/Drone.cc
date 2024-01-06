#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "DroneObserver.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "RechargeStation.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  observer_ = new DroneObserver(this);
  battery = new BatteryDecorator(this);
  battery->recharge();
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (observer_) delete observer_;
  if (battery) delete battery;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      notify(2);
      notify(3);
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

void Drone::notify(int situation) { observer_->constructMessage(situation); }

void Drone::update(double dt) {
  if (battery->needsCharge()) {
    if (!toRechargeStation) {
      findRechargeStation();
      notify(7);
    }

    toRechargeStation->move(this, dt);

    if (toRechargeStation->isCompleted()) {
      delete toRechargeStation;
      toRechargeStation = nullptr;
      battery->recharge();
      notify(8);
      if (package) {
        toPackage = new BeelineStrategy(getPosition(), package->getPosition());
      }
    }
  } else if (available) {
    notify(1);
    getNextDelivery();
  } else if (toPackage) {
    // If there's an ongoing delivery, check the battery
    if (!battery->needsCharge()) {
      toPackage->move(this, dt);
      battery->update(dt);

      if (toPackage->isCompleted()) {
        delete toPackage;
        toPackage = nullptr;
        pickedUp = true;
        notify(4);
        notify(5);
      }
    } else {
      // If the battery is depleted mid-delivery, leave the package and go
      // recharge
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      findRechargeStation();
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    battery->update(dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      notify(6);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

Package* Drone::getPackage() { return package; }

void Drone::findRechargeStation() {
  if (model) {
    Vector3 currentPosition = getPosition();
    const std::vector<RechargeStation*>& rechargeStations =
        model->getRechargeStations();

    if (!rechargeStations.empty()) {
      RechargeStation* nearestRechargeStation = nullptr;
      double minDistance = std::numeric_limits<double>::max();

      // Find the nearest recharge station
      for (RechargeStation* station : rechargeStations) {
        double distance =
            calculateDistance(currentPosition, station->getPosition());

        if (distance < minDistance) {
          minDistance = distance;
          nearestRechargeStation = station;
        }
      }

      if (nearestRechargeStation) {
        Vector3 rechargeStationPosition = nearestRechargeStation->getPosition();
        toRechargeStation = new JumpDecorator(
            new BeelineStrategy(currentPosition, rechargeStationPosition));
      }
    }
  }
}

double Drone::calculateDistance(const Vector3& pos1,
                                const Vector3& pos2) const {
  return std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2) +
                   std::pow(pos1.z - pos2.z, 2));
}
