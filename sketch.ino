#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

#define DHTPIN 7
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
Servo pintu;

const int buttonPin = 2;
const int ledHijau = 8;
const int ledMerah = 9;
const int buzzer = 10;

int totalOrang = 0;
int totalDemam = 0;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();

  pintu.attach(6);
  pintu.write(0);

  lcd.setCursor(0, 0);
  lcd.print("AUTO SCREENING");
  lcd.setCursor(0, 1);
  lcd.print("READY...");
  delay(2000);
  lcd.clear();
}

void printResult(float suhu, const char* status, const char* akses) {
  Serial.println("===== HASIL PEMERIKSAAN =====");
  Serial.print("Suhu        : "); Serial.print(suhu); Serial.println(" C");
  Serial.print("Status      : "); Serial.println(status);
  Serial.print("Akses       : "); Serial.println(akses);
  Serial.print("Total Orang : "); Serial.println(totalOrang);
  Serial.print("Total Demam : "); Serial.println(totalDemam);
  Serial.println("============================");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    float suhu = dht.readTemperature();
    totalOrang++;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Suhu:");
    lcd.print(suhu, 1);
    lcd.print("C");

    if (suhu > 37.0) {            // fever: lock gate, alarm on
      totalDemam++;
      digitalWrite(ledMerah, HIGH);
      digitalWrite(ledHijau, LOW);
      tone(buzzer, 1000);
      pintu.write(0);
      lcd.setCursor(0, 1);
      lcd.print("AKSES KUNCI");
      printResult(suhu, "DEMAM", "TERKUNCI");
      delay(3000);
      noTone(buzzer);
    } else {                      // normal: open gate
      digitalWrite(ledHijau, HIGH);
      digitalWrite(ledMerah, LOW);
      noTone(buzzer);
      lcd.setCursor(0, 1);
      lcd.print("AKSES BUKA");
      pintu.write(90);
      printResult(suhu, "NORMAL", "TERBUKA");
      delay(5000);
      pintu.write(0);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Total:");
    lcd.print(totalOrang);
    lcd.setCursor(0, 1);
    lcd.print("Demam:");
    lcd.print(totalDemam);
    delay(3000);

    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, LOW);
    lcd.clear();
    lcd.print("READY...");
  }
  lastButtonState = buttonState;
}
