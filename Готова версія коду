

const uint8_t pin = 2;
const uint8_t pin_buzzor = 3;
const uint16_t delay_millis_butt = 0;
const uint16_t delay_millis_last_press = 1000; 
const uint16_t many_press_delay = 400;
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
static uint32_t many_press_millis = 0;
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
    last_press_function();
    digitalWrite(pin_buzzor, 0);
  }
}
if (butt == 0 && butt_flag == 1 && millis() - butt_millis > delay_millis_butt){
  if (last_flag == 1){
    noner_many_press++;
     last_flag = 0;
     many_press_millis = millis();
     digitalWrite(pin_buzzor, 0);
  } 
  butt_flag = 0;  
  butt_millis = millis();
}
if (millis() - many_press_millis > many_press_delay && noner_many_press > 0){
press_function(noner_many_press);
noner_many_press = 0;
}
}















void last_press_function(){
  Serial.println("last press");
}

void press_function(uint8_t press){
switch(press){
  case 1:{ Serial.println("one function"); break;}
    case 2:{ Serial.println("two function"); break;}
      case 3:{ Serial.println("three function"); break;}
        case 4:{ Serial.println("four function"); break;}
          case 5:{ Serial.println("five function"); break;}
            case 6:{ Serial.println("six function"); break;}
              case 7:{ Serial.println("seven function"); break;}
                case 8:{ Serial.println("eight function"); break;}
                  case 9:{ Serial.println("nine function"); break;}
                    case 10:{ Serial.println("ten function"); break;}
                    default:{ Serial.println("no function"); break;}
}
}




