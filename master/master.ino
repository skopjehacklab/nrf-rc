#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

//uint8_t states[5] = {1,2,3,4,5};
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
    
  while (Serial.available()) {
    states[0] = Serial.parseInt();
    printf("Now sending...");

    bool ok = radio.write( states, states_size );
  if (ok)
    printf("ok\n\r");
  else
    printf("failed\n\r");
  // Try again in a short while
  
  delay(20);
  }
}
// vim:ai:cin:sts=2 sw=2 ft=cpp

