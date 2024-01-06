#ifndef ENTITY_OBSERVER_H_
#define ENTITY_OBSERVER_H_

#include "IObserver.h"
#include "IEntity.h"
#include "SimulationModel.h"

/**
 * @class EntityObserver
 * @brief Base observer class for all entities. Used to send notifications
 * about the current state of the simulation.
 */
class EntityObserver : public IObserver {
 public:
  /**
   * @brief EntityObservers are created with a entity.
   * @param entity IEntity pointer of entity to be observed.
   */
  EntityObserver(IEntity* entity);

  /**
   * @brief Destructor
   */
  virtual ~EntityObserver();

  /**
   * @brief Constructs notification depending on the sitution of
   * the entity and the entity's name.
   * @param situation Int used for determining what state the entity is in.
   */
  virtual void constructMessage(int situation);

  /**
   * @brief Updates the message_ member variable and then calls to print
   * the new message.
   * @param message String reference of the new message to print.
   */
  void update(const std::string &message) override;

  /**
   * @brief Prints the message_ member variable.
   */
  void printInfo();

 protected:
  std::string message_;
  IEntity* entity_ = nullptr;
};

#endif
