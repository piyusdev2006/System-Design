#include "RiderMapping.h"
#include <cmath>
#include <limits>
#include <utility>

Rider::Rider(std::string riderName, double xCoordinate, double yCoordinate)
    : name(std::move(riderName)), x(xCoordinate), y(yCoordinate),
      available(true) {}

std::string Rider::getName() const {
    return name;
}

double Rider::distanceTo(double destinationX, double destinationY) const {
    return std::sqrt((x - destinationX) * (x - destinationX) +
                     (y - destinationY) * (y - destinationY));
}

bool Rider::isAvailable() const {
    return available;
}

void Rider::setAvailable(bool value) {
    available = value;
}

RiderMappingAlgorithm::~RiderMappingAlgorithm() {
    for (Rider* rider : riders) {
        delete rider;
    }
}

void RiderMappingAlgorithm::addRider(Rider* rider) {
    riders.push_back(rider);
}

Rider* RiderMappingAlgorithm::assignNearestRider(
    double destinationX, double destinationY) {
    Rider* nearest = nullptr;
    double shortestDistance = std::numeric_limits<double>::max();

    for (Rider* rider : riders) {
        if (rider->isAvailable()) {
            double distance = rider->distanceTo(destinationX, destinationY);
            if (distance < shortestDistance) {
                shortestDistance = distance;
                nearest = rider;
            }
        }
    }

    if (nearest != nullptr) {
        nearest->setAvailable(false);
    }
    return nearest;
}
