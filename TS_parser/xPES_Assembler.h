#pragma once
#include "tsCommon.h"
#include "xPES_PacketHeader.h"
#include "tsTransportStream.h"
#include "xTS_AdaptationField.h"
#include <fstream>

class xPES_Assembler {
 public:
  enum class eResult : int32_t {
    UnexpectedPID = 1,
    StreamPackedLost,
    AssemblingStarted,
    AssemblingContinue,
    AssemblingFinished,
  };

 protected:
  // setup
  int32_t m_PID;
  // buffer
  uint8_t* m_Buffer;
  uint32_t m_BufferSize;
  uint32_t m_DataOffset;
  // operation
  int8_t m_LastContinuityCounter;
  bool m_Started;
  xPES_PacketHeader m_PESH;

 public:
  xPES_Assembler()  = default;
  ~xPES_Assembler() = default;
  void Init(int32_t PID);
  eResult AbsorbPacket(/*const*/ uint8_t* TransportStreamPacket,
                       const xTS_PacketHeader* PacketHeader,
                       const xTS_AdaptationField* AdaptationField);
  void PrintPESH() const { m_PESH.Print(); }
  uint8_t* getPacket() { return m_Buffer; }
  int32_t getNumPacketBytes() const { return m_DataOffset; }

 protected:
  void xBufferReset();
  void xBufferAppend( uint8_t* Data, int32_t Size);
};