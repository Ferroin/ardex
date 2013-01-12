#include <avr/wdt.h>
#include <Wire.h>
#include "config.h"

const int info = 13;
unsigned char state = INIT_STATE;1
int adata, itmp;
unsigned char data, tmp;
volatile unsigned char sinfo = 0;

#ifdef USE_INT0
void int0() {
  sinfo |= 1;
}
#endif // USE_INT0

#ifdef USE_INT1
void int1() {
  sinfo |= 2;
}
#endif // USE_INT1

void i2c_rx(int nBytes) {
  sinfo |= 4;
  tmp = state;
  state = Wire.read();
  if (state > 127) {
    state ^= tmp;
    tmp ^= state;
    state ^= tmp;
    tmp &= 0xF;
    itmp = constrain((int) (tmp & 0x7), 0, 6);
    if ((itmp <= 2) || (itmp == 6)) {
      tmp = (tmp & 0x8) >> 4;
      if (tmp) {
        digitalWrite(itmp + 6, LOW);
      } 
      else {
        digitalWrite(itmp + 6, HIGH);
      }
    } 
    else {
      tmp = Wire.read();
      analogWrite(itmp + 6, tmp);
    }
  }
  for (int i = 0; i < (nBytes - 1); i++) {
    Wire.read();
  }
}

void i2c_tx() {
  Wire.write(sinfo);
  sinfo ^= sinfo;
  Wire.write(state);
  switch (state) {
  case 0x00:
    //A read request when in state 0 transmits a null byte, then does a software reset
    Wire.write(0);
    wdt_enable(WDTO_15MS);
    exit(0);
    break;
  case 0x01:
    break;
#ifdef HRNG_STATE
  case 0x02:
    for (int i = 0; i < 4; i++) {
      tmp = (unsigned char) analogRead(A7);
      data |= (tmp & 2);
      data <<= 2;
    }
    Wire.write(data);
    break;
#endif // HRNG_STATE
#ifdef AR0_STATE
  case 0x10:
    adata = analogRead(A0);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR0_STATE
#ifdef AR1_STATE
  case 0x11:
    adata = analogRead(A1);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR1_STATE
#ifdef AR2_STATE
  case 0x12:
    adata = analogRead(A2);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR2_STATE
#ifdef AR3_STATE
  case 0x13:
    adata = analogRead(A3);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR3_STATE
#ifdef AR4_STATE
  case 0x14:
    adata = analogRead(A4);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR4_STATE
#ifdef AR5_STATE
  case 0x15:
    adata = analogRead(A5);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR5_STATE
#ifdef AR6_STATE
  case 0x16:
    adata = analogRead(A6);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR6_STATE
#ifdef AR7_STATE
  case 0x13:
    adata = analogRead(A7);
    Wire.write((unsigned char) (adata & 0xFF));
    Wire.write((unsigned char) (adata & 0x0F00));
    break;
#endif // AR7_STATE
  }
}

void setup() {
  MCUSR = 0;
  wdt_disable();
  pinMode(info, OUTPUT);
#ifdef USE_INT0
  pinMode(2, INPUT_PULLUP);
#endif // USE_INT0
#ifdef USE_INT1
  pinMode(3, INPUT_PULLUP);
#endif // USE_INT0
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  analogReference(AREF);
  Wire.begin(I2C_ADDR);
  Wire.onRequest(i2c_tx);
  Wire.onReceive(i2c_rx);
#ifdef USE_INT0
  attachInterrupt(0, int0, INT0_TRIG);
#endif // USE_INT0
#ifdef USE_INT1
  attachInterrupt(1, int1, INT1_TRIG);
#endif // USE_INT1
}

void loop() {
  digitalWrite(info, HIGH);
  delay(1000);
  digitalWrite(info, LOW);
  delay(1000);
}
