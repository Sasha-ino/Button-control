

//const uint8_t pin_buzzor = 2
const uint8_t pin = 3;
const uint16_t delay_time_butt = 250;
const uint16_t last_millis_time = 1000;

void setup() {
  // put your setup code here, to run once:
pinMode(pin, INPUT_PULLUP);
//pinMode(pin_buzzor, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Button();
}










void Button(){
//if (!digitalRead(pin) == 1){Serial.println("pin good");}
static bool butt_flag = 0;
static uint32_t butt_millis = 0;
bool butt; 
static bool last_flag = 0;
static uint16_t last_millis = 0;
butt = !digitalRead(pin);


if (butt == 1 && butt_flag == 0 && millis() - butt_millis > delay_time_butt && last_flag == 0){
  butt_flag = 1; 
last_millis = millis();
Serial.println("good");
}


if (butt == 1 && millis() - last_millis > last_millis_time/2 && last_flag == 0){
  // digitalWrite(pin_buzzor);
  if (millis() - last_millis > last_millis_time){
    last_butt_function();
    last_flag = 1;
  }
}

if (butt == 0 && butt_flag == 1){
  butt_millis = millis();
  if (last_flag == 1){
    last_flag = 0;
    butt_flag = 0;
  } else{
    last_flag = 0;
    butt_flag = 0;
  }
}


}




void last_butt_function(){
  Serial.println("last press");
}


