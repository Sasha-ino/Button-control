

const uint8_t pin = 2;
const uint8_t pin_buzzor = 3;
const uint16_t delay_millis_butt = 50;
const uint16_t delay_millis_last_press = 1000; 
void setup() {
  // put your setup code here, to run once:
pinMode(pin, INPUT_PULLUP);
pinMode(pin_buzzor, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
ButtonControl();
}











void ButtonControl(){
static uint32_t last_millis = 0; 
static uint32_t butt_millis = 0;
static uint32_t many_press = 0;

static uint8_t noner_many_press = 0;

static bool butt_flag = 0;
static bool last_flag = 0;

bool butt;
butt = !digitalRead(pin);


if (butt == 1 && butt_flag == 0 && millis() - butt_millis > delay_millis_butt){
  butt_millis = millis();
  butt_flag = 1; 
  last_millis = millis();
  last_flag = 1;
}


if (butt == 1 && butt_flag == 1 && millis() - last_millis > delay_millis_last_press/2 && last_flag == 1){
digitalWrite(pin_buzzor, 1);
  if (millis() - last_millis > delay_millis_last_press){
    last_flag = 0; 
    last_pres_function();
    digitalWrite(pin_buzzor, 0);
  }
}



if (butt == 0 && butt_flag == 1 && millis() - butt_millis > delay_millis_butt){
  if (last_flag == 1){
    noner_many_press++;
    Serial.println(noner_many_press);
     last_flag = 0;
  }
  digitalWrite(pin_buzzor, 0);
  butt_flag = 0;  
  butt_millis = millis();

  
}

}


void last_pres_function(){
  Serial.println("last press");
}






