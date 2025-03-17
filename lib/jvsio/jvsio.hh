#pragma once

#include <jvs_config.hh>
#include <jvs_frame.hh>
#include <jvs_serial.hh>
#include <jvs_config.hh>
#include <bitset>

#ifdef _PLATFORM_TEENSY
#include <Arduino.h>
#endif

void setup_io(const JVSConfig&);
void build_io_packet(int player, JVSResponse& response);
void update_analog(uint16_t (&analog_values)[8]);
