#ifndef RIDER_MAPPING_H
#define RIDER_MAPPING_H

#include <string>
#include <vector>

class Rider {
private:
    std::string name;
    double x;
    double y;
    bool available;

public:
    Rider(std::string riderName, double xCoordinate, double yCoordinate);
    std::string getName() const;
    double distanceTo(double destinationX, double destinationY) const;
    bool isAvailable() const;
    void setAvailable(bool value);
};

class RiderMappingAlgorithm {
private:
    std::vector<Rider*> riders;

public:
    ~RiderMappingAlgorithm();
    void addRider(Rider* rider);
    Rider* assignNearestRider(double destinationX, double destinationY);
};

#endif
