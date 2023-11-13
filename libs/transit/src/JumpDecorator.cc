#include "JumpDecorator.h"

JumpDecorator::JumpDecorator(IStrategy* s) : ICelebrationDecorator(s) {}

void JumpDecorator::celebrate(IEntity* entity, double dt) {
  position = entity->getPosition();
  if (jumpTime < 0.2) {
    entity->setPosition(position + Vector3(0.0, 0.5, 0.0));
  } else if (jumpTime < 0.4) {
    entity->setPosition(position - Vector3(0.0, 0.5, 0.0));
  } else {
    entity->setPosition(position);
    jumpTime = 0.0;
  }

  jumpTime += dt;
  celebrationTime += dt;
  return;
}