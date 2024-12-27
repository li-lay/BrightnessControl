#include "menu.h"
#include "monitor.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  Menu();
  std::vector<std::string> monitors;
  std::string brightness;
  int selectedMonitor = 0;

  try {
    monitors = detectMonitors();
    for (unsigned int i = 0; i < monitors.size(); i++) {
      std::cout << (i + 1) << ". " << monitors[i] << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  try {
    brightness = getCurrentMonitorBrightness(monitors[0]);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  int currentBrightness = std::stod(brightness) * 100;

  std::cout << "0. Exit\n";
  std::cout << "Choose your monitor: ";
  std::cin >> selectedMonitor;

  if (selectedMonitor == 0) {
    std::cout << "Exiting...\n";
    return 0;
  } else if (selectedMonitor > 0 && selectedMonitor <= monitors.size()) {
    int newBrightness;
    std::cout << "\nSelected monitor: " << monitors[selectedMonitor - 1]
              << std::endl;
    std::cout << "Current brightness for " << monitors[selectedMonitor - 1]
              << ": " << currentBrightness << "%\n";
    std::cout << "\nEnter new brightness (10-100): ";
    std::cin >> newBrightness;
    setBrightness(monitors[selectedMonitor - 1], newBrightness);
  } else {
    std::cout << "Invalid selection\n";
  }

  return 0;
}
