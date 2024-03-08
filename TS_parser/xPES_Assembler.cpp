#include "xPES_Assembler.h"

xPES_Assembler::eResult xPES_Assembler::AbsorbPacket(
    /*const*/ uint8_t* TransportStreamPacket,
    const xTS_PacketHeader* PacketHeader,
    const xTS_AdaptationField* AdaptationField) {

  m_DataOffset += 188 - 4 - (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0);
  int32_t size = 188;

    //SPRAWDZENIE, CZY TO POCZATEK SERII
  if (PacketHeader->parsedHeader[2] == 1) {
    m_PESH.Parse(TransportStreamPacket, AdaptationField->getLength());
    m_DataOffset = 0;
    m_DataOffset += 188 - 4 - (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0);
    m_Started = true;

    TransportStreamPacket += 4 + (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0) + m_PESH.getHeaderDataLength();
    size -= (4 + (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0) + m_PESH.getHeaderDataLength());
    xBufferAppend(TransportStreamPacket, size);

    return xPES_Assembler::eResult::AssemblingStarted;
  } 

  //SPR, CZY TO KONTYNUACJA
  else if (m_Started && m_DataOffset > 0 && m_DataOffset < m_PESH.getPacketLength() + 6) {
    TransportStreamPacket += 4 + (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0);
    size -= (4 + (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0));
    xBufferAppend(TransportStreamPacket, size);
    
    return xPES_Assembler::eResult::AssemblingContinue;
  } 

  // SPR, CZY TO KONIEC SERII
  else if (m_Started && m_DataOffset >= m_PESH.getPacketLength() + 6) {
    m_Started = false;

    TransportStreamPacket += 4 + (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0);
    size -= (4 + (PacketHeader->hasAdaptationField()? AdaptationField->getLength() : 0));
    xBufferAppend(TransportStreamPacket, size);
    
    return xPES_Assembler::eResult::AssemblingFinished;
  }

   else
    return xPES_Assembler::eResult::StreamPackedLost;
}

void xPES_Assembler::xBufferAppend(uint8_t* Data, int32_t Size) {
  std::string fileName = "PID136.mp2";
  std::ofstream mp2File;
  mp2File.open(fileName, std::ios::binary | std::ios::app);
  if (!mp2File) {
    std::cout << "File creation failed\n";
    return;
  } 
  mp2File.write(reinterpret_cast<char*>(Data), Size);
  mp2File.close();
}