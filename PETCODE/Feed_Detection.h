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
