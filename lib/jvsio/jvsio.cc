#include "jvsio.hh"

// int starts[2] = {36, 35};
// int levers[2][4] = {{5, 4, 22, 6}, {31, 30, 32, 23}};
// int buttons[2][8] = {{7, 8, 9, 10, 11, 12, 28, 29}, {21, 20, 19, 18, 40, 39,
// 38, 37}};

JVSIO::JVSIO(JVSParallel::Interface& parallel, const JVSConfig& config)
    : parallel_(parallel), config_(config) {}

void JVSIO::setup_io(const JVSConfig& config) {
  for (const auto& playerConfig : config_.players) {
    // set start button as input
    parallel_.pinMode(playerConfig.start_button, INPUT_PULLUP);
    for (const auto& lever : playerConfig.levers) {
      // set lever pins as input
      parallel_.pinMode(lever, INPUT_PULLUP);
    }
    for (const auto& button : playerConfig.buttons) {
      // set button pins as input
      parallel_.pinMode(button, INPUT_PULLUP);
    }
  }
}

void JVSIO::build_io_packet(int player, JVSResponse& response) {
  std::bitset<32> packet;
  packet.set(7, !parallel_.digitalRead(config_.players[player].start_button));

  for (int i = 0; i < 4; ++i) {
    packet.set(i + 2, !parallel_.digitalRead(config_.players[player].levers[i]));
  }

  bool press_service = true;
  for (int i = 0; i < 6; ++i) {
    press_service = press_service && !parallel_.digitalRead(config_.players[player].buttons[i]);
  }
  packet.set(6, press_service || !parallel_.digitalRead(config_.service_button));

  if (!press_service) {
    packet.set(1, !parallel_.digitalRead(config_.players[player].buttons[0]));
    packet.set(0, !parallel_.digitalRead(config_.players[player].buttons[1]));
    packet.set(15, !parallel_.digitalRead(config_.players[player].buttons[2]));
    packet.set(14, !parallel_.digitalRead(config_.players[player].buttons[3]));
    packet.set(13, !parallel_.digitalRead(config_.players[player].buttons[4]));
    packet.set(12, !parallel_.digitalRead(config_.players[player].buttons[5]));
    packet.set(11, !parallel_.digitalRead(config_.players[player].buttons[6]));
    packet.set(10, !parallel_.digitalRead(config_.players[player].buttons[7]));
  }

  auto val = packet.to_ulong();
  response.append(static_cast<uint8_t>(val & 0xFF));
  val >>= 8;
  response.append(static_cast<uint8_t>(val & 0xFF));
}

void JVSIO::update_analog(uint16_t (&analog_values)[8]) {
  constexpr auto player = 0;
  constexpr auto middle = 0x8000;
  constexpr auto magnitude = 16384;
  analog_values[0] = middle;
  analog_values[1] = middle;

  if (!parallel_.digitalRead(config_.players[player].levers[0])) {
    analog_values[1] += magnitude;
  }
  if (!parallel_.digitalRead(config_.players[player].levers[1])) {
    analog_values[1] -= magnitude;
  }
  if (!parallel_.digitalRead(config_.players[player].levers[2])) {
    analog_values[0] += magnitude;
  }
  if (!parallel_.digitalRead(config_.players[player].levers[3])) {
    analog_values[0] -= magnitude;
  }
}
