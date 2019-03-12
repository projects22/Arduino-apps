/*
 * Blurtooth Frequency Counter
 * Created: 12/08/2017 23:34:47
 *  Author: mfprojects.co.uk
*/


// the setup function runs once when you press reset or power the board
void setup() {
        // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    pinMode(5,INPUT_PULLUP);
    pinMode(6,INPUT_PULLUP);
    pinMode(7,INPUT_PULLUP);
    pinMode(8,INPUT_PULLUP);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
}

  
  // the loop function runs over and over again forever
void loop() {
  
  if(!digitalRead(5)) {Serial.write(5); delay(1000);}
  else if(!digitalRead(6)) {Serial.write(6); delay(1000);}    
  else if(!digitalRead(7)) {Serial.write(7); delay(1000);}
  else if(!digitalRead(8)) {Serial.write(8); delay(1000);}    
  //else {Serial.write(0); delay(1000);}


}

