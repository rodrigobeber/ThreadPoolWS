#pragma once

#include <functional>

class IConcurrencyModel {
public:
    virtual void execute(std::function<void()> task) = 0;
    virtual ~IConcurrencyModel() = default;
};