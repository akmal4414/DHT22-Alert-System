#include <DHT.h>


#define DHT22_PIN 9      
#define BUZZER_PIN 4      
#define GREEN_LED_PIN 5    

/
#define DHTTYPE DHT22      // Change this to DHT11 if you're using a DHT11 sensor
DHT dht(DHT22_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  dht.begin(); 

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);


  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {
  delay(2000); 

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  // Check if the readings are valid or okay
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  // Display the readings on the serial monitor
  Serial.print("DHT22# Humidity: ");
  Serial.print(humidity);
  Serial.print("%   ||  Temperature: ");
  Serial.print(tempC);
  Serial.print("°C ~ ");
  Serial.print(tempF);
  Serial.println("°F");
  Serial.println("= = = = = = = = = = = = = = = = = = = = = = = = = = = = =");

  // Temperature threshold check
  if (tempC >= 28.0) {
    // If temperature is too high, turn off green LED and activate buzzer
    digitalWrite(GREEN_LED_PIN, LOW);

    // Buzzer beeps 3 times
    for (int i = 0; i < 5; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Buzzer TURN ON!!!   ||  HIGH TEMPERATURE!!");
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
  } else {
    // If temperature is normal, keep the green LED on
    digitalWrite(GREEN_LED_PIN, HIGH);
    Serial.println("Temperature is normal.");
  }
}
