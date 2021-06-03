#include <Wire.h>
TwoWire WIRE2(2,I2C_FAST_MODE);
#define Wire WIRE2
int16_t Gyro_X, Gyro_Y, Gyro_Z;
void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(57600);
    Wire.setClock(400000); // set I2C clock speed to 400kHz
    Wire.begin();
    delay(250); //wait for gyro to start

    Wire.beginTransmission(0x68); //0x68 is adderess of MPU 6050
    Wire.write(0x6B); //write to power managment register
    Wire.write(0x00); //wake up gyro
    Wire.endTransmission();
}

void loop() 
{
  // put your main code here, to run repeatedly:
    Wire.beginTransmission(0x68);
    Wire.write(0x43); //tell mpu that we will be reading from 0x43 register
    Wire.endTransmission();

    Wire.requestFrom(0x68, 6); // request 6 bytes from mpu
    //As per data sheet Gyro valuse are store in 2's complement form in MPU we can retrive as this
    Gyro_X = Wire.read() << 8 | Wire.read(); //shigh high 8 bits left and add low and high byte to Gyro_X;
    Gyro_Y = Wire.read() << 8 | Wire.read();
    Gyro_Z = Wire.read() << 8 | Wire.read();

    Serial.print("X = ");
    Serial.print(Gyro_X);
    Serial.print("  Y = ");
    Serial.print(Gyro_Y);
    Serial.print("  Z = ");
    Serial.print(Gyro_Z);
    Serial.println();
    delay(250);
}
