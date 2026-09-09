# Self_Watering
An automated watering system built on an Arduino, using two analog moisture sensors and a relay-controlled pump.
The system averages readings from both sensors and activates the pump for a fixed 10-second interval when the average value exceeds a set threshold. Once triggered, the system enters a 48-hour lockout period before it will activate the pump again, preventing repeated triggering from a single moisture reading. Sensor values and system state are logged to serial output for monitoring

Arduino Uno
