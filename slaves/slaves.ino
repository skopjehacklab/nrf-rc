#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

//
// Payload
//

uint8_t states[1];
uint8_t states_size = sizeof(states);

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

  radio.begin();

  // This simple sketch opens a single pipes for these two nodes to communicate
  // back and forth.  One listens on it, the other talks to it.
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  radio.printDetails();
}

//
// Loop
//

void loop(void)
{
  // if there is data ready
  if ( radio.available() ) {
    // Dump the payloads until we've gotten everything
    bool done = false;
    while (!done) {

      // Fetch the payload, and see if this was the last one.
      done = radio.read( states, states_size );
      
      // Spew it
      printf("%d",states[0]);
    }
    printf("\r\n");
  }
}

// vim:ai:cin:sts=2 sw=2 ft=cpp

