#include "mbed.h"
#include "LSM6DSLSensor.h"
#include <cmath>

#define PI 3.141592654

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address

float computeAngle(float accX, float accY, float accZ){
  float pitch = atan2f(-accX, sqrtf(accY * accY + accZ * accZ));
  pitch = pitch * (180 / PI);
  return pitch;
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {
        float accX = (float)axes[0];
        float accY = (float)axes[1];
        float accZ = (float)axes[2];

        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
            printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res);
            thread_sleep_for(1000);
        float pitch = computeAngle(accX, accY, accZ);
            printf("AccX: %f, AccY: %f, AccZ: %f\r\n", accX, accY, accZ);
            printf("Pitch Angle: %f degrees\r\n", pitch);
        ThisThread::sleep_for(2500ms);
    }
}