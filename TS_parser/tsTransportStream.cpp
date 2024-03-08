#include "tsTransportStream.h"

//=============================================================================================================================================================================
// xTS_PacketHeader
//=============================================================================================================================================================================
void xTS_PacketHeader::Reset() {}

int32_t xTS_PacketHeader::Parse(const uint8_t* Input) {
  uint32_t Tmp = *((uint32_t*)Input);
  Tmp = xSwapBytes32(Tmp);

  // std::cout << Tmp << std::endl;

  uint32_t masks[8] = {
      0b11111111000000000000000000000000, 0b00000000100000000000000000000000,
      0b00000000010000000000000000000000, 0b00000000001000000000000000000000,
      0b00000000000111111111111100000000, 0b00000000000000000000000011000000,
      0b00000000000000000000000000110000, 0b00000000000000000000000000001111};
  uint32_t SB = Tmp & masks[0];
  SB = SB >> 24;
  uint32_t E = Tmp & masks[1];
  E = E >> 23;
  uint32_t S = Tmp & masks[2];
  S = S >> 22;
  uint32_t T = Tmp & masks[3];
  T = T >> 21;
  uint32_t PID = Tmp & masks[4];
  PID = PID >> 8;
  uint32_t TSC = Tmp & masks[5];
  TSC = TSC >> 6;
  uint32_t AFC = Tmp & masks[6];
  AFC = AFC >> 4;
  uint32_t CC = Tmp & masks[7];


  parsedHeader[0] = SB;
  parsedHeader[1] = E;
  parsedHeader[2] = S;
  parsedHeader[3] = T;
  parsedHeader[4] = PID;
  parsedHeader[5] = TSC;
  parsedHeader[6] = AFC;
  parsedHeader[7] = CC;

  return 0;
}


void xTS_PacketHeader::Print() const {
    std::cout << "TS: SB=" << parsedHeader[0] << " E=" << parsedHeader[1]
              << " S=" << parsedHeader[2] << " T=" << parsedHeader[3]
              << " PID=" << parsedHeader[4] << " TSC=" << parsedHeader[5]
              << " AFC=" << parsedHeader[6] << " CC=" << parsedHeader[7];
}


//=============================================================================================================================================================================