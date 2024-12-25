#include "monitor.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> detectMonitors() {
  std::vector<std::string> connectedMonitor;
  const char *command = "xrandr";

  // Open a pipe to the command
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read the output of the command
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  // Process the output to find connected monitors
  std::istringstream output_stream(result);
  std::string line;
  while (std::getline(output_stream, line)) {
    if (line.find(" connected") != std::string::npos) {
      // Extract the monitor name (the first word in the line)
      std::istringstream line_stream(line);
      std::string monitorName;
      line_stream >> monitorName;
      connectedMonitor.push_back(monitorName);
    }
  }

  return connectedMonitor;
}

std::string getCurrentMonitorBrightness(const std::string &monitor) {
  const std::string command = "xrandr --verbose";
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);

  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read the output of the command
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  // Process the output to find the brightness for the specified monitor
  std::istringstream output_stream(result);
  std::string line;
  bool monitor_found = false;

  while (std::getline(output_stream, line)) {
    if (line.find(monitor + " connected") != std::string::npos) {
      monitor_found = true; // Monitor is found
    } else if (monitor_found && line.empty()) {
      // Stop processing if we hit an empty line after the monitor section
      break;
    }

    if (monitor_found && line.find("Brightness:") != std::string::npos) {
      // Extract the brightness value
      std::istringstream line_stream(line);
      std::string brightness_label;
      double brightness_value;
      line_stream >> brightness_label >> brightness_value;
      return std::to_string(brightness_value); // Return brightness as string
    }
  }

  return "Brightness not found"; // Return a message if brightness is not found
}

int setBrightness(const std::string &monitor, const int &newBrightness) {
  if (newBrightness >= 10 && newBrightness <= 100) {
    double setBrightnessValue = newBrightness / 100.0;
    std::string command = "xrandr --output " + monitor + " --brightness " +
                          std::to_string(setBrightnessValue);
    /*std::cout << command << std::endl;*/
    system(command.c_str());
    std::cout << "\nBrightness set to " << newBrightness << "%.\n";
    std::cout << "Bye...\n";
    return 0;
  } else {
    std::cout << "\nInvalid brightness value! Should be [10 - 100].";
    return -1;
  }
}
