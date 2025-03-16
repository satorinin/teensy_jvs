#pragma once
#include <stdint.h>
#include <jvs_serial.hh>

enum JVSStatusCode : uint8_t
{
  NORMAL_STATUS = 1,
  UNKNOWN_COMMAND_STATUS = 2,
  CHECKSUM_ERROR_STATUS = 3,
  ACK_OVERFLOW_STATUS = 4
};

enum JVSReportCode : uint8_t
{
  NORMAL_REPORT = 1,
  PARAM_LEN_ERROR_REPORT = 2,
  PARAM_VALUE_ERROR_REPORT = 3,
  BUSY_ERROR_REPORT = 4
};

enum JVSState
{
  READ_ID,
  READ_LEN,
  READ_DATA,
  READY
};

class JVSFrameReader
{
public:
  JVSFrameReader(JVSSerial::Interface&);

  bool update();
  int addr();
  uint8_t* buffer();
  bool read(uint8_t& val);
  uint32_t size() const;
  void reset();
  uint8_t id() const;

private:
  JVSSerial::Interface& jvsInterface_;
  JVSState state_;
  uint8_t buffer_[256];
  uint32_t cur_len_;
  uint32_t len_;
  uint32_t id_;
  bool escape_{false};
};

class JVSResponse
{
public:
  JVSResponse();

  const uint8_t* serialize(size_t& final_len);
  void append(const uint8_t value);
  void append_u16(const uint16_t value);
  void append(const char* str, const size_t len);
  void append_str(const char* str);

  static constexpr size_t data_offset = 2;
  uint8_t& id;
  uint8_t& len;
  JVSStatusCode& status;

private:
  uint8_t buffer[256];
  uint8_t checksum;
};
