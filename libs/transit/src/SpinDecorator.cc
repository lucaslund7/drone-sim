#include "SpinDecorator.h"

SpinDecorator::SpinDecorator(IStrategy* s) : ICelebrationDecorator(s) {}

void SpinDecorator::celebrate(IEntity* entity, double dt) {
    entity->rotate((0.5/dt)/360.0);
    celebrationTime += dt;
    return;
}