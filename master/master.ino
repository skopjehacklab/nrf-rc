#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


String input;

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

uint8_t states[] = {1};
uint8_t states_size = sizeof(states);

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

  radio.begin();

  // This simple sketch opens a single pipes for these two nodes to communicate
  // back and forth.  One listens on it, the other talks to it.

  radio.openWritingPipe(pipe);

  radio.printDetails();
}

void loop(void)
{  
  uint8_t address;
  char cmd[10];
  char c;
  
  while ( Serial.available() ) {
    c = Serial.read();
    if ( c != '\r' ) {
      input += c;
    } else {
      input.toCharArray(cmd,10);
      byte okparse = sscanf(cmd, "%d %d", &address, states);

      if (okparse == 2 ) {
        radio.openWritingPipe(pipe+(uint64_t)address);

        radio.printDetails();

        printf("Now sending...");
        bool okwrite = radio.write( states, states_size );
    
        if (okwrite)
          printf("ok\n\r");
        else
          printf("failed\n\r");
      }
      input = "";
    }
    delay(20);
  }

}
// vim:ai:cin:sts=2 sw=2 ft=cpp

