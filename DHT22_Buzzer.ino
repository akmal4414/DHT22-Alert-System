#include <DHT11.h>

#define DHT11_PIN 9         // Pin connected to the DHT11 sensor
#define BUZZER_PIN 4        // Pin connected to the buzzer
#define GREEN_LED_PIN 5     // Pin connected to the green LED

DHT11 dht11(DHT11_PIN);     // Initialize DHT11 object

void setup() {
  Serial.begin(115200);

  // Set the pin modes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Turn off the buzzer and LED initially
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {
  delay(2000); // Wait 2 seconds between readings

  // Create variables to store humidity and temperature readings
  int humidity = 0;
  int tempC = 0;
  
  // Read humidity and temperature from DHT11 sensor
  int chk = dht11.read(DHT11_PIN, &tempC, &humidity);

  // Check if the readings are valid
  if (chk != DHTLIB_OK) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  // Display the readings on the serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%   ||  Temperature: ");
  Serial.print(tempC);
  Serial.println("°C");
  Serial.println("================================");

  // Temperature threshold check
  if (tempC >= 28) {
    // If temperature is too high, turn off green LED and activate buzzer
    digitalWrite(GREEN_LED_PIN, LOW);

    // Buzzer beeps 3 times
    for (int i = 0; i < 3; i++) {
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
