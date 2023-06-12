//Libraries
#include <DHT.h>;
#include <LiquidCrystal.h>

//Constants
#define DHTPIN A3     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
LiquidCrystal lcd(7,8,9,10,11,12);//Create lcd object

//Variables
//DHT22
int chk;
float temp; //Stores temperature value

// LCD
boolean a=LOW,b=HIGH;

// Fan
int sensorPin = A0;
int PWM = 3;
int sensorVal;
int PWMVal;

void setup() {
  lcd.begin(16,2);        //Start lcd 
  lcd.setCursor(0,0);     //Set in position 0,0
  lcd.print("deg.C");
  pinMode(sensorPin, INPUT);
  pinMode(PWM, OUTPUT);
  Serial.begin(9600);
  dht.begin();

}

void loop() {
   delay(1000);
   
   //Read data and store it to variables temp
   temp= dht.readTemperature();
   
   //Print temp values to serial monitor
   Serial.print("  Temp: ");
   Serial.print(temp);
   Serial.println(" Celsius");
   Serial.println(sensorVal);
   lcd.setCursor(0,0);
   lcd.print("TempC: ");
   lcd.print(temp);
   delay(500);      //Delay 1 sec.
   lcd.clear();

   //read sensor value and set upper limit cap
   sensorVal = analogRead(sensorPin);
   if(sensorVal >800){
     sensorVal = 800;
  }

  //map and assign pwm values to the fan output 0 to 255 corresponds to 0 to 100%
  PWMVal = map(sensorVal, 450, 800, 30, 255);

  //set 450 as out cut out or cut in limit where the fan switches from off to the lower PWM limit
  if(sensorVal <450){
    PWMVal = 0;
  }

  //write the PWM value to the pwm output pin
  analogWrite(PWM, PWMVal);

   if(temp>=31 && a==LOW)//if temperature above of 25 degrees
   {
     digitalWrite(sensorPin,HIGH);  //Active fan
   }
   else if(temp<=29&&b==LOW)//if temperature is under 23 degrees
   {
     digitalWrite(sensorPin,LOW); //Turn off fan
   }
}
