int tau;
int R;
 
int experiment_counter;
void setup() {
  // put your setup code here, to run once:
  tau = 1; // tau = 1 second
  R = 1e6; // R = 1e6 ohm
  experiment_counter = 0;
  int bps = 9600; // velocità, espressa in bps (boud rate per secondo).
  Serial.begin(bps);
  pinMode(2,OUTPUT); // set pin mode of second pin to OUTPUT
  discharge();
  
}

void charge(){
  digitalWrite(2, HIGH); //// turn ON battery
  Serial.print("Experiment n. ");
  Serial.print(experiment_counter);
  Serial.print("\n");
  unsigned long startChargingTime = millis();
  unsigned long chargeTime = startChargingTime;
  int seconds = 6;
  while(chargeTime < startChargingTime+seconds*1000){
     int sensorValue = analogRead(A0); //read tension 
     float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 – 1023) to a voltage (0 – 5V)
     chargeTime = millis(); //get current time
     Serial.print(chargeTime-startChargingTime); // print charging time
     Serial.print(" "); 
     Serial.print(voltage); //print voltage
     Serial.print("\n");
     delay(100); //wait 100ms 
  }
  
}

void discharge(){
  digitalWrite(2, LOW); // turn OFF battery
  int seconds = 6;
  Serial.println("Discharging...");
  unsigned long startDischargingTime = millis();
  unsigned long dischargeTime = startDischargingTime;
  while(dischargeTime < startDischargingTime+seconds){
    int sensorValue = analogRead(A0); //read tension 
    float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 – 1023) to a voltage (0 – 5V)
    dischargeTime = millis();
    Serial.print(dischargeTime-startDischargingTime); // print charging time
     Serial.print(" "); 
     Serial.print(voltage); //print voltage
     Serial.print("\n");
     delay(100); //wait 100ms 
  }
   
}

void stop(){
  Serial.println("Stopping sketch");
  while(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  charge();
  discharge();
  experiment_counter++;
  if(experiment_counter==50){
    stop();
  }
}
  /*

  
  //Serial.print("testo");
  timePassed = millis(); //get the time passsed since the Arduino board began running
  digitalWrite(2, HIGH);
  int sensorValue = analogRead(A0); //read tension 
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 – 1023) to a voltage (0 – 5V)
  Serial.println(voltage);
  */
  

