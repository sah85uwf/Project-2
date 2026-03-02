//Sophia Herrmann

#include "Scheduler.hpp"
#include <queue>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

void runRoundRobin(const std::vector<Process> &original,
                   double contextSwitch,
                   double quantum,
                   std::vector<Process> &result,
                   std::vector<std::pair<double,char>> &ganttTimes) {
    result = original;
    ganttTimes.clear();

    size_t n = result.size();
    if (n == 0) return;

    std::queue<int> ready;
    double currentTime = 0.0;
    size_t completed = 0;
    size_t nextArrivalIdx = 0;

    std::vector<int> order(n);
    for (size_t i = 0; i < n; ++i) order[i] = i;
    std::sort(order.begin(), order.end(),
              [&](int i, int j){ return result[i].arrival < result[j].arrival; });

    while (completed < n) {
        while (nextArrivalIdx < n && result[order[nextArrivalIdx]].arrival <= currentTime + 1e-9) {
            ready.push(order[nextArrivalIdx]);
            nextArrivalIdx++;
        }

        if (ready.empty()) {
            if (nextArrivalIdx < n) {
                currentTime = result[order[nextArrivalIdx]].arrival;
                continue;
            }
            break;
        }

        int idx = ready.front(); ready.pop();
        Process &p = result[idx];

        if (!p.started) {
            p.firstStart = currentTime;
            p.started = true;
        }

        double execTime = std::min(quantum, p.remaining);
        double sliceStart = currentTime;
        double sliceEnd = sliceStart + execTime;

        p.remaining -= execTime;
        currentTime = sliceEnd;

        ganttTimes.push_back({sliceStart, p.id});
        ganttTimes.push_back({sliceEnd, ' '});

        
        if (p.remaining <= 1e-9) {
            p.finishTime = currentTime;
            completed++;
        } else {
            ready.push(idx); 
        }

        
        if (contextSwitch > 0.0 && completed < n && !ready.empty()) {
            double csStart = currentTime;
            double csEnd = csStart + contextSwitch;
            currentTime = csEnd;
            ganttTimes.push_back({csStart, 'x'});
            ganttTimes.push_back({csEnd, ' '});
        }
    }
}

void printGantt(const std::vector<std::pair<double,char>> &ganttTimes,
                double quantum,
                double /*contextSwitch*/) {
    std::cout << "The Process scheduling as per Round-Robin Algorithm (Quantum = "
              << static_cast<int>(quantum) << ") is as follows:\n\n";

    if (ganttTimes.empty()) return;

    std::string line;
    for (size_t i=0;i+1<ganttTimes.size();i+=2) {
        double t1d = ganttTimes[i].first;
        char id = ganttTimes[i].second;
        double t2d = ganttTimes[i+1].first;

        int t1 = static_cast<int>(std::round(t1d * 1000.0)/1000.0);  
        int t2 = static_cast<int>(std::round(t2d * 1000.0)/1000.0);

        if (id == 'x') {
            line += std::to_string(t1) + "x" + std::to_string(t2) + "   ";
        } else {
            line += std::to_string(t1) + "   " + id + "   " + std::to_string(t2) + "   ";
        }
    }

    while (!line.empty() && std::isspace(line.back())) line.pop_back();
    std::cout << line << "\n\n";
}