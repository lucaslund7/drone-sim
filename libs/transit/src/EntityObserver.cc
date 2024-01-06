#include "EntityObserver.h"


EntityObserver::EntityObserver(IEntity* entity) : entity_(entity) {
    message_ = "Observer for " + entity_->getName() + " has been created";
    printInfo();
}

EntityObserver::~EntityObserver() {}

void EntityObserver::constructMessage(int situation) {
    std::string m = "Generic EntityObserver constructMessage has been called";
    update(m);
}


void EntityObserver::update(const std::string &message) {
    if (message_ == message) {
        return;
    }
    message_ = message;
    printInfo();
}

void EntityObserver::printInfo() {
    JsonObject info;
    info["message"] = message_;
    SimulationModel* model_ = entity_->getModel();
    if (model_) {
        model_->sendEventThrough("Notify", info);
    }
}
