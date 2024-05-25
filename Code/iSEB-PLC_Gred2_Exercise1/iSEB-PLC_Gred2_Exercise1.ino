/* Control of double acting cylinder with double solenoid valve */
#include <WS2812FX.h>

/* Define the sequence of the LED */
#define DI_1_LED 0

#define DI_2_LED 1
#define DI_3_LED 2
#define DI_4_LED 3
#define DI_5_LED 8
#define DI_6_LED 9
#define DI_7_LED 10
#define DI_8_LED 11
#define DO_1_LED 4
#define DO_2_LED 5
#define DO_3_LED 6
#define DO_4_LED 7

/* Pinout Definition */
#define rgbledPin 11
#define DI_1 A0
#define DI_2 A1
#define DI_3 A2
#define DI_4 A3
#define DI_5 8
#define DI_6 9
#define DI_7 A5
#define DI_8 A4
#define DO_1 12
#define DO_2 6
#define DO_3 5
#define DO_4 4
 
uint8_t DI_state = 0; 
uint8_t DO_State = 0;

unsigned long milliSecond = 0 ;
unsigned long last_change = 0;
unsigned long now = 0;
uint16_t bf1s = 0 ;
uint32_t color[12] = {0x00};

WS2812FX ws2812fx = WS2812FX(12, rgbledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  // put your setup code here, to run once:
  ws2812fx.init();
  ws2812fx.setBrightness(64);
  // segment 1 is our custom effect
  ws2812fx.setCustomMode(myCustomEffect);
  ws2812fx.setSegment(0, 0, 11, FX_MODE_CUSTOM,(uint32_t)0x000000, 50, false);
  ws2812fx.start();
  // initialize the LED pin as an output:
  pinMode(DO_1, OUTPUT);
  pinMode(DO_2, OUTPUT);
  pinMode(DO_3, OUTPUT);
  pinMode(DO_4, OUTPUT);
  setDoutPin(DO_1, LOW); 
  setDoutPin(DO_2, LOW); 
  setDoutPin(DO_3, LOW); 
  setDoutPin(DO_4, LOW); 

  // initialize the pushbutton pin as an input:
  pinMode(DI_1, INPUT);
  pinMode(DI_2, INPUT);
  pinMode(DI_3, INPUT);
  pinMode(DI_4, INPUT);
  pinMode(DI_5, INPUT);
  pinMode(DI_6, INPUT);
  pinMode(DI_7, INPUT);
  pinMode(DI_8, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* update Digital Input pin */
  DI_state = 0;
  if(1 == digitalRead(DI_1))
  {
    DI_state |= 0x01;
    updateLedColor(DI_1_LED,0);
  }
  else
  {
    updateLedColor(DI_1_LED,1);
  }

  if(1 == digitalRead(DI_2))
  {
    DI_state |= 0x02;
    updateLedColor(DI_2_LED,0);
  }
  else
  {
    updateLedColor(DI_2_LED,1);
  }

  if(1 == digitalRead(DI_3))
  {
    DI_state |= 0x04;
    updateLedColor(DI_3_LED,0);
  }
  else
  {
    updateLedColor(DI_3_LED,1);
  }

  if(1 == digitalRead(DI_4))
  {
    DI_state |= 0x08;
    updateLedColor(DI_4_LED,0);
  }
  else
  {
    updateLedColor(DI_4_LED,1);
  }

  if(1 == digitalRead(DI_5))
  {
    DI_state |= 0x10;
    updateLedColor(DI_5_LED,0);
  }
  else
  {
    updateLedColor(DI_5_LED,1);
  }

  if(1 == digitalRead(DI_6))
  {
    DI_state |= 0x20;
    updateLedColor(DI_6_LED,0);
  }
  else
  {
    updateLedColor(DI_6_LED,1);
  }

  if(1 == digitalRead(DI_7))
  {
    DI_state |= 0x40;
    updateLedColor(DI_7_LED,0);
  }
  else
  {
    updateLedColor(DI_7_LED,1);
  }
  if(1 == digitalRead(DI_8))
  {
    DI_state |= 0x80;
    updateLedColor(DI_8_LED,0);
  }
  else
  {
    updateLedColor(DI_8_LED, 1);
  }
  
  now = millis();
  if(milliSecond != millis())
  {
    bf1s++;
    milliSecond = millis();
  }

  /* serial out the current state every 1s */
  if(1000 < bf1s)
  {
    bf1s = 0 ;
    Serial.print("Input:");
    for (int i=8;i!=0;i--)
    {
      Serial.print((DI_state >>(i-1)) & 1 == 1 ? "0" : "1"); // will reverse bit order!
    }
    Serial.println();
    Serial.print("Output:");
    for (int i=4;i!=0;i--)
    {
      Serial.print((DO_State >>(i-1)) & 1 == 1 ? "1" : "0"); // will reverse bit order!
    }
    Serial.println();
  }

  /* PB 1 ON S2 ON -> Y1 ON */
  if(((DI_state&0x01)==0x00)/*&&((DI_state&0x04)==0x04)*/)
  { 
    setDoutPin(DO_1, HIGH); 
    setDoutPin(DO_2, LOW); 
  }
   /* PB 2 ON S3 ON -> Y2 ON */
  else if(((DI_state&0x02)==0x00)/*&&((DI_state&0x08)==0x08)*/)
  {
    setDoutPin(DO_1, LOW); 
    setDoutPin(DO_2, HIGH); 
  }
  
  ws2812fx.service();
}

/* update led every 50ms */
uint16_t myCustomEffect(void) { 
  uint8_t j = 0;
  WS2812FX::Segment* seg = ws2812fx.getSegment(); // get the current segment
  for(uint16_t i=seg->start; i<=seg->stop; i++) {
    ws2812fx.setPixelColor(i, color[j++]);
  }
}

/* Update digital output */
void setDoutPin(uint8_t digitalOutput,uint8_t state){
  switch (digitalOutput)
  {
    case DO_1:
    {
      DO_State = state == 0x01 ? (DO_State|0x01) : (DO_State & ~(0x01)) ;  
      digitalWrite(DO_1, state);
      updateLedColor(DO_1_LED, state);
      break;
    }
    case DO_2:
    {
      DO_State = state == 0x01 ? (DO_State|0x02) : (DO_State & ~(0x02)) ;  
      digitalWrite(DO_2, state);
      updateLedColor(DO_2_LED, state);
      break;
    }
    case DO_3:
    {
      DO_State = state == 0x01 ? (DO_State|0x04) : (DO_State & ~(0x04)) ;  
      digitalWrite(DO_3, state);
      updateLedColor(DO_3_LED, state);
      break;
    }
    case DO_4:
    {
      DO_State = state == 0x01 ? (DO_State|0x08) : (DO_State & ~(0x08)) ;  
      digitalWrite(DO_4, state);
      updateLedColor(DO_4_LED, state);
      break;
    }
  }
}

void updateLedColor(uint8_t led, uint8_t state)
{
  if(0 == state)
  {
    color[led] = 0x00;
  }
  else
  {
    color[led] = 0x00FF0000;
  }
}

