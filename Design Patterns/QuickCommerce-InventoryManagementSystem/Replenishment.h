#ifndef REPLENISHMENT_H
#define REPLENISHMENT_H

#include <map>

class InventoryManager;

class ReplenishStrategy {
public:
    virtual ~ReplenishStrategy() = default;
    virtual void replenish(InventoryManager* manager,
                           const std::map<int, int>& itemsToReplenish) = 0;
};

class ThresholdReplenishStrategy : public ReplenishStrategy {
private:
    int threshold;

public:
    explicit ThresholdReplenishStrategy(int threshold);
    void replenish(InventoryManager* manager,
                   const std::map<int, int>& itemsToReplenish) override;
};

class WeeklyReplenishStrategy : public ReplenishStrategy {
public:
    void replenish(InventoryManager* manager,
                   const std::map<int, int>& itemsToReplenish) override;
};

#endif
