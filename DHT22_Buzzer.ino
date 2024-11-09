#include <DHT.h>

// Pin Definitions
#define DHT11_PIN 9        // Pin connected to the DHT22 sensor
#define BUZZER_PIN 4       // Pin connected to the buzzer
#define GREEN_LED_PIN 5    // Pin connected to the green LED

// DHT Sensor Configuration
#define DHTTYPE DHT11      // Change this to DHT11 if you're using a DHT11 sensor
DHT dht(DHT11_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  dht.begin(); // Initialize the DHT sensor

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Ensure all outputs are initially off
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {
  delay(2000); // Delay between sensor readings

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  // Check if the readings are valid
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  // Display the readings on the serial monitor
  Serial.print("DHT11# Humidity: ");
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
