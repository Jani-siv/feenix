#include "Ticks.hpp"

#include <utility>
#include <iostream>

namespace devices {
namespace cpu {

Ticks::Ticks(std::string runMode)
{
    if (!runMode.empty()) {
        runMode_ = std::move(runMode);
    }
    else
        runMode_ = "free";
}
//todo clean this function
uint64_t Ticks::runClock()
{
    if (runMode_.find("free") == 0)
    {
        return 0x1;
    }
    bool ask = true;
    if (runMode_.find("step") == 0)
    {
        std::string line;
        line = readLine();
        while(true)
        {
            bool allOk = true;
            if (line.empty())
            {
                std::cout << "Line was empty" << std::endl;
                allOk = false;
            }
            for (auto &i: line)
            {
                if (!std::isdigit(i))
                {
                    //todo bug in code it's hiding somewhere here... :)
                    std::cout << "line contains chars" << std::endl;
                    allOk = false;
                }
            }
            if (allOk) {
                break;
            }
            else {
                readLine();
            }
        }
        uint64_t tic = std::stoul(line);
        return tic;
    }
}

std::string Ticks::readLine()
{
    std::string line;
    std::cout << "give step num and enter to continue" << std::endl;
    std::cin >> line;
    return line;
}

} //namespace cpu
} //namespace devices
