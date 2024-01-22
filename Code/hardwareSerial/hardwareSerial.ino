int ByteReceived = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write("Hello World\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  serialRx();
}

void serialRx(){
    while (Serial.available() > 0) {
    ByteReceived = Serial.read();
    // prints the received data on serial monitor
    Serial.print(" Received Serial Data is: ");
    Serial.println((char)ByteReceived);
  }
}