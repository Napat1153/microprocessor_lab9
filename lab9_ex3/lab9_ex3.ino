#include <SPI.h>
bool toggle;
volatile int timer = 3200;
int clock_pin = 13; //SHCP 
int latch_pin = 10; //STCP 
int data_pin = 11; //DS 
int map7seg[10] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};
int i = 1;

void setup(){
  noInterrupts(); 
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = timer;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
}

void loop(){
}

ISR(TIMER_OVF_vect){
  TCNT1 = timer;
  spi_write1(map7seg[i]);
  i++; 
  if(i>9)
    i = 0;
}

void spi_write1(unsigned char cData){
  shiftOut(data_pin, clock_pin, MSBFIRST, cData);
  digitalWrite(latch_pin, HIGH);
  digitalWrite(latch_pin, LOW);
}
