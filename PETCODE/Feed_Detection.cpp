#include "Feed_Detection.h"




namespace FEEDDETECTION
{
  feed_detection::feed_detection()
  {
   
  }
 
  feed_detection::~feed_detection()
  {
   
  }
 
  int feed_detection::begin()
  {
      pinMode(LED_G_PIN_, OUTPUT);
      pinMode(LED_Y_PIN_, OUTPUT);
      pinMode(LED_R_PIN_, OUTPUT);
      pinMode(bez_pin, OUTPUT);
      pinMode(light_module_pin_mid_, INPUT);
      pinMode(light_module_pin_bottom_, INPUT);


      return 1;
  }


  void feed_detection::LED_control(LED_type type)
  {
      switch(type)
      {
        case LED_type::LED_G :
          digitalWrite(LED_G_PIN_, HIGH);
          digitalWrite(LED_Y_PIN_, LOW);
          digitalWrite(LED_R_PIN_, LOW);
          break;
        case LED_type::LED_Y :
          digitalWrite(LED_G_PIN_, LOW);
          digitalWrite(LED_Y_PIN_, HIGH);
          digitalWrite(LED_R_PIN_, LOW);
          break;
        case LED_type::LED_R :
          digitalWrite(LED_G_PIN_, LOW);
          digitalWrite(LED_Y_PIN_, LOW);
          digitalWrite(LED_R_PIN_, HIGH);
          break;
        case LED_type::LED_ALL_BLINK :
          digitalWrite(LED_G_PIN_, LOW);
          digitalWrite(LED_Y_PIN_, LOW);
          digitalWrite(LED_R_PIN_, LOW);
          delay(300);
          digitalWrite(LED_G_PIN_, HIGH);
          digitalWrite(LED_Y_PIN_, HIGH);
          digitalWrite(LED_R_PIN_, HIGH);
          delay(300);
          digitalWrite(LED_G_PIN_, LOW);
          digitalWrite(LED_Y_PIN_, LOW);
          digitalWrite(LED_R_PIN_, LOW);
          delay(300);
          digitalWrite(LED_G_PIN_, HIGH);
          digitalWrite(LED_Y_PIN_, HIGH);
          digitalWrite(LED_R_PIN_, HIGH);
          delay(300);
          digitalWrite(LED_G_PIN_, LOW);
          digitalWrite(LED_Y_PIN_, LOW);
          digitalWrite(LED_R_PIN_, LOW);
          break;
        default:
          digitalWrite(LED_G_PIN_, LOW);
          digitalWrite(LED_Y_PIN_, LOW);
          digitalWrite(LED_R_PIN_, LOW);
          break;
      }
  }


  void feed_detection::buzz_control(bool ison)
  {
      if(ison)
        digitalWrite(bez_pin, HIGH);
      else
        digitalWrite(bez_pin, LOW);
  }


  void feed_detection::Ano_read_lightData()
  {   ///數值越高表示越暗 ADC  4095 dark , 1300 light
      light_mid_value_ = analogRead(light_module_pin_mid_);
      light_bottom_value_ = analogRead(light_module_pin_bottom_);
      light_arr[0] = light_mid_value_;
      light_arr[1] = light_bottom_value_;
      Serial.println("Mid : " + (String)light_arr[0]);
//      delay(100);
      Serial.println("Bottom : " + (String)light_arr[1]);
//      delay(100);
  }
 
}
