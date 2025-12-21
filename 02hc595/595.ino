// Modified from https://github.com/beneater/eeprom-programmer?tab=readme-ov-file
#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define ST_CLK 4


void invoke_store_clock() {
  digitalWrite(ST_CLK, LOW);
  digitalWrite(ST_CLK, HIGH);
  digitalWrite(ST_CLK, LOW);
}

void put_shift_data(int data) {
    // 0b1111000000001111
    shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, data >> 8); // 11110000
    shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, data); // 000001111
    invoke_store_clock();
}

// void set_address(int address) {

//   // 0b11100011100 -> 0b0000011100011100
//   put_shift_data(address);
// }

void set_address_for_read(int address) {
  // 0b11100011100 -> 0b0000011100011100 -> 0b0000011100011100
  put_shift_data(address);
}

void set_address_for_write(int address) {
  // 0b11100011100 -> 0b0000011100011100 -> 0b1000011100011100
  // output disable (active low), 1
  address = address | 0x8000;
  // 0b0000011100011100 | 0b1000000000000000
  put_shift_data(address);
}

void setup() {
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(ST_CLK, OUTPUT);
  
  set_address_for_write(0b11100011100); // A10 - A0, output disable
  set_address_for_read(0b11100011100); // A10 - A0, output enbale
  
}

void loop() {

}
