#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT
#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "levanvu"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,13,0,43,0,10,13,0,
  2,0,58,16,22,11,2,26,31,31,
  79,78,0,79,70,70,0,65,4,26,
  15,9,9,66,132,25,35,13,10,2,
  24,67,4,40,38,20,5,2,26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

  // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF  

    // output variables
  uint8_t led_1_r; // =0..255 LED Green brightness 
  int8_t level_1; // =0..100 level position 
  char text_1[11];  // string UTF8 end zero 
    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 13
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,7,6,5,4);

#define in 14
#define out 19
int count=0;

void IN()
{
    count++;
    lcd.clear();
    lcd.print("So Nguoi:");
    lcd.setCursor(0,1);
    lcd.print(count);
    delay(1000);
}

void OUT()
{
    count--; {if(count <= 0) {count=0; return;}}
    lcd.clear();
    lcd.print("So Nguoi:");
    lcd.setCursor(0,1);
    lcd.print(count);
    delay(1000);
}

void setup() 
{
  RemoteXY_Init (); 
  lcd.begin(16,2);
  lcd.print("Dem So Nguoi!!!");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(PIN_SWITCH_1, OUTPUT);
  lcd.clear();
  lcd.print("So Nguoi:");
  lcd.setCursor(0,1);
  lcd.print(count);
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 

  //if((RemoteXY.switch_1==0) ? RemoteXY.PIN_SWITCH_1_1_g = 0 : RemoteXY.PIN_SWITCH_1_1_g =255);
  if(digitalRead(in) == LOW)
  IN();
  if(digitalRead(out) == LOW)
  OUT();
  if((RemoteXY.switch_1==0) ? RemoteXY.led_1_r = 0 : RemoteXY.led_1_r = 255);
 
  RemoteXY.level_1=count; // =0..100 level position 
  
  strcpy(RemoteXY.text_1, itoa(count, RemoteXY.text_1,10));
  
  if(count<=0)
  {   
     if((RemoteXY.switch_1==0)){
        lcd.clear();
        digitalWrite(PIN_SWITCH_1, LOW);
        RemoteXY.led_1_r = 0;
        lcd.clear();
        lcd.print("Khong Co Ai!");
        lcd.setCursor(0,1);
        lcd.print("Den TAT.");
        delay(200);
    }
    else{
      lcd.clear();
      digitalWrite(PIN_SWITCH_1, HIGH);
      RemoteXY.led_1_r = 255;
      lcd.clear();
      lcd.print("Khong Co Ai!");
      lcd.setCursor(0,1);
      lcd.print("Den SANG.");
      delay(200);
    }
  }
  else
  {
    digitalWrite(PIN_SWITCH_1, HIGH);
    RemoteXY.led_1_r = 255;
  }
}
