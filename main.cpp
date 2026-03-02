/*
Sophia Herrmann
COP4610
Project 2
*/

#include <iostream>
#include <vector>
#include "Process.hpp"
#include "Scheduler.hpp"

int main(int argc, char *argv[]) {
    std::string filename = "26S_COP4610_Project2_InputFile1.txt";
    if (argc > 1) filename = argv[1];

    double contextSwitch = 0.0, quantum = 0.0;
    std::vector<Process> processes;

    if (!readInput(filename, contextSwitch, quantum, processes)) {
        std::cerr << "Error reading input file.\n";
        return 1;
    }

    printInput(contextSwitch, quantum, processes);

    std::vector<Process> scheduled;
    std::vector<std::pair<double,char>> gantt;
    runRoundRobin(processes, contextSwitch, quantum, scheduled, gantt);
    printGantt(gantt, quantum, contextSwitch);

    std::vector<Metrics> metrics;
    double avgTA, avgWait, avgResp;
    computeMetrics(scheduled, metrics, avgTA, avgWait, avgResp);
    printMetrics(scheduled, metrics, avgTA, avgWait, avgResp);

    std::cout << "---------------------------------------------------------------------\n\n";
    std::cout << "Thanks for using this program, dear Process Manager!\n\n";
    std::cout << "Completed with exit code: 0\n\n";

    return 0;
}