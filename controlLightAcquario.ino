
#define RELAY1  7 
#include <DS3231.h>
#include <Wire.h>
DS3231 rtc;
bool h12 = false;
bool PM = true;
bool Century = true;

bool set = false;
int year = 18;
int month = 5;
int date = 20;
int hour = 19;
int minute = 03;
int second = 0;
String accensioneLuce;   //Declare a String variable to hold your name
bool changeValue = true;

void setup() {
  Serial.begin(9600);      // turn on Serial Port
  pinMode(RELAY1, OUTPUT);   
  Wire.begin();

  if(set){
    rtc.setClockMode(false);
    rtc.setYear(year);
    rtc.setMonth(month);
    rtc.setDate(20);
    rtc.setHour(hour);
    rtc.setMinute(minute);
    rtc.setSecond(second);
    rtc.setDoW(2);
   
  } 
}
 
void loop() {
  bool on = false; 
  
 while(true){
      Serial.print(rtc.getYear());
      Serial.print("-");
      Serial.print(rtc.getMonth(Century));
      Serial.print("-");
      Serial.print(rtc.getDate());
      Serial.print(" ");
      Serial.print(rtc.getHour(h12,PM)); //24-hr
      Serial.print(":");
      Serial.print(rtc.getMinute());
      Serial.print(":");
      Serial.println(rtc.getSecond());
      Serial.print(rtc.getDoW(), DEC);
      Serial.println();
  
      int hour = int(rtc.getHour(h12,PM)); 
      
      if(hour >= 9 && hour <= 20 && !on){
        
        digitalWrite(RELAY1,0);           // Turns ON Relays 1
        Serial.println("Light ON");
        on = true;
      
      }else if((hour<=9 || hour >=20) && on){
        
        digitalWrite(RELAY1,1);           // Turns ON Relays 1
        Serial.println("Light OFF");
        on = false;
        
      }
      
      int dayOfWeek = int(rtc.getDoW());
      int dayOfMonth = int(rtc.getDate());
      int month = int(rtc.getMonth(Century));
      
      if(changeValue && (month == 3 || month == 10)){
        
          if(dayOfWeek == 2 && hour >= 3 && dayOfMonth + 7 < 31 ){
          
            switch(month){
              case 3:
                rtc.setHour(hour +1 );
                changeValue = false;
                break;
              case 10:
                rtc.setHour(hour - 1);
                changeValue = false;
                break;
              default:
                break;
            }
        }
        
      }
      
     if(month == 4 || month == 11){
      
        changeValue = true;
      }
      
      
      delay (60000*10); // every 10 min
  }
  
}

