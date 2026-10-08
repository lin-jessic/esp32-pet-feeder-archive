#include <Arduino.h>
#include <Servo.h>
#define motor_pin_ 22 //SG90 Pin
#define btn_pin_ 21 //按鈕pin 手動放料
/*七段顯示器腳位定義*/
#define senven_seg_pin_a 19 //七段顯示器腳位 7
#define senven_seg_pin_b 18 //七段顯示器腳位 6
#define senven_seg_pin_c 5  //七段顯示器腳位 4
#define senven_seg_pin_d 17 //七段顯示器腳位 2
#define senven_seg_pin_e 16 //七段顯示器腳位 1
#define senven_seg_pin_f 4  //七段顯示器腳位 9
#define senven_seg_pin_g 0  //七段顯示器腳位 10


namespace MOTOR_CONTROLLER
{


  enum gate_statu
  {
      open_ = 0 ,
      close_
  };
 
  class motor_controller
  {
      public:
        motor_controller();
        ~motor_controller();
        int begin();
        void gate_control();
        void sevenSegWrite(byte digit);
        void btn_control();
        inline int getMotorCount(){return motor_count_;};
        void close_motor(){myServo_.write(position_close_);};
      private:
        gate_statu gate_statu_;
        Servo myServo_;
        int position_open_ = 35;
        int position_close_= 0;
        int seg_pin_arr[7] = {senven_seg_pin_a , senven_seg_pin_b , senven_seg_pin_c , senven_seg_pin_d , senven_seg_pin_e ,
        senven_seg_pin_f , senven_seg_pin_g};
        byte seven_seg_digits[10][7] = {
                                 { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
                             };
         
        unsigned long timePrevious, timeCurrent;
        int motor_count_ = 0;
       
  };
}
