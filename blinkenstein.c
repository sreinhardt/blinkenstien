// actual C
// #include <stdint.h>
// #include <stdio.h>
// s/Serial.print(|ln)/printf/; s/delay/\/\/delay/; s/Serial/\/\/Serial/; s/pinMode/\/\/pinMode/;

// written for esp8266

typedef enum {
  End = 0,
  Dot = 1,
  Dash = 2,
} Signal;
#define sig_len 6
uint16_t dot_sleep = 200;
uint16_t dash_sleep = 500;
uint16_t char_sleep = 1000;

typedef struct {
  char letter;
  Signal sig[sig_len];
} Char;

// https://morsecode.scphillips.com/morse2.html
Char lookup_table[] = {
  { 'A', {Dot, Dash, End, End, End, End} },            // .-
  { 'B', {Dash, Dot, Dot, Dot, End, End} },            // -...
  { 'C', {Dash, Dash, Dot, Dash, End, End} },          // -.-.
  { 'D', {Dash, Dot, Dot, End, End, End} },            // -..
  { 'E', {Dot, End, End, End, End, End} },             // .
  { 'F', {Dot, Dot, Dash, Dot, End, End} },            // ..-.
  { 'G', {Dash, Dash, Dot, End, End, End} },           // --.
  { 'H', {Dot, Dot, Dot, Dot, End, End} },             // ....
  { 'I', {Dot, Dot, End, End, End, End} },             // ..
  { 'J', {Dot, Dash, Dash, Dash, End, End} },          // .---
  { 'K', {Dash, Dot, Dash, End, End, End} },           // -.-
  { 'L', {Dot, Dash, Dot, Dot, End, End} },            // .-..
  { 'M', {Dash, Dash, End, End, End, End} },           // --
  { 'N', {Dash, Dot, End, End, End, End} },            // -.
  { 'O', {Dash, Dash, Dash, End, End, End} },          // ---
  { 'P', {Dot, Dash, Dash, Dot, End, End} },           // .--.
  { 'Q', {Dash, Dash, Dot, Dash, End, End} },          // --.-
  { 'R', {Dot, Dash, Dot, End, End, End} },            // .-.
  { 'S', {Dot, Dot, Dot, End, End, End} },             // ...
  { 'T', {Dash, End, End, End, End, End} },            // -
  { 'U', {Dot, Dot, Dash, End, End, End} },            // ..-
  { 'V', {Dot, Dot, Dot, Dash, End, End} },            // ...-
  { 'W', {Dot, Dash, Dash, End, End, End} },           // .--
  { 'X', {Dash, Dot, Dot, Dash, End, End} },           // -..-
  { 'Y', {Dash, Dot, Dash, Dash, End, End} },          // -.--
  { 'Z', {Dash, Dash, Dot, Dot, End, End} },           // --..
  // numbers
  { '0', {Dash, Dash, Dash, Dash, Dash, End} },        // -----
  { '1', {Dot, Dash, Dash, Dash, Dash, End} },         // .----
  { '2', {Dot, Dot, Dash, Dash, Dash, End} },          // ..---
  { '3', {Dot, Dot, Dot, Dash, Dash, End} },           // ...--
  { '4', {Dot, Dot, Dot, Dot, Dash, End} },            // ....-
  { '5', {Dot, Dot, Dot, Dot, Dot, End} },             // .....
  { '6', {Dash, Dot, Dot, Dot, Dot, End} },            // -....
  { '7', {Dash, Dash, Dot, Dot, Dot, End} },           // --...
  { '8', {Dash, Dash, Dash, Dot, Dot, End} },          // ---..
  { '9', {Dash, Dash, Dash, Dash, Dot, End} },         // ----.
  // symbols
  { '.', {Dot, Dash, Dot, Dash, Dot, Dash} },          // .-.-.-
  { ',', {Dash, Dash, Dot, Dot, Dash, Dash} },         // --..--
  { ':', {Dash, Dash, Dash, Dot, Dot, Dot} },          // ---...
  { '?', {Dot, Dot, Dash, Dash, Dot, Dot} },           // ..--..
  { '\'', {Dot, Dash, Dash, Dash, Dash, Dot} },        // .----.
  { '-', {Dash, Dot, Dot, Dot, Dot, Dash} },           // -....-
  { '/', {Dash, Dot, Dot, Dash, Dot, End} },           // -..-.
  { '{', {Dash, Dot, Dash, Dash, Dot, Dash} },         // -.--.-
  { '}', {Dash, Dot, Dash, Dash, Dot, Dash} },         // -.--.-
  { '"', {Dot, Dash, Dot, Dot, Dash, Dot} },           // .-..-.
  { '@', {Dot, Dash, Dash, Dot, Dash, Dot} },          // .--.-.
  { '=', {Dash, Dot, Dot, Dot, Dash, End} },           // -...-
};

uint8_t flag[] = {0x76, 0x46, 0x4, 0x5d, 0x9, 0x4c, 0xf, 0x5b,
                  0x1d, 0x66, 0x59, 0x10, 0x43, 0x6e, 0x3a, 0x72,
                  0x33, 0x67, 0x4a, 0xe, 0x4f, 0x1b, 0x5a, 0x77,
                  0x3e, 0x13, 0x40, 0x5, 0x40, 0x7f, 0x2};

uint8_t key = 0x42;
uint8_t prev = 0x00;
//const short int LED = LED_BUILTIN; // ESP-01
//const short int LED = 1;           // ESP12E (some)
const short int LED = 2;             // ESP12F

char decrypt(uint8_t f) {
  uint8_t result = prev ^ f;
  prev = f;
  return (char) result;
}

void blink_char(char c) {
  int len = sizeof(lookup_table);
  for (uint8_t i=0; i < len; ++i) {         // loop lookup for char match
    Char C = lookup_table[i];
    if (c == C.letter) {                    // found correct letter
      for (uint8_t x=0; x < sig_len; ++x) { // loop dot/dash for appropriate blinks
        switch( C.sig[x] ){
          case End: break;                  // no signal on end
          case Dot:
            digitalWrite(LED, LOW);         // turn on
            delay(dot_sleep);               // leave on for dot
            break;
          case Dash:
            digitalWrite(LED, LOW);         // turn on
            delay(dash_sleep);              // leave on for dash
            break;
        } // switch
        digitalWrite(LED, HIGH);            // turn off after char
      } // inner for
      break;                                // exit outer for
    } // if
  } // outer for
}



void setup() {
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  prev = key;
  digitalWrite(LED, HIGH);        // start off
  for (uint8_t i=0; i < sizeof(flag); ++i) {
    uint8_t fc = flag[i];         // grab encoded char
    char dc = decrypt(fc);        // decode to real value
    blink_char(dc);               // appropriately blink
    delay(char_sleep);            //
  }
}
