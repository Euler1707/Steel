// ########################### STEPPING PARAMETERS #############################


int delay_on = 7000 ;
int step_mult_on = 2.5 ;
int speed_on = 15000 ;

int delay_cl = 3000 ;
int step_mult_cl = 1.75;
int speed_cl = 800 ;

int delay_run = 1000 ;
int step_mult_run = 2.0 ;
int speed_run = 1000 ;

int delay_e_stop_op = 2000 ;
int step_e_stop_op = 3.0 ;
int speed_e_stop_op = 800 ;


int delay_e_stop_cl = 2000 ;
int step_e_stop_cl = 5.0 ;
int speed_e_stop_cl = 800 ;

// ########################### STEPPING PARAMETERS #############################

//%%%%%%%%%%%%%%%%%%%%%% E-STOP VARIABLES %%%%%%%%%%%%%%%%%%%%%%%%%%%

boolean start1 = true;
volatile boolean e_stop = false;

//%%%%%%%%%%%%%%%%%%%%%% END E-STOP VARIABLES %%%%%%%%%%%%%%%%%%%%%%%%


//%%%%%%%%%%%%%%%%%%%%%% MOTOR VARIABLES %%%%%%%%%%%%%%%%%%%%%%%%%%%


unsigned long start, finished, elapsed;

int direccionPin = 2;
int stepsPin = 3;

int reset = 10;
int pasos = 200;

int ledPinRed = 6;
int ledPinGreen = 7;

int button = 4;
int buttonState = 0;
int previousButtonState = 0;

//%%%%%%%%%%%%%%%%%%%%%% END MOTOR VARIABLES %%%%%%%%%%%%%%%%%%%%%%%%%%%

void setup() {
  // put your setup code here, to run once:
  //%%%%%%%%%%%%%%%%%%%%%% E-STOP VOID SETUP %%%%%%%%%%%%%%%%%%%%%%%%%%%
  Serial.begin(9600);
  delay(100);
  attachInterrupt(2, e_stop_ISR, RISING);
  //%%%%%%%%%%%%%%%%%%%%%% END E-STOP VOID SETUP %%%%%%%%%%%%%%%%%%%%%%%%%%%

  //%%%%%%%%%%%%%%%%%%%%%% MOTOR VOID SETUP %%%%%%%%%%%%%%%%%%%%%%%%%%%
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);

  pinMode(button, INPUT); // start button

  pinMode(stepsPin, OUTPUT);
  pinMode(direccionPin, OUTPUT);

  pinMode(reset, OUTPUT);

  Serial.println("Press 1 for Start/reset, 2 for elapsed time");

  delay(delay_on);

  //digitalWrite(reset, LOW); // When reset is in LOW the motor will not run.
  digitalWrite(reset, HIGH); // When reset is in HIGH the motor will run.
  digitalWrite(direccionPin, LOW); // This will set the motor direction

  //THIS MOTION OPENS THE VALVE FROM THE START

  for (int i = 0; i < pasos * step_mult_on ; i++) // This dictates the the number or turns
  {
    digitalWrite(stepsPin, HIGH); // This LOW to HIGH change is what
    digitalWrite(stepsPin, LOW); // makes the motor to turn after each pulse.

    // The following function sets the speed at which the LOW to HIGH change occurs
    // Dictaring the rotational speed.
    delayMicroseconds(speed_on);
  }

  //%%%%%%%%%%%%%%%%%%%%%% END MOTOR VOID SETUP %%%%%%%%%%%%%%%%%%%%%%%%%%%
}

void displayResult()
{
  float h, m, s, ms;
  unsigned long over;
  elapsed = finished - start;
  h = int(elapsed / 3600000);
  over = elapsed % 3600000;
  m = int(over / 60000);
  over = over % 60000;
  s = int(over / 1000);
  ms = over % 1000;
  Serial.print("Raw elapsed time: ");
  Serial.println(elapsed);
  Serial.print("Elapsed time: ");
  Serial.print(h, 0);
  Serial.print("h ");
  Serial.print(m, 0);
  Serial.print("m ");
  Serial.print(s, 0);
  Serial.print("s ");
  Serial.print(ms, 0);
  Serial.println("ms");
  Serial.println();
}


void loop() {

  if (start1 == true) {

    if (e_stop == false) {
      //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

      buttonState = digitalRead(button);

      if (buttonState == HIGH) {
        digitalWrite(ledPinRed, HIGH);
        digitalWrite(ledPinGreen, LOW);
      }

      else {
        digitalWrite(ledPinRed, LOW);
        digitalWrite(ledPinGreen, HIGH);
      }

      if (digitalRead(button) == HIGH)
      {
        start = millis();
        delay(0); // for debounce
        Serial.println("Started...");
      }

      if (digitalRead(button) == LOW)
      {
        finished = millis();
        delay(0); // for debounce
        displayResult();
      }

      if (elapsed <= 12000) {

        if (buttonState != previousButtonState) {

          // State change interrups...

          if ( buttonState == 1) {
            delay(delay_cl);
            digitalWrite(reset, LOW); // When reset is in LOW the motor will not run.
            digitalWrite(reset, HIGH); // When reset is in HIGH the motor will run.
            digitalWrite(direccionPin, HIGH); // This will set the motor direction

            for (int i = 0; i < pasos * step_mult_cl ; i++) // This dictates the the number or turns
            {
              digitalWrite(stepsPin, HIGH); // This LOW to HIGH change is what
              digitalWrite(stepsPin, LOW); // makes the motor to turn after each pulse.

              // The following function sets the speed at which the LOW to HIGH change occurs
              // Dictaring the rotational speed.
              delayMicroseconds(speed_cl);
            }
          }

          else {
            delay(delay_run);
            digitalWrite(reset, LOW); // When reset is in LOW the motor will not run.
            digitalWrite(reset, HIGH); // When reset is in HIGH the motor will run.
            digitalWrite(direccionPin, LOW); // This will set the motor direction

            for (int i = 0; i < pasos * step_mult_run ; i++) // This dictates the the number or turns
            {
              digitalWrite(stepsPin, HIGH); // This LOW to HIGH change is what
              digitalWrite(stepsPin, LOW); // makes the motor to turn after each pulse.

              // The following function sets the speed at which the LOW to HIGH change occurs
              // Dictaring the rotational speed.
              delayMicroseconds(speed_run);
            }
          }
        }

        previousButtonState = buttonState;

      }

      //###########################################################################
      Serial.println("all is well with the world...");
      delay(300);
    }

    else {

      Serial.println("Emergency Stop!!");
      Serial.println("This is a Joke!!!");

      Serial.println("You have finished the workout, please exit");

      delay(delay_e_stop_op);

      digitalWrite(reset, LOW); // When reset is in LOW the motor will not run.
      digitalWrite(reset, HIGH); // When reset is in HIGH the motor will run.
      digitalWrite(direccionPin, LOW); // This will set the motor direction

      for (int i = 0; i < pasos * step_e_stop_op ; i++) // This dictates the the number or turns
      {
        digitalWrite(stepsPin, HIGH); // This LOW to HIGH change is what
        digitalWrite(stepsPin, LOW); // makes the motor to turn after each pulse.

        // The following function sets the speed at which the LOW to HIGH change occurs
        // Dictaring the rotational speed.
        delayMicroseconds(speed_e_stop_op);
      }

      delay(delay_e_stop_cl);

      digitalWrite(reset, LOW); // When reset is in LOW the motor will not run.
      digitalWrite(reset, HIGH); // When reset is in HIGH the motor will run.
      digitalWrite(direccionPin, HIGH); // This will set the motor direction

      for (int i = 0; i < pasos * step_e_stop_cl ; i++) // This dictates the the number or turns
      {
        digitalWrite(stepsPin, HIGH); // This LOW to HIGH change is what
        digitalWrite(stepsPin, LOW); // makes the motor to turn after each pulse.

        // The following function sets the speed at which the LOW to HIGH change occurs
        // Dictaring the rotational speed.
        delayMicroseconds(speed_e_stop_cl);
      }

      start1 = false;
      //for (;;) {}

    }

  }
}

void e_stop_ISR(void) {
  detachInterrupt(2);
  e_stop = !e_stop;
}

