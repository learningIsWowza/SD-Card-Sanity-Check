#include "Sodaq_DS3231.h"
#include <SD.h>
#include <SPI.h>

int SD_CS = 10; // chip select for SD card
const char* FILE_NAME = "Temperature_Log.txt";
const char* HEADER    = "SD card logger\n[PLACEHOLDER]";

void CreateFile(char* f);
void ReadFromFile(char* f);
void WriteToFile(char* f, char* message);
