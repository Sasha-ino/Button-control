#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <RotaryEncoder.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Wire.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#define SKREEN_WIDTH 128
#define SKREEN_HEIGHT 64
#include <EEPROM.h>

char* ecran_tecst[] = {"ControlAcceleration", "ControlSpeedMax", "ProgramTest", "RunMyProgram"};

class myControl{
  private:
enum ecran_control_print{Home, ControlAcceleration, ControlSpeedMax, ProgramTest, RunMyProgram};
ecran_control_print ecran_print = Home;


Adafruit_SSD1306 display{SKREEN_WIDTH, SKREEN_HEIGHT, &Wire, -1};
RotaryEncoder encoder{2, 3};
AccelStepper stepper{1, 4, 5};


uint8_t _pin_butt;
uint8_t _pin_encoder;
uint16_t Acceleration_control = 500;
uint16_t Sped_Max_control = 500;
bool butt_flag = 0;
uint32_t millis_button = 0;
bool encoder_butt_flag = 0;
uint32_t millis_button_encoder = 0;
int16_t lass_poss = 0;
uint8_t control_encoder = 4;
bool control_encoder_print = 0;   // малюємо коли змінилося число   
bool print_start = 1;
bool button_encoder_flag_control_menu = 0;
bool ontrocl_button_menu = 0;





public:
myControl(uint8_t pin_encoder, uint8_t pin_butt) : _pin_butt(pin_butt), _pin_encoder(pin_encoder) {}
void begin(){
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
  stepper.setAcceleration(Acceleration_control);
  stepper.setMaxSpeed(Sped_Max_control);
  pinMode(_pin_butt, INPUT_PULLUP);
  pinMode(_pin_encoder, INPUT_PULLUP);
  EEPROM.put(0, 0);
EEPROM.put(2, 0);
EEPROM.put(4, 0);
}
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void buttonTick(){
  bool button;
  button = !digitalRead(_pin_butt);
if (button == 1 && butt_flag == 0 && millis() - millis_button > 200){
  butt_flag = 1; 
  millis_button = millis();
  Serial.println("кнопку натиснуто");
  stepper.stop();
}
if (button == 0 && butt_flag == 1){
  butt_flag = 0;
  stepper.move(1000000000);
}
 bool button_encoder;
 button_encoder = !digitalRead(_pin_encoder);
if (button_encoder == 1 && encoder_butt_flag == 0 && millis() - millis_button_encoder > 200){
  encoder_butt_flag = 1;
  millis_button_encoder = millis();
  Serial.println("кнопку енкодера натиснуто");
}
if (button_encoder == 0 && encoder_butt_flag == 1){
  encoder_butt_flag = 0;
  button_encoder_flag_control_menu = !button_encoder_flag_control_menu;
  ontrocl_button_menu = 1;
}
if (button_encoder_flag_control_menu == 1 && ontrocl_button_menu == 1){
  ontrocl_button_menu = 0;

 if(print_start == 0){
    EEPROM.put(0, lass_poss);
 }

  switch(lass_poss){
    case 0:{ 
      ecran_print = ControlAcceleration; 
      print_start = 1; 
      control_encoder = 10; 
      uint16_t encoder_control;
        EEPROM.get(2, encoder_control);
        encoder.setPosition(encoder_control);
        lass_poss = encoder_control;
      break;}
    case 1:{ 
      ecran_print = ControlSpeedMax; 
      print_start = 1; 
      control_encoder = 10; 
       uint16_t encoder_control;
          EEPROM.get(4, encoder_control);
        encoder.setPosition(encoder_control);
        lass_poss = encoder_control;

      break;}
    case 2:{ ecran_print = ProgramTest; print_start = 1; break;}
    case 3:{ ecran_print = RunMyProgram; print_start = 1; break;}
  }
}
else if (button_encoder_flag_control_menu == 0 && ontrocl_button_menu == 1){
    if(print_start == 0){
  for (uint8_t i = 2; i < (5 * 2); i = i + 2 ){
    if (ecran_print == i / 2){
       EEPROM.put(i, lass_poss);
    }
  }
  }
  ontrocl_button_menu = 0;
  ecran_print = Home; 
  print_start = 1;
   control_encoder = 4;
   uint16_t encoder_control;
    EEPROM.get(0, encoder_control);
    encoder.setPosition(encoder_control);
    lass_poss = encoder_control;
   }

}
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
 void controlTict(){
  stepper.run();
  encoder.tick();
 }
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
void encoderTick(){
int16_t NewPos = encoder.getPosition();
if (lass_poss != NewPos){
if (NewPos < 0){ encoder.setPosition(0); lass_poss = 0;}
else if (NewPos == control_encoder){encoder.setPosition(control_encoder - 1); lass_poss = control_encoder - 1;}
else {lass_poss = NewPos; control_encoder_print = 1;}
if (control_encoder_print){
  Serial.println(lass_poss);
}
}
}
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
void MenyHome(){
if (control_encoder_print == 1 || print_start == 1){
control_encoder_print = 0;
 /*if (print_start == 1){
  encoder.setPosition(0);
  lass_poss = 0;
}
*/
 display.clearDisplay();
 switch(ecran_print){
  case Home:{
   
for (uint8_t i = 0; i < control_encoder; i++){
 if (i == lass_poss){
        display.fillRect(0, i * 12, 128, 12, WHITE); // Прямокутник на весь рядок
        display.setTextColor(BLACK);
      } else {
        display.setTextColor(WHITE);
       display.fillRect(0, i * 12, 128, 12, BLACK); 
        
      }
      display.setCursor(5, i * 12 + 2);
      display.print(ecran_tecst[i]);
    }
    display.display();
    break;
}

case ControlAcceleration:{
   display.drawRect(10, 25, 108, 14, WHITE);
uint8_t control_menu = map(lass_poss, 0, control_encoder - 1, 10, 108);
display.fillRect(10, 25, control_menu, 14, WHITE);
Sped_Max_control = map(lass_poss, 0, control_encoder - 1, 50, 2000);
 stepper.setAcceleration(Sped_Max_control);
  display.display();
   break;
}
case ControlSpeedMax:{
   display.drawRect(10, 25, 108, 14, WHITE);
uint8_t control_menu = map(lass_poss, 0, control_encoder - 1, 10, 108);
display.fillRect(10, 25, control_menu, 14, WHITE);
Sped_Max_control = map(lass_poss, 0, control_encoder - 1, 50, 3000);
  stepper.setMaxSpeed(Sped_Max_control);
  display.setCursor(5, 50);
  display.print("GOOD");
  display.display();
break;
}
case ProgramTest:{
break;
}
case RunMyProgram:{
 stepper.moveTo(9999);
break;
}


}
  print_start = 0;
}
}
};


myControl motorControl(6, 7);

void setup() {
  // put your setup code here, to run once:
motorControl.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
motorControl.controlTict();
motorControl.buttonTick();
motorControl.encoderTick();
motorControl.MenyHome();
}








