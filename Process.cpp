//Sophia Herrmann

#include "Process.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

bool readInput(const std::string &filename,
               double &contextSwitch,
               double &quantum,
               std::vector<Process> &procs) {
    std::ifstream in(filename.c_str());
    if (!in) return false;

    if (!(in >> contextSwitch)) return false;
    if (!(in >> quantum)) return false;

    std::vector<double> arrivals, bursts;
    double a, b;
    while (in >> a >> b) {
        arrivals.push_back(a);
        bursts.push_back(b);
    }

    procs.clear();
    for (size_t i = 0; i < arrivals.size(); ++i) {
        Process p;
        p.id = static_cast<char>('A' + i);
        p.arrival = arrivals[i];
        p.burst = bursts[i];
        p.remaining = bursts[i];
        p.firstStart = -1.0;
        p.finishTime = -1.0;
        p.started = false;
        procs.push_back(p);
    }
    return true;
}

void printInput(double contextSwitch,
                double quantum,
                const std::vector<Process> &procs) {
    std::cout << "The number of time instants for context switch read from input file: "
              << contextSwitch << "\n\n";

    std::cout << "The arrival times and burst times indicated in the file:\n";
    std::cout << std::left
              << std::setw(8) << "Process"
              << std::setw(12) << "Arrv. Time"
              << "Burst Time\n\n";

    for (const auto &p : procs) {
        std::cout << std::setw(8) << p.id
                  << std::setw(12) << p.arrival
                  << p.burst << "\n";
    }
    std::cout << "\n";
}

void computeMetrics(const std::vector<Process> &procs,
                    std::vector<Metrics> &metrics,
                    double &avgTA,
                    double &avgWait,
                    double &avgResp) {
    size_t n = procs.size();
    metrics.resize(n);
    avgTA = avgWait = avgResp = 0.0;

    for (size_t i = 0; i < n; ++i) {
    const Process &p = procs[i];
    double ta = p.finishTime - p.arrival;
    double wt = ta - p.burst;
    double rt = p.firstStart - p.arrival;

    metrics[i].turnaround = ta;
    metrics[i].wait       = wt;
    metrics[i].response   = rt;

    avgTA   += ta;
    avgWait += wt;
    avgResp += rt;
}

    if (n > 0) {
        avgTA   = std::round(avgTA / n * 100.0) / 100.0;
        avgWait = std::round(avgWait / n * 100.0) / 100.0;
        avgResp = std::round(avgResp / n * 100.0) / 100.0;
    }
}

void printMetrics(const std::vector<Process> &procs,
                  const std::vector<Metrics> &metrics,
                  double avgTA,
                  double avgWait,
                  double avgResp) {
    std::cout << "The turnaround times, wait times and response times will be:\n";
    std::cout << std::left
              << std::setw(8) << "Process"
              << std::setw(12) << "TA Time"
              << std::setw(12) << "Wait Time"
              << "Response Time\n\n";

    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < procs.size(); ++i) {
        std::cout << std::setw(8) << procs[i].id
                  << std::setw(12) << metrics[i].turnaround
                  << std::setw(12) << metrics[i].wait
                  << metrics[i].response
                  << "\n";
    }

    std::cout << "\n"
              << std::setw(8) << "Avg"
              << std::setw(12) << avgTA
              << std::setw(12) << avgWait
              << avgResp
              << "\n\n";
}