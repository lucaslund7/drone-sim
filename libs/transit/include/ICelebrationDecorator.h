#ifndef I_CELEBRATION_DECORATOR_H_
#define I_CELEBRATION_DECORATOR_H_

#include "IStrategy.h"

class ICelebrationDecorator : public IStrategy {
 protected:
  double celebrationTime;

 private:
  IStrategy* strategy;

 public:
  /**
   * @brief Constructor that creates the ICelebrationDecorator object
   * @param strategy Type IStrategy* that is the strategy to be used
   **/
  ICelebrationDecorator(IStrategy* strategy = nullptr);

  /**
   * @brief move function that moves the entity for its celebration
   * @param entity Type IEntity* that is the entity to be moved
   * @param dt type double is the time
   **/
  virtual void move(IEntity* entity, double dt);

  /**
   * @brief isCompleted function that checks if the celebration is completed and
   *returns a bool
   * @return bool that is true if the celebration is completed and false if it
   *is not
   **/
  virtual bool isCompleted();

  /**
   * @brief celebrate function that is used by the decorators to celebrate
   *(JumpDecorator and SpinDecorator)
   * @param entity Type IEntity* that is the entity to be moved
   * @param dt type double is the time
   **/
  virtual void celebrate(IEntity* entity, double dt){};
};

/*
Tried to follow UML and instructions in the readME but not 100% confident.
Changed celebrate to take a pointer not an actual object, was throwing errors
when I used it as an actual object and tried to dereference the pointer so I
guess it was a type?

Constructor for ICelebrationDecorator which default sets the strategy to null
Included it so that when we make Spin Decorator and JumpDecorator they can be
constructed without issue. Not positive that it will work / is necessary but
based it off of PathStrategy.h/.cc

Set celebrate to just empty brackets here then not included in the .cc file
did this since this decorator wont actually have a celebrate, the
jump and spin will have the important stuff and within those
is where we do like entity.rotate(360) if i understand correctly.
*/

#endif  // I_CELEBRATION_DECORATOR_H_