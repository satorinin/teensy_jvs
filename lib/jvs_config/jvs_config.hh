#pragma once
#include <array>
#include <string>
#include <vector>

constexpr int MAX_LEVERS = 4;

struct PlayerConfig {
  std::vector<int> buttons;                 // Individual button pins
  std::vector<std::array<int, MAX_LEVERS>> levers;   // Each lever has 4 directional pins
  int start_button;                         // Start button pin
  std::vector<std::array<int, 2>> analogs;  // Each analog has X,Y pins
};

struct JVSConfig {
  std::vector<PlayerConfig> players;
  int test_button;
  int service_button;

  static JVSConfig load_from_file(const std::string& filepath);
};
