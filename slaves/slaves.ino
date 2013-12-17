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

uint8_t state;
uint8_t state_size = sizeof(state);

void setup(void)
{
  Serial.begin(9600);
  printf_begin();

  radio.begin();

  // This simple sketch opens a single pipes for these two nodes to communicate
  // back and forth.  One listens on it, the other talks to it.
  radio.openReadingPipe(1,pipe+3);
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
      done = radio.read( &state, state_size );
      
      // Spew it
      printf("%d",state);
    }
    printf("\r\n");
  }
}

// vim:ai:cin:sts=2 sw=2 ft=cpp

