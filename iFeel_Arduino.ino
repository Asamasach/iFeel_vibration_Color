//a project for iFeel sensing
//Mainatance: asamasach@gmail.com
//-----------------------------------

int S0 = 4;//pinB
int S1 = 5;//pinA
int S2 = 6;//pinE
int S3 = 7;//pinF
int taosOutPin = 8;//pinC
int LED = 13;//pinD
int grey=0;

void setup() {
TCS3200setup();
Serial.begin(115200);
Serial.print("\n\n\nready\n\n\n");
delay(100);
}

// primary loop takes color readings from all four channels and displays the raw values once per second.  What you might wish to do with those values is up to you...
void loop() {

detectColor(taosOutPin);
Serial.print("\n\n\n");
delay(200);
vibr(grey);

}

int detectColor(int taosOutPin){

float white = colorRead(taosOutPin,0,1);
float red = colorRead(taosOutPin,1,1);
float blue = colorRead(taosOutPin,2,1);
float green = colorRead(taosOutPin,3,1);

Serial.print("white ");
Serial.println(white);

Serial.print("red ");
Serial.println(red);

Serial.print("blue ");
Serial.println(blue);

Serial.print("green ");
Serial.println(green);
//analogWrite(12, (white+red+blue+green)/4);
grey=0.2126*red+0.7152*green+0.0722*blue;
}


float colorRead(int taosOutPin, int color, boolean LEDstate){ 

taosMode(1);

//setting for a delay to let the sensor sit for a moment before taking a reading.
int sensorDelay = 100;

//set the S2 and S3 pins to select the color to be sensed 
if(color == 0){//white
digitalWrite(S3, LOW); //S3
digitalWrite(S2, HIGH); //S2
// Serial.print(" w");
}

else if(color == 1){//red
digitalWrite(S3, LOW); //S3
digitalWrite(S2, LOW); //S2
// Serial.print(" r");
}

else if(color == 2){//blue
digitalWrite(S3, HIGH); //S3
digitalWrite(S2, LOW); //S2 
// Serial.print(" b");
}

else if(color == 3){//green
digitalWrite(S3, HIGH); //S3
digitalWrite(S2, HIGH); //S2 
// Serial.print(" g");
}

// create a var where the pulse reading from sensor will go
float readPulse;

//  turn LEDs on or off, as directed by the LEDstate var
if(LEDstate == 0){
    digitalWrite(LED, LOW);
}
if(LEDstate == 1){
    digitalWrite(LED, HIGH);
}

// wait a bit for LEDs to actually turn on, as directed by sensorDelay var
delay(sensorDelay);

// now take a measurement from the sensor, timing a low pulse on the sensor's "out" pin
readPulse = pulseIn(taosOutPin, LOW, 80000);

//if the pulseIn times out, it returns 0 and that throws off numbers. just cap it at 80k if it happens
if(readPulse < .1){
readPulse = 80000;
}

//turn off color sensor and LEDs to save power 
taosMode(0);

// return the pulse value back to whatever called for it... 
return readPulse;

}

void vibr(int delay_time){
analogWrite(12,512);
delay(50);
analogWrite(12,0);
delay(delay_time/1000);
return;
}
void taosMode(int mode){
    
    if(mode == 0){
    //power OFF mode-  LED off and both channels "low"
    digitalWrite(LED, LOW);
    digitalWrite(S0, LOW); //S0
    digitalWrite(S1, LOW); //S1
    //  Serial.println("mOFFm");
    
    }else if(mode == 1){
    //this will put in 1:1, highest sensitivity
    digitalWrite(S0, HIGH); //S0
    digitalWrite(S1, HIGH); //S1
    // Serial.println("m1:1m");
    
    }else if(mode == 2){
    //this will put in 1:5
    digitalWrite(S0, HIGH); //S0
    digitalWrite(S1, LOW); //S1
    //Serial.println("m1:5m");
    
    }else if(mode == 3){
    //this will put in 1:50
    digitalWrite(S0, LOW); //S0
    digitalWrite(S1, HIGH); //S1 
    //Serial.println("m1:50m");
    }
    
    return;

}

void TCS3200setup(){

    //initialize pins
    pinMode(LED,OUTPUT); //LED pinD
    
    //color mode selection
    pinMode(S2,OUTPUT); //S2 pinE
    pinMode(S3,OUTPUT); //s3 pinF
    
    //color response pin (only actual input from taos)
    pinMode(taosOutPin, INPUT); //taosOutPin pinC
    
    //communication freq (sensitivity) selection
    pinMode(S0,OUTPUT); //S0 pinB
    pinMode(S1,OUTPUT); //S1 pinA 
    
    return;

}
