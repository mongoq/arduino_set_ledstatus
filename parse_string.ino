// Define String Communication ------

const byte numChars = 4; // 3 LEDs 
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;

// General Setup ---------------------

void setup() {
 Serial.begin(9600);
 Serial.println("LINKUP");
}

void loop() {
 recvWithEndMarker();
 showNewData();
 setup_leds();
}

// -----------------------------------

// Define LED Pins 
// Trick to use Analog Pins as Digital ones ;-) 

int red = 15;
int red_gnd = 14;
int yellow = 17;
int yellow_gnd = 16;
int green = 19;
int green_gnd = 18;

// Initiliaze LEDs 

void setup_leds() {
  pinMode(red, OUTPUT);
  pinMode(red_gnd, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(yellow_gnd, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(green_gnd, OUTPUT);
  analogWrite(red_gnd, 0);
  analogWrite(yellow_gnd, 0);
  analogWrite(green_gnd, 0);
}

void set_led(byte rgb, byte onoff){
  switch (rgb) {
   case 1: analogWrite(red,    onoff * 255); break;
   case 2: analogWrite(yellow, onoff * 255); break;
   case 3: analogWrite(green,  onoff * 255); break;
   default: break;  
  }
}

// -------------------------------

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 while (Serial.available() > 0 && newData == false) {
 rc = Serial.read();

 if (rc != endMarker) {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string
 ndx = 0;
 newData = true;
 }
 }
}

void showNewData() {
 if (newData == true) {
 //Serial.print("CMD: ");
 //Serial.println(receivedChars);
 //Serial.print("OK");
 Serial.println("OK");
 newData = false;
 dissect_to_leds(receivedChars);
 }
}

void dissect_to_leds(char *arr){
 if      (arr[0]=='1') set_led(1,1);
 else if (arr[0]=='0') set_led(1,0);
 if      (arr[1]=='1') set_led(2,1);
 else if (arr[1]=='0') set_led(2,0);
 if      (arr[2]=='1') set_led(3,1);
 else if (arr[2]=='0') set_led(3,0);
}
