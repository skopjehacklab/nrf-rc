#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


String input;

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

// This is the TX pipe. The slaves will listen on a address which is with an offset of 'address' to this one
const uint64_t pipe = 0xE8E8F0F0E1LL;

int state = 0;
uint8_t state_size = sizeof(state);

void setup(void) {
  Serial.begin(9600);
  printf_begin();

  radio.begin();
  radio.openWritingPipe(pipe);
  printf("Booting up ....\n\r");
  radio.printDetails();
  printf("\n\rBooted!\n\r");
  printf("Syntax : '_addr_ _state_'\n\n\r");
}

void loop(void) {
  uint8_t address;
  char cmd[10];
  char c;


  while ( Serial.available() ) {
    c = Serial.read();
    if ( c != '\r' ) {
      input += c;
    } else {
      input.toCharArray(cmd,10);
      byte okparse = sscanf(cmd, "%hhd %hhd", &address, &state);
      //printf("%d", state);

      if (okparse == 2 ) {
        radio.openWritingPipe(pipe+(uint64_t)address);

        //radio.printDetails();

        printf("Now sending...\n\r");
        printf("Address : %hhd \n\rState : %hhd\n\r", address, state);
        bool okwrite = radio.write( &state, state_size );

        if (okwrite)
          printf("OK\n\r");
        else
          printf("Failed\n\r");
      }
      input = "";
    }
    delay(20);
  }

}
// vim:ai:cin:sts=2 sw=2 ft=cpp

