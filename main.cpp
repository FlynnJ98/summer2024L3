#include "mbed.h"
#include "LSM6DSLSensor.h"
#include <cmath>

/* 
This program will read the values of x, y & z on the accelerometer and calculate the pitch angle of the
Mbed based on calculations provided for this lab. This program only calculates the pitch angle as the compute angle function.
LSM6DSL sensor is on the mbed board. This is the sensor giving us the data. 
*/

#define PI 3.141592654 // defines the value of PI so it can be called easier within the code. 

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address

float computeAngle(float accX, float accY, float accZ){
  float pitch = atan2f(-accX, sqrtf(accY * accY + accZ * accZ)); // included a minus before accX because at 0.00 it was printing a minus on the screen. 
  pitch = pitch * (180 / PI); // Convert from radians to degrees 
  return pitch; // returns the pitch as a floating number
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL); // initialising the gyroscope. 

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) { // while value is 1, execute what is within this loop.
//convert values to float values
        float accX = (float)axes[0];
        float accY = (float)axes[1];
        float accZ = (float)axes[2];

        acc_gyro.get_x_axes(axes); // gets the gyroscope to find the axes values from the center. 
        res = computeAngle(axes[0], axes[1], axes[2]); // computing the angle
            printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res); // prints the values of the sensor. 
            thread_sleep_for(1000); // sleep for 1 second. 
        float pitch = computeAngle(accX, accY, accZ); // compute the angle pitch
            printf("AccX: %f, AccY: %f, AccZ: %f\r\n", accX, accY, accZ); // get values for X, Y, Z and print on screen. 
            printf("Pitch Angle: %f degrees\r\n", pitch); // print pitch angle based on the calculation. 
        ThisThread::sleep_for(2500ms); // sleep for 2.5 seconds before printing again. 
    }
}