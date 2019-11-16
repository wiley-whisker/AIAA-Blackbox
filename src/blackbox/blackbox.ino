/*
 * This is where the completed blackbox program is to be written.
 */

#include <SPI.h>
#include <SD.h>

// Set the pins used
#define cardSelect 4

File initFile;
File logfile;

String initHeaders = "offset";
String logHeaders = "index, A0";

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

void createInitFile() {
  char filename[15];
  strcpy(filename, "/BLKBOX00.TXT");
  for (uint8_t i = 0; i < 100; i++) {
    filename[7] = '0' + i/10;
    filename[8] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  initFile = SD.open(filename, FILE_WRITE);
  if( ! initFile ) {
    Serial.print("Couldnt create "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to "); 
  Serial.println(filename);
  
}

void createLogFile() {
  char filename[15];
  strcpy(filename, "/BLKBOX00.CSV");
  for (uint8_t i = 0; i < 100; i++) {
    filename[7] = '0' + i/10;
    filename[8] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  logfile = SD.open(filename, FILE_WRITE);
  if( ! logfile ) {
    Serial.print("Couldnt create "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to "); 
  Serial.println(filename);
  
}

// This line is not needed if you have Adafruit SAMD board package 1.6.2+
//   #define Serial SerialUSB

void setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("\r\nAnalog logger test");
  pinMode(13, OUTPUT);


  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }

  Serial.println("Making initFile...");
  createInitFile();
  // Print init data.
  int offset = 0;
  int offset_size = 10;
  for (int ii=0;ii<offset_size;ii++){
    offset += analogRead(A0)-(1023/2);
  }
  offset /= offset_size;
  initFile.println(initHeaders);
  initFile.println(offset);
  initFile.close();
  

  Serial.println("Creating logFile...");
  createLogFile();
  logfile.println(logHeaders);
  logfile.flush();

  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.println("Ready!");
}

uint8_t i=0;
unsigned int index = 0;
void loop() {
  digitalWrite(8, HIGH);
  logfile.print(index); logfile.print(","); logfile.println(analogRead(0));
  logfile.flush();
  Serial.print(index); Serial.print(","); Serial.println(analogRead(0));
  digitalWrite(8, LOW);

  index++;
  delay(100);
}
