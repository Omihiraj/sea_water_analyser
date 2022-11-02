#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);


//pH Variables..............
float calibration_value = 21.34;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;
//..........................
void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  tempMeasure();
  pHMeasure();
  delay(3000);
}

void tempMeasure() {
  sensors.requestTemperatures(); //initialize request
  float temperatureC = sensors.getTempCByIndex(0);//This Function can mesure Celcius
  float temperatureF = sensors.getTempFByIndex(0);//This Function can mesure Faranhitee
  Serial.print("Temp : ");
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print("Temp : ");
  Serial.print(temperatureF);
  Serial.println("ºF");
}

void pHMeasure() {
  for (int i = 0; i < 10; i++)
  {
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = (-5.70 * volt + calibration_value)*-1;
  Serial.print("pH Val:");
  Serial.println(ph_act);
}
