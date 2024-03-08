#pragma once
#include <iostream>
#include "tsCommon.h"

class xTS_AdaptationField {
 protected:
  // AF length
  // mandatory fields
  uint16_t parsedAF[9];
 public:
  void Reset();
  int32_t Parse(const uint8_t* Input, uint8_t AdaptationFieldControl);
  void Print() const;

 public:
  // derrived values
  uint32_t getNumBytes() const {}
  uint16_t getLength() const { return parsedAF[0] + 1; }
};