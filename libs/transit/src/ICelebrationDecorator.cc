#include "ICelebrationDecorator.h"

ICelebrationDecorator::ICelebrationDecorator(IStrategy* s)
    : strategy(s), celebrationTime(0.0) {}

void ICelebrationDecorator::move(IEntity* entity, double dt) {
  if (strategy->isCompleted()) {
    if (!(isCompleted())) {
      celebrate(entity, dt);
    }
  } else {
    strategy->move(entity, dt);
  }
}
bool ICelebrationDecorator::isCompleted() { return celebrationTime >= 4.0; }