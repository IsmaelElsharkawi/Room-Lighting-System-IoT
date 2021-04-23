#define CAYANNE_DEBUG
#define CAYANNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "3e3aa4b0-a47d-11eb-8779-7d56e82df461";
char password[] = "b6e05921421ce3269dc0624b00fd2b036a3f996c";
char clientID[] = "7fe15340-a47e-11eb-b767-3f1a8f1211ba";

char ssid[]= "WE7EA1CC";
char wifiPassword[]="kb450229";

#define LDR_D0_green 18
#define LDR_D0_blue 18
#define LDR_D0_yellow 18
#define green_LED 15
#define blue_LED 22
#define yellow_LED 23

#define ROOM_1_CHANNEL 1
#define ROOM_2_CHANNEL 2
#define ROOM_3_CHANNEL 3
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(LDR_D0_green, INPUT);
  pinMode(LDR_D0_blue, INPUT);
  pinMode(LDR_D0_yellow, INPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID,ssid,wifiPassword);
}


void turn_on_off(int pin_LDR_no, int pin_out_no, int room_channel){
  int sensorValue = digitalRead(pin_LDR_no);
  if(sensorValue==1) digitalWrite(pin_out_no, HIGH);
  if(sensorValue==0) digitalWrite(pin_out_no, LOW);
  Cayenne.virtualWrite(room_channel, sensorValue,"digital_sensor", "d"); //virtual pin that writes temperature to channel 0 cayenne
}
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  Cayenne.loop();
  turn_on_off(LDR_D0_green, green_LED, ROOM_1_CHANNEL);
  turn_on_off(LDR_D0_blue, blue_LED, ROOM_2_CHANNEL);
  turn_on_off(LDR_D0_yellow, yellow_LED, ROOM_3_CHANNEL);
}
