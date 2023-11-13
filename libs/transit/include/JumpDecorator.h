

#include "ICelebrationDecorator.h"

class JumpDecorator : public ICelebrationDecorator {
 public:
  /**
   * @brief Jump decorator constructor that creates a jump decorator
   * @param strategy Type IStrategy* that is the strategy to be used
   **/
  JumpDecorator(IStrategy* strategy = nullptr);

  /**
   * @brief celebrate function that is used to make the entity jump
   * @param entity Type IEntity* that is the entity to be moved
   * @param dt type double is the time
   **/
  void celebrate(IEntity* entity, double dt);

 private:
  Vector3 position;
  double jumpTime;
};