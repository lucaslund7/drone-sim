#ifndef I_OBSERVER_H_
#define I_OBSERVER_H_

#include <string>

class IObserver {
 public:
    /**
    * @brief Virtual destructor for IObserver.
    */
    virtual ~IObserver() {}

    /**
    * @brief Pure virtual function designed for child classes to
    * update what has just been observed
    * @param message String reference of the new message of event observed.
    */
    virtual void update(const std::string &message) = 0;
};


#endif
