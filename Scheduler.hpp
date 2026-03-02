//Sophia Herrmann

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include "Process.hpp"

void runRoundRobin(const std::vector<Process> &original,
                   double contextSwitch,
                   double quantum,
                   std::vector<Process> &result,
                   std::vector<std::pair<double,char>> &ganttTimes);

void printGantt(const std::vector<std::pair<double,char>> &ganttTimes,
                double quantum,
                double contextSwitch = 0.0);

#endif