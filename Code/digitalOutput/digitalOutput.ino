/* Pinout Definition */
#define DO_1 12
#define DO_2 6
#define DO_3 5
#define DO_4 4

uint8_t DO_State = 0;

unsigned long milliSecond = 0 ;
unsigned long last_change = 0;
unsigned long now = 0;
uint16_t bf1s = 0 ;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
 
  // initialize the LED pin as an output:
  pinMode(DO_1, OUTPUT);
  pinMode(DO_2, OUTPUT);
  pinMode(DO_3, OUTPUT);
  pinMode(DO_4, OUTPUT);
}

void loop() {
  digitalWrite(DO_1,HIGH);
  digitalWrite(DO_2,HIGH);
  digitalWrite(DO_3,HIGH);
  digitalWrite(DO_4,HIGH);
  delay(1000);
  digitalWrite(DO_1,LOW);
  digitalWrite(DO_2,LOW);
  digitalWrite(DO_3,LOW);
  digitalWrite(DO_4,LOW);
  delay(1000);
}
