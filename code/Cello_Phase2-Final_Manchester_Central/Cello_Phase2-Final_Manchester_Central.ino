/*
Cello Arm Version 2 24 July 2016

Version used in manchester Central

Stroke length reduced to avoid travel issues



***********************************************************
** ALWAYS RESET ARDUINO BEFORE POWERING UP STEPPER MOTOR **
***********************************************************

Does Forward stroke folled by reverse stroke after graphene trigger
Stroke takes 0.833248 seconds in each direction, total time 1.666667 seconds or once a bar at 144 beats / second tempo
See spreadsheet for exact timing calculations

After forward and reverse stroke checks graphene signal again

    - If closed repeats forward and reverse stroke
    - If open Stops and waits for new ghaphine closure closure
*/

/*

** WIRING DETAILS **

GND - Black wire to microswitch common
GND - Purple wire to Graphene Contact
+5V - Orange wire to stepper controller OPTO
*/
const int direct = 7; // Grey  wire to stepper controller DIR, low = backwards stroke, high  = forward stroke
const int pulse = 4; // White wire to stepper controller PUL (pulse)
const int led13 = 13;
const int microswitch = 2; // Yellow Wire to microswitch N.O.
const int Graphene_Start = 12; // Blue wire to Graphene Contact

int count = 0;
int ramp = 0;
int ramp_delay = 0;
int stroke_time = 250; // Stroke time = 0.85714 seconds adjust to match graphene 140

unsigned long fstart_time;
unsigned long fstop_time;
unsigned long bstart_time;
unsigned long bstop_time;

/* 
Sets up I/O hand uses micro switch to find reference.
*/

void setup() {

  pinMode(led13, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(direct, OUTPUT);
  pinMode(Graphene_Start, INPUT); // Graphene Start Input
  digitalWrite(Graphene_Start, HIGH); // Turn on Pull Up
  pinMode(microswitch, INPUT); // Forward end stop
  digitalWrite(microswitch, HIGH); // Turn on Pull Up
  digitalWrite(direct, LOW); // low = backwards stroke, high  = forward stroke
  
  count = 1;
   digitalWrite(direct, HIGH);
    do { 
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(2500);            // wait for 2.5m seconds
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(2500);           // wait for a 5ms second
        count = digitalRead(microswitch);
    } while (count > 0);
    count = 0;
    digitalWrite(direct, LOW);
    do { 
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(640);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(640);              // wait for a 5ms second
        count ++;
    } while (count <1550);
    delay(2000);
}

// the loop function runs over and over again forever
void loop() {
    do { 
       /*
        Wait For Graphene Start
       */
       } while (digitalRead(Graphene_Start) > 0);

    fstart_time = micros();
//  delay(80);
    forward_stroke();
    fstop_time = micros(); 

    do {       
       /*
        Wait For Graphene Start
       */
       } while (digitalRead(Graphene_Start) > 0);
    bstart_time = micros();   
//  delay(80);
    backward_stroke();
    bstop_time = micros(); 
//  stop_time = micros();    
    
 Serial.begin(9600);
 Serial.print("   Forward Time: "); 
 Serial.println(fstop_time-fstart_time); 
 Serial.print("   Backward Time: "); 
 Serial.println(fstop_time-fstart_time); 
}

void forward_stroke() {
   count = 0;
    digitalWrite(direct, HIGH);
    ramp_delay = 1000+ stroke_time;
  
    for (ramp = 0; ramp <100; ramp ++) {
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(ramp_delay);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(ramp_delay);              // wait for a 5ms second
        ramp_delay = ramp_delay - 10;
        count ++;
    }
    
    do { 
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(stroke_time);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(stroke_time);              // wait for a 5ms second
        count ++;
    } while (count <1150);

    ramp_delay = stroke_time;
    for (ramp = 0; ramp <100; ramp ++) {
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(ramp_delay);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(ramp_delay);              // wait for a 5ms second
        ramp_delay = ramp_delay + 10;
        count ++;
}
}
void backward_stroke() {

   
   count = 0;
    digitalWrite(direct, LOW);
    ramp_delay = 1000 + stroke_time;
  
    for (ramp = 0; ramp <100; ramp ++) {
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(ramp_delay);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(ramp_delay);              // wait for a 5ms second
        ramp_delay = ramp_delay - 10;
        count ++;
    }
    
    do { 
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(stroke_time);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(stroke_time);              // wait for a 5ms second
        count ++;
    } while (count <1150);

    ramp_delay = stroke_time;
    for (ramp = 0; ramp <100; ramp ++) {
        digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(pulse, HIGH);  // start step
        delayMicroseconds(ramp_delay);              // wait for a n u seconds 320us needed
        digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(pulse, LOW);  // stop step
        delayMicroseconds(ramp_delay);              // wait for a 5ms second
        ramp_delay = ramp_delay + 10;
        count ++;
}
}


