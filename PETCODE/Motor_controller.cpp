#include <Arduino.h>


#define LED_G_PIN_ 12
#define LED_Y_PIN_ 14
#define LED_R_PIN_ 27


#define light_module_pin_mid_ 25 //中間光敏電阻 AD0
#define light_module_pin_bottom_ 26 //底部光敏電阻 AD3


#define bez_pin 13 //蜂鳴器




namespace FEEDDETECTION
{
  enum LED_type
  {
      LED_G = 0, LED_Y , LED_R , LED_ALL_BLINK , LED_DIS_ALL
  };


 
  class feed_detection
  {
      public:
        feed_detection();
        ~feed_detection();
        int begin();
        void LED_control(LED_type type);
        void buzz_control(bool ison);
        void Ano_read_lightData();
        int * getLightData(){return light_arr;};
      private:
        LED_type led_type_ = LED_type::LED_DIS_ALL;
        int light_mid_value_ , light_bottom_value_;
        int light_arr[2] = {0};
  };
}


Motor_controller.cpp
#include "Motor_controller.h"


namespace MOTOR_CONTROLLER
{
    motor_controller::motor_controller()
    {
     
    }
    motor_controller::~motor_controller()
    {
     
    }
    int motor_controller::begin()
    {
      pinMode(senven_seg_pin_a, OUTPUT);  
      pinMode(senven_seg_pin_b, OUTPUT);
      pinMode(senven_seg_pin_c, OUTPUT);
      pinMode(senven_seg_pin_d, OUTPUT);
      pinMode(senven_seg_pin_e, OUTPUT);
      pinMode(senven_seg_pin_f, OUTPUT);
      pinMode(senven_seg_pin_g, OUTPUT);


      pinMode(btn_pin_ , INPUT);
     
      myServo_.attach(motor_pin_);
      myServo_.write(0);
      return 1;
    }


    void motor_controller::gate_control()
    {
       myServo_.write(position_open_);
       delay(1000); //3s
       myServo_.write(position_close_);
       motor_count_ ++;
       if(motor_count_ > 9)
        motor_count_ = 0;  
    }
 
    void motor_controller::sevenSegWrite(byte digit)
    {
        if(digit < 10)
        {
            for (byte seg = 0; seg < 7; ++seg)
            {
               digitalWrite(seg_pin_arr[seg], seven_seg_digits[digit][seg]);
            }
        }    
    }


    //按鈕防彈跳 , 手動觸發
    void motor_controller::btn_control()
    {
        timeCurrent = millis();
        if ((timeCurrent - timePrevious) > 200) //扣掉上次按下ㄉ時間要大於 200ms , 才觸發按_鈕功能 避免連續彈跳問題
        {
            timePrevious = timeCurrent;
            gate_control();
        }
    }


}

