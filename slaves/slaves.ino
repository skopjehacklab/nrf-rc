#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define ADDR_OFFSET 3 // Listeningt address offset


RF24 radio(9,10);

// The base of the listening address. The real one will have an offset of ADDR_OFFSET
const uint64_t pipe = 0xE8E8F0F0E1LL;

uint8_t state;
uint8_t state_size = sizeof(state);

void setup(void) {
  Serial.begin(9600);
  printf_begin();

  printf("Booting up...\n\r");
  radio.begin();

  radio.openReadingPipe(1,pipe+ADDR_OFFSET);
  radio.startListening();

  radio.printDetails();
  printf("Booted !\n\r");
}


void loop(void) {
  // if there is data ready
  if ( radio.available() ) {
    // Dump the payloads until we've gotten everything
    bool done = false;
    while (!done) {

      // Fetch the payload, and see if this was the last one.
      done = radio.read( &state, state_size );
      // Spew it
      printf("Got state : %hhd\n\r", state);
    }
    printf("\r\n");
  }
}

// vim:ai:cin:sts=2 sw=2 ft=cpp

