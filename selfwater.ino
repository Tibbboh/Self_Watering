// this is a reocnstruction of teh oginal code and has not been tested with hardware

// Pin assignments
const int moistureSensor1 = A0; // First moisture sensor pin
const int moistureSensor2 = A1; // Second moisture sensor pin
const int relayPin = 7;          // Relay control pin

// Threshold set to 600
int threshold = 600;

// Timing variables
unsigned long motorRunDuration = 10000; // 10 seconds for motor
unsigned long twoDays = 172800000; // 2 days in milliseconds
unsigned long oneDay = 86400000; // 1 day in milliseconds

unsigned long lastPumpTime = 0; // For tracking when the pump last ran
bool pumpActive = false; // Flag to track if the pump has been activated

void setup() {
  Serial.begin(9600);
  
  // Initialize the relay pin as OUTPUT
  pinMode(relayPin, OUTPUT);
  
  // Start with the relay off
  digitalWrite(relayPin, HIGH); // Ensure the pump is off at startup
}

void loop() {
  // Read moisture levels from both sensors
  int moistureValue1 = analogRead(moistureSensor1);
  int moistureValue2 = analogRead(moistureSensor2);
  
  // Calculate the average moisture value
  int averageMoisture = (moistureValue1 + moistureValue2) / 2;

  // Display individual and average moisture levels in the serial monitor
  Serial.print("Moisture Sensor 1: ");
  Serial.println(moistureValue1);
  Serial.print("Moisture Sensor 2: ");
  Serial.println(moistureValue2);
  Serial.print("Average Moisture: ");
  Serial.println(averageMoisture);
  
  // If the average moisture level is above the threshold (600)
  if (averageMoisture > threshold) {
    // Check if enough time has passed since the last pump activation
    if (!pumpActive) { // If the pump is not currently active
      digitalWrite(relayPin, LOW); // Activate the pump
      Serial.println("Pump activated for 10 seconds.");
      delay(motorRunDuration); // Run the pump for 10 seconds
      digitalWrite(relayPin, HIGH); // Deactivate the pump
      lastPumpTime = millis(); // Update the last pump time
      pumpActive = true; // Set the pump active flag
      Serial.println("Pump deactivated.");
    }
  }

  // If the pump has been activated, check if 2 days have passed
  if (pumpActive) {
    // Calculate the time since the last pump activation
    unsigned long elapsedTime = millis() - lastPumpTime;

    if (elapsedTime >= twoDays) {
      Serial.println("2 days passed, ready to check moisture levels again.");
      pumpActive = false; // Reset pump active flag
      Serial.println("Pump can activate again.");
    } else {
      // Calculate remaining time for 2 days
      unsigned long remainingTime = twoDays - elapsedTime;
      Serial.print("Time remaining until next activation: ");
      Serial.print(remainingTime / 1000); // Convert milliseconds to seconds
      Serial.println(" seconds.");
    }
  }

  // If the pump was not active for a full day, we can check again for the moisture level
  if (!pumpActive && (millis() - lastPumpTime >= oneDay)) {
    Serial.println("One day passed, checking moisture levels again.");
  }

  // Print out the last pump time for debugging
  Serial.print("Last Pump Time: ");
  Serial.println(lastPumpTime);

  // Wait for a short period before the next reading
  delay(1000); // Adjust the delay as needed
}
