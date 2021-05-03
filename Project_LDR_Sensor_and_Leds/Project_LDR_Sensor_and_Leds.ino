#define CAYANNE_DEBUG
#define CAYANNE_PRINT Serial
#define LDR_D0_green 18
#define LDR_D0_blue 18
#define LDR_D0_yellow 18

#define green_LED 15
#define blue_LED 22
#define yellow_LED 23

#define ROOM_1_CHANNEL 1
#define ROOM_2_CHANNEL 2
#define ROOM_3_CHANNEL 3

#include <CayenneMQTTESP32.h>
#include <Time.h>
#include <TimeLib.h>

char username[] = "3e3aa4b0-a47d-11eb-8779-7d56e82df461";
char password[] = "b6e05921421ce3269dc0624b00fd2b036a3f996c";
char clientID[] = "7fe15340-a47e-11eb-b767-3f1a8f1211ba";
char ssid[]= "WE7EA1CC";
char wifiPassword[]="kb450229";
int flag_set_from_button[3]={0,0,0};
long long time1=0,time2=0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(LDR_D0_green, INPUT);
  pinMode(LDR_D0_blue, INPUT);
  pinMode(LDR_D0_yellow, INPUT);
  time1 = millis();
  pinMode(green_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  //t.pulse(13, 2* 60 * 1000, HIGH);
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID,ssid,wifiPassword);
}


void turn_on_off(int pin_LDR_no, int pin_out_no, int room_channel){
  if(flag_set_from_button[room_channel-1] == 0){
    int sensorValue = digitalRead(pin_LDR_no);
    if(sensorValue==1) digitalWrite(pin_out_no, HIGH);
    if(sensorValue==0) digitalWrite(pin_out_no, LOW);
    Cayenne.virtualWrite(room_channel, sensorValue,"Digital LDR Reading", "binary");
  }
}

void turn_on_off_green_schedule(){
  if(month()=5 && day()==3 && hour()==1 && minute()==5 && second()>=30){
      digitalWrite(green_LED, HIGH);
  }
  if(month()=5 && day()==3 && hour()==1 && minute()==5 && second()>=30){
      digitalWrite(green_LED, LOW);
  }
}

void turn_on_off_yellow_schedule(){
  if(month()=5 && day()==3 && hour()==1 && minute()==5 && second()>=30){
      digitalWrite(yellow_LED, HIGH);
  }
  if(month()=5 && day()==3 && hour()==1 && minute()==5 && second()>=30){
      digitalWrite(yellow_LED, LOW);
  }
}

void turn_on_off_blue_schedule(){
  if(month()=5 && day()==3 && hour()==1 && minute()==5 && second()>=30){
      digitalWrite(blue_LED, HIGH);
  }
  if(month()=5 && day()==3 && hour()==1 && minute()==5 && second()>=30){
      digitalWrite(blue_LED, LOW);
  }
}

void loop() {
  Cayenne.loop();
  time2=millis();
  turn_on_off_yellow_schedule();
  turn_on_off(LDR_D0_green, green_LED, ROOM_1_CHANNEL);
  turn_on_off(LDR_D0_blue, blue_LED, ROOM_2_CHANNEL);
  turn_on_off(LDR_D0_yellow, yellow_LED, ROOM_3_CHANNEL);
}

CAYENNE_IN(4){
  digitalWrite(green_LED, getValue.asInt() );
  flag_set_from_button[0] = getValue.asInt();
}

CAYENNE_IN(5){
  digitalWrite(blue_LED, getValue.asInt() );
  flag_set_from_button[1] = getValue.asInt();
}

CAYENNE_IN(6){
  digitalWrite(yellow_LED, getValue.asInt() );
  flag_set_from_button[2] = getValue.asInt();
}
