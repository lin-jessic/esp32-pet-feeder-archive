#include "Motor_controller.h"
#include "Feed_Detection.h"


using namespace MOTOR_CONTROLLER;
using namespace FEEDDETECTION;
motor_controller *motor;
feed_detection *feed;


int state_ = 0;




/*Timer ISR*/
hw_timer_t * timer = NULL;
volatile int FLAG_timIT = 0 ;
 
void IRAM_ATTR Callback_TimerIT()
{
   FLAG_timIT = 1; //Timer flag 1 , ISR Func cant block
}


void Timer_Init()
{  
    // 1 / (80MHZ/80) = 1us
    timer = timerBegin(1, 80 , true); //Timer 0 , 80 = 不分頻 ,countup , reset Timer = true;
    timerAttachInterrupt(timer , &Callback_TimerIT , true); //callback to Timer
    timerAlarmWrite(timer , 1000000 , true);  //1s = 1000000us , so is 5s timer will interrupt , true = repeat timer
    timerAlarmEnable(timer); // enable timer0
    Serial.println("Timer 0 is Start now!");
}
/*Timer ISR*/


/*Btn ISR*/
volatile bool FLAG_btn = false;


void IRAM_ATTR Callback_btnIT()
{
   FLAG_btn = true; //Timer flag 1 , ISR Func cant block
}


void Btn_Intet_Init()
{
  attachInterrupt(digitalPinToInterrupt(btn_pin_) ,Callback_btnIT , HIGH );
  Serial.println("btn interrupt is Start now!");
}
/*Btn ISR*/




void setup() {
  Serial.begin(115200);
  motor = new motor_controller();
  feed = new feed_detection();
 
  do
  {
      if(!motor->begin())
        break;
      if(!feed->begin())
        break;
      feed->LED_control(LED_type::LED_ALL_BLINK);
      delay(500);
      Serial.println("Init Ok!");
      Timer_Init();
      Btn_Intet_Init();
  }while(false);
 
}


void loop() {


  motor->sevenSegWrite(motor->getMotorCount());
  feed->Ano_read_lightData();
 
  // btn trigger interrupt manual
  if(FLAG_btn) //btn interrupt trigger flag
  {
    Serial.println("Btn Trigger");
    motor->gate_control();
    Serial.println("Btn Trigger : " + String(motor->getMotorCount()) );
    FLAG_btn = false; //after trigger need to set Flag to false
  }


  // Timer trigger interrupt AUTO
  if(FLAG_timIT && state_ == 0) //timer interrupt trigger flag
  {
    if(state_ == 0 )
    {
      motor->close_motor();
    }
    Serial.println("Timer Trigger");
    motor->gate_control();
    Serial.println("Timer Trigger : " + String(motor->getMotorCount()) );
    FLAG_timIT = 0; //after trigger need to set Flag to false
  }


  //數值越高表示越暗
  if(feed->getLightData()[0] < 2300 && feed->getLightData()[1] < 2300) //if feed empty
  {
      state_ = 1;
      feed->LED_control(LED_type::LED_R);
      feed->buzz_control(true);
      motor->close_motor();
  }
  else if(feed->getLightData()[0] < 2300 || feed->getLightData()[1] < 2300) //mid light module
  {
      state_ = 0;
      feed->LED_control(LED_type::LED_Y);
      feed->buzz_control(false);
  }
  else //if feed is ok
  {
      state_ = 0;
      feed->LED_control(LED_type::LED_G);
      feed->buzz_control(false);
  }
 


 
}

