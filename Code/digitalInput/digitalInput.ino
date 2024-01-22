/* Pinout Definition */
#define DI_1 A0
#define DI_2 A1
#define DI_3 A2
#define DI_4 A3
#define DI_5 8
#define DI_6 9
#define DI_7 A5
#define DI_8 A4

uint8_t DI_state = 0;
unsigned long milliSecond = 0 ;
unsigned long last_change = 0;
unsigned long now = 0;
uint16_t bf1s = 0 ;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");

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
  }

  if(1 == digitalRead(DI_2))
  {
    DI_state |= 0x02;
  }

  if(1 == digitalRead(DI_3))
  {
    DI_state |= 0x04;
  }

  if(1 == digitalRead(DI_4))
  {
    DI_state |= 0x08;
  }

  if(1 == digitalRead(DI_5))
  {
    DI_state |= 0x10;
  }


  if(1 == digitalRead(DI_6))
  {
    DI_state |= 0x20;
  }


  if(1 == digitalRead(DI_7))
  {
    DI_state |= 0x40;
  }

  if(1 == digitalRead(DI_8))
  {
    DI_state |= 0x80;
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
      Serial.print((DI_state >>(i-1)) & 1 == 1 ? "1" : "0"); // will reverse bit order!
    }
    Serial.println();
  }
}

