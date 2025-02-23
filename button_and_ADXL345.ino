#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

#define BUTTON_PIN 19
#define SENSITIVITY_THRESHOLD 17 // Adjust for soil conditions
#define SCALE_FACTOR 10            // Distance scaling (calibrate if needed)

int humanCount = 0;
bool buttonPressed = false;

void setup() {
  Serial.begin(115200);

  // Initialize ADXL345
  if (!accel.begin()) {
    Serial.println("❌ ADXL345 not detected. Check connections!");
    while (1);
  }

  // Set Medium Data Rate & Normal Sensitivity
  accel.setRange(ADXL345_RANGE_16_G); // Wider range for soil movement
  setDataRate(ADXL345_DATARATE_100_HZ); // Medium rate (100 Hz)

  Serial.println("✅ ADXL345 Initialized in Medium Rate");

  // Initialize Push Button
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Internal pull-up used
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  // Calculate total vibration intensity
  float totalMovement = sqrt(
    pow(event.acceleration.x, 2) +
    pow(event.acceleration.y, 2) +
    pow(event.acceleration.z - 9.81, 2) // Subtract gravity
  );

  Serial.print("Movement: ");
  Serial.println(totalMovement, 3);

  // Detect significant movement
  if (totalMovement > SENSITIVITY_THRESHOLD) {
    Serial.println("⚠️ Possible Human Movement Detected. Press Button to Confirm.");

    // Estimate Distance (Inverse proportional to intensity)
    float estimatedDistance = (1 / totalMovement) * SCALE_FACTOR;
    Serial.print("📏 Estimated Distance: ");
    Serial.print(estimatedDistance, 2);
    Serial.println(" meters");

    // Wait for button press to confirm
    if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
      buttonPressed = true;
      humanCount++;

      Serial.println("✅ Human Detection Confirmed!");
      Serial.print("👤 Total Persons Detected: ");
      Serial.println(humanCount);
      Serial.print("🔎 Final Distance: ");
      Serial.print(estimatedDistance, 2);
      Serial.println(" meters");

      delay(500); // Debounce delay
    }
  }

  // Reset button press flag after release
  if (digitalRead(BUTTON_PIN) == HIGH && buttonPressed) {
    buttonPressed = false;
  }

  delay(100); // Short delay between reads
}

void setDataRate(uint8_t dataRate) {
  Wire.beginTransmission(0x53); // ADXL345 I2C address
  Wire.write(0x2C);             // BW_RATE register
  Wire.write(dataRate);         // Set data rate
  Wire.endTransmission();
}
