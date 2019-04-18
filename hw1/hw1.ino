
const int OUTPUT_LED_PIN1 = 11;
const int OUTPUT_LED_PIN2 = 10;
const int OUTPUT_LED_PIN3 = 9;

const int BUTTON_INPUT_PIN = A2;
const int PHOTON_INPUT_PIN = A0;


long timer = 0;

// For the demo
const int TARGET = 10000;
const int AFTER_TIME = 13000;
const int BEFORE_TIME = 7000;

//// For the Younghoon's sleep time
//const long TARGET = 8 * 3600 * 1000;
//const long AFTER_TIME = 7.75 * 3600 * 1000;
//const long BEFORE_TIME = 8.25 * 3600 * 1000;

boolean isStable= true;
int lastButtonVal = -1;

void setup() {
  pinMode(OUTPUT_LED_PIN1, OUTPUT);
  pinMode(OUTPUT_LED_PIN2, OUTPUT);
  pinMode(OUTPUT_LED_PIN3, OUTPUT);
  pinMode(PHOTON_INPUT_PIN , INPUT);
  pinMode(BUTTON_INPUT_PIN , INPUT);


  Serial.begin(9600);
}

void loop() {
  int photon = analogRead(PHOTON_INPUT_PIN);
  int currButtonVal = analogRead(BUTTON_INPUT_PIN);
  float leadVal = min(max((photon - 500.0)*1.0/(1024-500), 0.2), 1);

//  Serial.print(currButtonVal);
//  Serial.print(",");
  Serial.println(leadVal);


  if (lastButtonVal < 0){
    lastButtonVal = currButtonVal;
  }



  if (isStable) {
    // Check if it's unstable now
    if (abs(currButtonVal - lastButtonVal) > 6) {
      isStable = false;
      // Reset the timer
      timer = 0;
    }

  } else {
    if (abs(currButtonVal - lastButtonVal) <= 6) {
      isStable = true;

    }
  }
  // De-noise
  lastButtonVal = (lastButtonVal + currButtonVal) / 2;

  // 0:bright
  analogWrite(OUTPUT_LED_PIN1, 255-(255-red(timer))*leadVal); //red
  analogWrite(OUTPUT_LED_PIN2, 255-(255-green(timer))*leadVal); //green
  analogWrite(OUTPUT_LED_PIN3, 255-(255-blue(timer))*leadVal); //blue
  delay(100);

  // Prevent that the timer overflows;
  if (timer <= AFTER_TIME) {
    timer += 100;
  }

}


// timer : ~ BEFORE_TIME : blue
// timer : TARGET - 500ms ~ TARGET : turn off
// timer : BEFORE_TIME ~ AFTER_TIME : green
// timer : AFTER_TIME ~  : red
int blue(long timer) {
  if (timer < BEFORE_TIME){
    return 0;
  } else if (timer >= TARGET - 500 && timer < TARGET) {
    return 255;
  } else if (timer >= BEFORE_TIME && timer < AFTER_TIME) {
    return 255;
  }  else {
    return 255;
  }
}

int red(long timer) {
  if (timer < BEFORE_TIME){
    return 255;
  } else if (timer >= TARGET - 500 && timer < TARGET) {
    return 255;
  } else if (timer >= BEFORE_TIME && timer < AFTER_TIME) {
    return 255;
  }  else {
    return 0;
  }
}
int green(long timer) {
  if (timer < BEFORE_TIME){
    return 255;
  } else if (timer >= TARGET - 500 && timer < TARGET) {
    return 255;
  } else if (timer >= BEFORE_TIME && timer < AFTER_TIME) {
    return 0;
  }  else {
    return 255;
  }
}
