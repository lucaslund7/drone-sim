#include "DroneObserver.h"

DroneObserver::DroneObserver(Drone* drone) : EntityObserver(drone) {
  drone_ = drone;
}

DroneObserver::~DroneObserver() {
  // Was Giving Segmentation Faults when simulation was being stopped.
  // if (drone_) delete drone_;
}

void DroneObserver::constructMessage(int situation) {
  std::string droneName = drone_->getName();
  std::string packageName;
  std::string ownerName;
  if (drone_->getPackage()) {
    packageName = drone_->getPackage()->getName();
    ownerName = drone_->getPackage()->getOwner();
  }
  std::string m;

  switch (situation) {
    case 1:
      m = droneName + " is waiting for a package to deliver.";
      break;
    case 2:
      m = droneName + " has been assigned a package!";
      break;
    case 3:
      m = droneName + " is going to pick up " + packageName + " for " +
          ownerName;
      break;
    case 4:
      m = droneName + " has picked up " + packageName + " for " + ownerName;
      break;
    case 5:
      m = droneName + " will now deliver " + packageName + " to " + ownerName;
      break;
    case 6:
      m = droneName + " has delivered " + packageName + " to " + ownerName +
          "\n";
      break;
    case 7:
      m = droneName + " is going to recharge.";
      break;
    case 8:
      m = droneName + " has recharged.";
      break;
  }
  update(m);
}
