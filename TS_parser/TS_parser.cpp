// telekom_multim_lab2.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <fstream>
#include "tsCommon.h"
#include "tsTransportStream.h"
#include "xTS_AdaptationField.h"
#include "xPES_Assembler.h"

int main(int argc, char* argv[], char* envp[]) {
  // TODO - open file
#pragma warning(suppress : 4996)
  FILE* file = std::fopen("example_new.ts", "rb");
  if (!file) {
    std::cout << "Nie udalo sie otworzyc pliku";
    delete file;
    return 0;
  }

  /*else
    std::cout << std::endl << "otwarto plik" << std::endl;*/

  xTS_PacketHeader TS_PacketHeader;

  int32_t TS_PacketId = 0;
  uint8_t TS_PacketBuffer[188];
  xPES_Assembler PES_Assembler;
  while (!feof(file)) {
    // TODO - read from file
    int iOdczytanoBajtow = fread(TS_PacketBuffer, 188, 1, file);

    TS_PacketHeader.Reset();
    TS_PacketHeader.Parse(TS_PacketBuffer);
    if (TS_PacketHeader.parsedHeader[4] == 136 && TS_PacketHeader.parsedHeader[0] == 'G') {

      // sprawdzanie pola AF
      xTS_AdaptationField TS_AdaptationField;
      if (TS_PacketHeader.hasAdaptationField()) {
        TS_AdaptationField.Parse(TS_PacketBuffer, TS_PacketHeader.parsedHeader[6]);
        //TS_AdaptationField.Print();
      }

      printf("%010d ", TS_PacketId);
      TS_PacketHeader.Print();
      /*
      if (TS_PacketHeader.hasAdaptationField()) {
        TS_AdaptationField.Print();
      }
      */
      
      xPES_Assembler::eResult Result = PES_Assembler.AbsorbPacket(
          TS_PacketBuffer, &TS_PacketHeader, &TS_AdaptationField);
        switch(Result)
        {
            case xPES_Assembler::eResult::StreamPackedLost : printf(" PcktLost "); break;
            case xPES_Assembler::eResult::AssemblingStarted : printf(" Started "); PES_Assembler.PrintPESH(); break;
            case xPES_Assembler::eResult::AssemblingContinue: printf(" Continue "); /*printf("PES: Len=%d",PES_Assembler.getNumPacketBytes());*/ break;
            case xPES_Assembler::eResult::AssemblingFinished: printf(" Finished "); printf("PES: Len=%d", PES_Assembler.getNumPacketBytes()); break;
            default: break;
        }
      

      printf("\n");
      TS_PacketId++;
    }
  }
  delete file;
  return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file