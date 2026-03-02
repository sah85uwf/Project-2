//Sophia Herrmann

#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <string>

struct Process {
    char id;
    double arrival;
    double burst;
    double remaining;
    double firstStart;
    double finishTime;
    bool started;
};

struct Metrics {
    double turnaround;
    double wait;
    double response;
};

bool readInput(const std::string &filename,
               double &contextSwitch,
               double &quantum,
               std::vector<Process> &procs);

void printInput(double contextSwitch,
                double quantum,
                const std::vector<Process> &procs);

void computeMetrics(const std::vector<Process> &procs,
                    std::vector<Metrics> &metrics,
                    double &avgTA,
                    double &avgWait,
                    double &avgResp);

void printMetrics(const std::vector<Process> &procs,
                  const std::vector<Metrics> &metrics,
                  double avgTA,
                  double avgWait,
                  double avgResp);

#endif
