#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) { available = true; }

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (celebration1) delete celebration1;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strategy = package->getStrategyName();
      if (strategy == "astar") {
        toFinalDestination = new AstarStrategy(
            packagePosition, finalDestination, model->getGraph());
        celebration1 = new JumpDecorator(toFinalDestination);
      } else if (strategy == "dfs") {
        toFinalDestination = new DfsStrategy(packagePosition, finalDestination,
                                             model->getGraph());
        celebration1 = new JumpDecorator(new SpinDecorator(toFinalDestination));
      } else if (strategy == "bfs") {
        toFinalDestination = new BfsStrategy(packagePosition, finalDestination,
                                             model->getGraph());
        celebration1 = new SpinDecorator(new SpinDecorator(toFinalDestination));
      } else if (strategy == "dijkstra") {
        toFinalDestination = new DijkstraStrategy(
            packagePosition, finalDestination, model->getGraph());
        celebration1 = new SpinDecorator(new JumpDecorator(toFinalDestination));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
        celebration1 = new SpinDecorator(toFinalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  if (available) getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (celebration1) {
    celebration1->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (celebration1->isCompleted()) {
      delete toFinalDestination;
      delete celebration1;
      toFinalDestination = nullptr;
      celebration1 = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}
