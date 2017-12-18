#include <Wire.h>
#include <I2Cdev.h>
#include <LSM303DLHC.h>
#include <L3GD20H.h>

LSM303DLHC accelMag;
L3GD20H gyro;

// Accelerometer
int16_t ax, ay, az;
// Magenetometer
int16_t mx, my, mz; 
// Gyroscope
int16_t avx, avy, avz;


#define LED_PIN 13 // (Arduino is 13, Teensy is 6)
bool blinkState = false;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Initializing I2C devices...");
    gyro.initialize();
    accelMag.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(gyro.testConnection() ? "L3GD20H connection successful" : "L3GD20H connection failed");
    Serial.println(accelMag.testConnection() ? "LSM303DLHC connection successful" : "LSM303DLHC connection failed");


// LSM303DLHC Testing
    // set scale to 2Gs
    accelMag.setAccelFullScale(2);
    // set accel data rate to 200Hz
    accelMag.setAccelOutputDataRate(200);
    Serial.print("Accel Scale: ");
    Serial.println(accelMag.getAccelFullScale());
    Serial.print("Accel Output Data Rate: ");
    Serial.println(accelMag.getAccelOutputDataRate());
    accelMag.setMagOutputDataRate(220);                   // set mag data rate to 220Hz
    Serial.print("Mag Output Data Rate: ");
    Serial.println(accelMag.getMagOutputDataRate());
    accelMag.setMagGain(1100);                            //set mag gain to 1100
    Serial.print("Mag Gain: ");
    Serial.println(accelMag.getMagGain());
    accelMag.setMagMode(LSM303DLHC_MD_CONTINUOUS);        // Enable mag
    Serial.println(accelMag.getMagMode());

// LSGD20H Testing

    // set scale to 250
    gyro.setFullScale(250);


}

void loop() {
    Serial.flush();
    // read raw angular velocity measurements from device
    gyro.getAngularVelocity(&avx, &avy, &avz);
    accelMag.getAcceleration(&ax, &ay, &az);
    accelMag.getMag(&mx, &my, &mz);


    //Serial.print("Acceleration:\t");
    Serial.print(ax*0.0000625F,4); Serial.print(" ");
    Serial.print(ay*0.0000625F,4); Serial.print(" ");
    Serial.print(az*0.0000625F,4); Serial.print(";");

    //Serial.print("  Magnetic Field:\t");
    Serial.print(mx); Serial.print(" ");
    Serial.print(my); Serial.print(" ");
    Serial.print(mz); Serial.print(";");

    //Serial.print("angular velocity (dps):\t");
    Serial.print(avx*0.00875F,DEC); Serial.print(" ");
    Serial.print(avy*0.00875F,DEC); Serial.print(" ");
    Serial.println(avz*0.00875F,DEC); //Serial.print("");


   // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);

   delay(100);
}
