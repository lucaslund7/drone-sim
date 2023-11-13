

#include "ICelebrationDecorator.h"

class SpinDecorator : public ICelebrationDecorator {
 public:
  /**
   * @brief Spin decorator constructor that creates a spin decorator
   * @param strategy Type IStrategy* that is the strategy to be used
   **/
  SpinDecorator(IStrategy* strategy = nullptr);

  /**
   * @brief celebrate function that is used to spin the entity
   * @param entity Type IEntity* that is the entity to be moved
   * @param dt type double is the time
   **/
  void celebrate(IEntity* entity, double dt);
};
