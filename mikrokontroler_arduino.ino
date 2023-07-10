#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool pumpStatus = true ;  // Status pompa air (mati awalnya)

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
  lcd.print("");
  delay(3000);
  lcd.clear();
  pinMode(13,OUTPUT);
}

void loop() { 
  // Baca data dari Bluetooth
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == '0')
    {
      digitalWrite(13,HIGH);
      pumpStatus = true;
    }
    else if(data == '1')
    {
      digitalWrite(13,LOW);
      pumpStatus = false;
    }
  }

  // Tampilkan status pompa air di LCD
  lcd.setCursor(0, 0);
  if (pumpStatus) {
    digitalWrite(2, LOW);  
    lcd.print("POMPA AIR = OFF ");
  } else{
    digitalWrite(2, HIGH);  
    lcd.print("POMPA AIR = ON ");
  }
  
  int value = analogRead(A0);
  Serial.println(value);

  // Tampilkan status kelembaban tanah di LCD
  lcd.setCursor(0, 1);
  if (value < 500) {
    lcd.print("Status : BASAH");
  } else if (value > 500 && value < 800) {
    lcd.print("Status : NORMAL ");
  } else if (value > 800) {
    lcd.print("Status : KERING ");
  }
}