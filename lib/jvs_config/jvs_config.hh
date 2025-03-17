#pragma once
#include <array>
#include <string>
#include <vector>

constexpr int MAX_LEVERS_DIRECTIONS = 4;

struct PlayerConfig {
  std::vector<int> buttons;                 // Individual button pins
  std::array<int, MAX_LEVERS_DIRECTIONS> levers;   // Each lever has 4 directional pins
  int start_button;                         // Start button pin
};

struct JVSConfig {
  std::vector<PlayerConfig> players;
  int test_button;
  int service_button;
};
