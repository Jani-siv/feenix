#pragma once

#include <string>

namespace devices {
namespace cpu {

enum class RunMode : uint8_t {
    freerun = 0,
    steps = 1,
    error = 2
};

class Ticks {
public:
    Ticks(std::string runMode);
    ~Ticks()=default;
    uint64_t runClock();
private:
    std::string runMode_;
    void setRunMode();
    RunMode mode{};
protected:
    virtual std::string readLine();
};

} //namespace cpu
} //namespace devices
