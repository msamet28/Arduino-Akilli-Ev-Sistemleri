// Mehmet Samet DURSUN 

#include <Key.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


 #define flamepin A0
 #define buzzer 22
 
 #define pir A3
 #define led 25
 
 #define thermometer A1 
 LiquidCrystal lcd(44,45,53,52,51,50,49,48,47,46); //RS,E,D0,D1,D2,D3,D4,D5,D6,D7
 
 #define greenled 23
 #define redled 24

 const byte rows=4;
 const byte columns=3;
 char buttons[rows][columns]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}
                             };
 byte rowPins[rows]={40,41,42,43};
 byte columnPins[columns]={39,38,37};
 Keypad x=Keypad(makeKeymap(buttons),rowPins,columnPins,rows,columns);
 
 char P[4]={'1','2','3','4'};
 char password[4];
 int i=0;
 
 
void setup() 
{
  pinMode(flamepin,INPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(pir,INPUT);
  pinMode(led,OUTPUT);
  
  pinMode(thermometer,INPUT);
  lcd.begin(16,2);
  analogReference(INTERNAL1V1);
  
  Serial.begin(9600);
  Serial.print("Enter Your Password:");
  pinMode(redled,OUTPUT);
  pinMode(greenled,OUTPUT);  
}

void loop()
{
  int Flame = digitalRead(flamepin);
  
  int Sensor= digitalRead(pir);
  
  float C=analogRead(thermometer);
  C=C*1100/(1024*10);
  
  char  key=x.getKey();
  
  if(key)
  {
    password[i]=key;
    i++;
    Serial.print("*");
    if(i==4)
    {
      check();
    }    
  }
  
  
  if(C>31)
  {
    lcd.setCursor(4,0);
    lcd.print("TEMP:");
    lcd.setCursor(10,0);
    lcd.print(int(C));
    lcd.setCursor(13,0);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print("Yuksek Sicaklik"); 
  }
  else if(C<20)
  {
    lcd.setCursor(4,0);
    lcd.print("TEMP:");
    lcd.setCursor(10,0);
    lcd.print(int(C));
    lcd.setCursor(13,0);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print("Dusuk Sicaklik");  
  }
  else
  {
    lcd.setCursor(4,0);
    lcd.print("TEMP:");
    lcd.setCursor(10,0);
    lcd.print(int(C));
    lcd.setCursor(13,0);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print("               ");
  }
  
  
  if(Sensor==HIGH)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  
  
  if(Flame==HIGH)
  {
    digitalWrite(buzzer,HIGH);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }
   
}  

int check()
{
   if( password[0]==P[0] && password[1]==P[1] && password[2]==P[2] && password[3]==P[3] )
   {
     Serial.println("");
     Serial.print("CORRECT PASSWORD");
     digitalWrite(greenled,HIGH); 
   }
   else
   {
     Serial.println("");
     Serial.println("WRONG PASSWORD");
     digitalWrite(redled,HIGH);  
   }  
}
