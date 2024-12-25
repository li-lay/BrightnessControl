#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>

std::vector<std::string> detectMonitors();
std::string getCurrentMonitorBrightness(const std::string &monitor);
int setBrightness(const std::string &monitor, const int &newBrightness);

#endif // MONITOR_H
