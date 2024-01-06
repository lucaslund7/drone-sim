#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <deque>
#include <map>
#include <set>

#include "CompositeFactory.h"
#include "Drone.h"
#include "IController.h"
#include "IEntity.h"
#include "RechargeStation.h"
#include "Robot.h"
#include "graph.h"

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::IGraph* graph) { this->graph = graph; }

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   *
   * @param id of the entity to be removed
   */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns IGraph* graph pointer
   */
  const routing::IGraph* getGraph();

  /**
   * @brief Calls sendEventToView directly to the controller
   * @param event Type string that contains the command to be called in main.js.
   * @param details Type JsonObject that contains a reference to the information
   * to be sent to the front end.
   * @returns Void
   */
  void sendEventThrough(const std::string& event, const JsonObject& details);

  std::deque<Package*> scheduledDeliveries;

  /**
   * @brief Gets the recharge stations in the simulation
   * @return a vector of RechargeStation pointers
   */
  std::vector<RechargeStation*> getRechargeStations() const;

 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  void removeFromSim(int id);
  const routing::IGraph* graph;
  CompositeFactory entityFactory;
  std::vector<RechargeStation*> rechargeStations;
};

#endif
