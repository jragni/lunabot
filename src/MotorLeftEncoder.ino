#define ENC_A 2
#define ENC_B 3

int count = 0;

void readEncoder() {
  int b = digitalRead(ENC_B);
  if (b > 0) {
    count++;
  } else {
    count--;
  }
}

void setup() {
  // Initialize left motor pins
  Serial.begin(115200);
  // Initialize encoder pins
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENC_A), readEncoder, RISING);

}

void loop() {
  Serial.println(count);
}

