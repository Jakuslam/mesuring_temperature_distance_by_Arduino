/*

 Mesering temperature of object by IR sensor (MLX90614) and corecting tempereature using ultra soud distance meter


Seminární práce Jakuba Slámy
*/

#include <Wire.h>  
#include <Adafruit_MLX90614.h> // Library for IR sensor

//SD card pins
#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 10  //using digital pin 10 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

//inicialization vareables for temperature sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// inicialization of pins for distance sensor
const int trigPin = 3;
const int echoPin = 6;

//set up everithing
void setup() {
// Setup pin for US sensor
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//start serial monitor
  Serial.begin(9600);
  Serial.println("Test");
//begin mesuring temperature
  mlx.begin();
//inicializating speaker pin
tmrpcm.speakerPin = 9;
if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  tmrpcm.play("one.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
}

float getDistance(){
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;// Calculating the distance in cm

  return distance;
}

//get temperature
float getTemp(){
  float tempObjectC;
  tempObjectC = mlx.readObjectTempC();
  return tempObjectC;
}

void printTemp(){
  float tmp = getTemp();    
  Serial.print(tmp);    
  Serial.println("C");
}

void sayNumber(int temp){
  int decimal = temp / 10 ;
  int rest = temp % 10; 

  if(decimal != 1){
    switch(rest){
      case 1:
        tmrpcm.play("one.wav");
      break;
      case 2:
        tmrpcm.play("two.wav");
      break;
      case 3:
        tmrpcm.play("three.wav");
      break;
      case 4:
        tmrpcm.play("four.wav");
      break;
      case 5:
        tmrpcm.play("five.wav");
      break;
      case 6:
        tmrpcm.play("six.wav");
      break;
      case 7:
        tmrpcm.play("seven.wav");
      break;
      case 8:
        tmrpcm.play("eight.wav");
      break;
      case 9:
        tmrpcm.play("nine.wav");
      break;
    }

    tmrpcm.play("and.wav");

    switch(decimal){
      case 2:
        tmrpcm.play("twenty.wav");
      break;
      case 3:
        tmrpcm.play("thirty.wav");
      break;
      case 4:
        tmrpcm.play("forty.wav");
      break;
      case 5:
        tmrpcm.play("fifty.wav");
      break;
      case 6:
        tmrpcm.play("sixty.wav");
      break;
      case 7:
        tmrpcm.play("seventy.wav");
      break;
      case 8:
        tmrpcm.play("eighty.wav");
      break;
      case 9:
        tmrpcm.play("ninety.wav");
      break;
    }

  }
  


  Serial.println(decimal);
  Serial.println(rest);
}

void desideWhatToSay(int temp){
  sayNumber(temp);

}

void loop() {

    // Prints the distance on the Serial Monitor
  Serial.print(getDistance());
  Serial.print(", ");
  Serial.println(getTemp());
  desideWhatToSay(int(round(getTemp())));
  
  delay(1000);
}
