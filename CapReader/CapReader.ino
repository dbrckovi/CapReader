#include <LiquidCrystal.h>

const float R1 = 1000.0;
const float R2 = 1000000.0;
const float R3 = 10000000.0;

const int CHARGE_VALUE = 647;     // (647 is 63.2% of 1023)
const int MAX_INITIAL_VOLTAGE = 3;
const int BUTTON = 2;
const int CHARGE1 = 3;  //1k
const int CHARGE2 = 4;  //1M
const int CHARGE3 = 5;  //10M
const int DISCHARGE = 8;
const int rs = 6, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(CHARGE1, INPUT);
  pinMode(CHARGE2, INPUT);
  pinMode(CHARGE3, INPUT);
  pinMode(DISCHARGE, OUTPUT);

  digitalWrite(DISCHARGE, LOW);
  lcd.begin(16, 2);
  PrintLine(0, "Ready");
}

void loop() 
{
  if(digitalRead(BUTTON) == HIGH) 
  {
    Measure();
    PrintLine(0, "Ready");
  }
}

void Measure()
{
  PrintLine(0, "Measuring...");
  PrintLine(1, " ");

  unsigned long elapsed = 0;
  float R;

  Discharge();
  R = R1;
  elapsed = ChargeAndWait(CHARGE1);

  if (elapsed < 1000)
  {
    Discharge();
    R = R2;
    elapsed = ChargeAndWait(CHARGE2);
  }

  if (elapsed < 1000)
  {
    Discharge();
    R = R3;
    elapsed = ChargeAndWait(CHARGE3);
  }

  Discharge();

  if (elapsed > 1000) PrintLine(0, "Finished");
  else PrintLine(0, "Not sure");

  PrintCapacitance(elapsed, R);

  while(digitalRead(BUTTON) == HIGH) {}
}

void Discharge()
{
  digitalWrite(DISCHARGE, HIGH);
  
  while(true)
  {
    if (analogRead(A5) <= MAX_INITIAL_VOLTAGE) break;
    if (digitalRead(BUTTON) == LOW) break;
  }
  digitalWrite(DISCHARGE, LOW);
}

unsigned long ChargeAndWait(int pinNumber)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, HIGH);
  unsigned long start_time = micros();
  unsigned long elapsed = 0;
  
  while (digitalRead(BUTTON) == HIGH)
  {
    if (analogRead(A5) > CHARGE_VALUE) 
    {
      elapsed = micros() - start_time;
      break;
    }
  }
  digitalWrite(pinNumber, LOW);
  pinMode(pinNumber, INPUT);
  return elapsed;
}

void PrintVoltage(int voltage)
{
    String strVoltage = String(voltage);
    PrintLine(1, strVoltage);
}

void PrintCapacitance(unsigned long elapsedMillis, float R)
{
  double seconds = (double)elapsedMillis / 1000000.0;
  double fahrads = seconds / R;
  double milliFahrads = fahrads * 1000.0;
  double microFahrads = milliFahrads * 1000.0;
  double nanoFahrads = microFahrads * 1000.0;
  double picoFahrads = nanoFahrads * 1000.0;

  String out;
  
  if (fahrads > 1.0) out = String(fahrads) + " F";
  else if (milliFahrads > 1.0) out = String(milliFahrads) + " mF";
  else if (microFahrads > 1.0) out = String(microFahrads) + " uF";
  else if (nanoFahrads > 1.0) out = String(nanoFahrads) + " nF";
  else if (picoFahrads > 1.0) out = String(picoFahrads) + " pF";
  
  PrintLine(1, out);
}

void PrintLine(int line, String text)
{
    while (text.length() < 16)
    {
      text += ' ';
    }
  
    lcd.setCursor(0, line);
    lcd.print(text);
}
