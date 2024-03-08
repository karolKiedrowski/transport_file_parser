#include "xTS_AdaptationField.h"

int32_t xTS_AdaptationField::Parse(const uint8_t* Input,
    uint8_t AdaptationFieldControl) {
  uint16_t Tmp = *((uint16_t*)(Input + 4));
  Tmp = xSwapBytes16(Tmp);
  // std::cout << std::endl << "To jest Tmp: " << Tmp << std::endl;
  uint16_t masks[9] = {
      0b1111111100000000, 0b0000000010000000, 0b0000000001000000,
      0b0000000000100000, 0b0000000000010000, 0b0000000000001000,
      0b0000000000000100, 0b0000000000000010, 0b0000000000000001};

  parsedAF[0] = Tmp & masks[0];
  parsedAF[0] = parsedAF[0] >> 8;

  parsedAF[1] = Tmp & masks[1];
  parsedAF[1] = parsedAF[1] >> 7;

  parsedAF[2] = Tmp & masks[2];
  parsedAF[2] = parsedAF[2] >> 6;

  parsedAF[3] = Tmp & masks[3];
  parsedAF[3] = parsedAF[3] >> 5;

  parsedAF[4] = Tmp & masks[4];
  parsedAF[4] = parsedAF[4] >> 4;

  parsedAF[5] = Tmp & masks[5];
  parsedAF[5] = parsedAF[5] >> 3;

  parsedAF[6] = Tmp & masks[6];
  parsedAF[6] = parsedAF[6] >> 2;

  parsedAF[7] = Tmp & masks[7];
  parsedAF[7] = parsedAF[7] >> 1;

  parsedAF[8] = Tmp & masks[8];
  return 0;
}

void xTS_AdaptationField::Print() const {
  std::cout << "  AF: L= " << parsedAF[0] << " DC=" << parsedAF[1]
            << " RA=" << parsedAF[2] << " SP=" << parsedAF[3]
            << " PR=" << parsedAF[4] << " OR=" << parsedAF[5]
            << " SF=" << parsedAF[6] << " TP=" << parsedAF[7]
            << " EX=" << parsedAF[8];
}