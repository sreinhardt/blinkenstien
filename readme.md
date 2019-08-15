### Blinkenstein
#### Embedded

Beep Beep Beep, Boop Boop Boop, Beep Beep Beep???

Points: 400
Flag: 40BYTECTF{?IS-THAT-DATA-I-SEE?}

#### Solution

Reverse binary for rolling xor, emulate and map blinkys, or burn to esp8266 and watch

#### Building

* Gen flag
  ```
  Generating flag from...
  Flag: b'40BYTECTF{?IS-THAT-DATA-I-SEE?}'
  Key: 66
  Hex encrypt:
  [0x76, 0x46, 0x4, 0x5d, 0x9, 0x4c, 0xf, 0x5b, 0x1d, 0x66, 0x59, 0x10, 0x43, 0x6e, 0x3a, 0x72, 0x33, 0x67, 0x4a, 0xe, 0x4f, 0x1b, 0x5a, 0x77, 0x3e, 0x13, 0x40, 0x5, 0x40, 0x7f, 0x2]
  Encrypted: b'vF\x04]\tL\x0f[\x1dfY\x10Cn:r3gJ\x0eO\x1bZw>\x13@\x05@\x7f\x02'
  Decrypted: b'40BYTECTF{?IS-THAT-DATA-I-SEE?}'
  Hex: [118, 70, 4, 93, 9, 76, 15, 91, 29, 102, 89, 16, 67, 110, 58, 114, 51, 103, 74, 14, 79, 27, 90, 119, 62, 19, 64, 5, 64, 127, 2]
  Decrypted hex: b'40BYTECTF{?IS-THAT-DATA-I-SEE?}'
  ```
* blinkentstein.c -> build.ino
* burn to esp

