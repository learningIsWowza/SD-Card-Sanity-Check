/*
 * SD Card sanity check
 */

#include "time.h"

/* Here we declare pointer resetFunc to a
 * function that returns 0,
 * this tricks our reset vector to point at address 0x0
 * and forces the Active LO RESET pin on uProccesor LOW
 * Crude af but fastest way to resest thru software.           
 */
void(* resetFunc) (void) = 0;

File MY_FILE;

void setup() {
  Serial.begin(9600);
  pinMode(SD_CS, OUTPUT);
  SPI.begin();

  if(SD.begin(SD_CS)){
    Serial.println("SD card intialized...");
  }
  else{
    Serial.println("SD card intialization failed...");
    Serial.println("Resetting in 1 second");
    delay(800);
    resetFunc();
  }
}

void CreateFile(char* f){
  MY_FILE = SD.open(f, FILE_WRITE);
  MY_FILE.write(HEADER);
}

void WriteToFile(char* f, char* message){
  MY_FILE = SD.open(f, FILE_WRITE);
  MY_FILE.println(message);
  MY_FILE.close();
}

void ReadFromFile(char* f){
  MY_FILE = SD.open(f);
  if(MY_FILE){
    Serial.println("Data from: " +String(f));
    while(MY_FILE.available()){
      Serial.print(MY_FILE.read());
    }
    MY_FILE.close();
  }else{
    Serial.println("Error opening " + String(f)); 
  }  
}

void loop() {    
  if(MY_FILE){
    WriteToFile(FILE_NAME, "Testing");
  }
  else{
    CreateFile(FILE_NAME);
  }  
  // Delays are cancer but for testing purposes this is OK
  delay(500);
  ReadFromFile(FILE_NAME);
  delay(3000);
}
