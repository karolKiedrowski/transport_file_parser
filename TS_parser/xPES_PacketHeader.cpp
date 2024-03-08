#include "xPES_PacketHeader.h"

int32_t xPES_PacketHeader::Parse(const uint8_t* Input, uint16_t AF_lenght) {
  //counter = 6;
  uint32_t Pes;
    Pes = *((uint32_t*)(Input + 6 + (AF_lenght / 8)));

  Pes = xSwapBytes32(Pes);
  uint16_t Pes_len = *((uint16_t*)(Input + 10 + (AF_lenght / 8)));
  Pes_len = xSwapBytes16(Pes_len);
  uint32_t masks[2] = {0b11111111111111111111111100000000,
                       0b00000000000000000000000011111111};

  m_PacketStartCodePrefix = Pes & masks[0];
  m_PacketStartCodePrefix = m_PacketStartCodePrefix >> 8;

  m_StreamId = Pes & masks[1];

  m_PacketLength = Pes_len;

  m_HeaderDataLenght = 6;

  if (m_StreamId != eStreamId::eStreamId_program_stream_map &&
      m_StreamId != eStreamId::eStreamId_padding_stream &&
      m_StreamId != eStreamId::eStreamId_private_stream_2 &&
      m_StreamId != eStreamId::eStreamId_ECM &&
      m_StreamId != eStreamId::eStreamId_EMM &&
      m_StreamId != eStreamId::eStreamId_program_stream_directory &&
      m_StreamId != eStreamId::eStreamId_DSMCC_stream &&
      m_StreamId != eStreamId::eStreamId_ITUT_H222_1_type_E) {
    m_HeaderDataLenght += 3;
    uint8_t additionalLength = *((uint8_t*)(Input + 6 + (AF_lenght / 8)) + 6 + 3);
    m_HeaderDataLenght += (additionalLength/8) + 1;
    //m_HeaderDataLenght = 9;
  }

  return 0;
}

void xPES_PacketHeader::Print() const {
  std::cout << " PES: PSCP=" << m_PacketStartCodePrefix
            << " SID=" << m_StreamId
            << " L=" << m_PacketLength;
}
