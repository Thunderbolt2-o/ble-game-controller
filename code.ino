#include <Wire.h>
#include <BleKeyboard.h>

#define BUTTON_PIN 19

BleKeyboard bleKeyboard;
// MMA8452Q I2C address is 0x1C(28)
#define Addr 0x1C
 
void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Initialise I2C communication as MASTER
  Wire.begin();
  bleKeyboard.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
 
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x2A);
  // StandBy mode
  Wire.write((byte)0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
 
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x2A);
  // Active mode
  Wire.write(0x01);
  // Stop I2C Transmission
  Wire.endTransmission();
 
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x0E);
  // Set range to +/- 2g
  Wire.write((byte)0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}
 
void loop()
{
  unsigned int data[7];
 
  // Request 7 bytes of data
//  Wire.requestFrom(Addr, 7);
// 
//  // Read 7 bytes of data
//  // staus, xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
//  if(Wire.available() == 7) 
//  {
//    data[0] = Wire.read();
//    data[1] = Wire.read();
//    data[2] = Wire.read();
//    data[3] = Wire.read();
//    data[4] = Wire.read();
//    data[5] = Wire.read();
//    data[6] = Wire.read();
//  }
// 
//  // Convert the data to 12-bits
//  int xAccl = ((data[1] * 256) + data[2]) / 16;
//  if (xAccl > 2047)
//  {
//    xAccl -= 4096;
//  }
// 
//  int yAccl = ((data[3] * 256) + data[4]) / 16;
//  if (yAccl > 2047)
//  {
//    yAccl -= 4096;
//  }
// 
//  int zAccl = ((data[5] * 256) + data[6]) / 16;
//  if (zAccl > 2047)
//  {
//    zAccl -= 4096;
//  }
// 
//  // Output data to serial monitor
//  Serial.print(xAccl);
//  Serial.print(" "); 
//  Serial.print(yAccl);
//  Serial.print(" ");
//  Serial.print(zAccl);
//  Serial.print("\n");
//  delay(500);

  if(bleKeyboard.isConnected()) {
    int currentState;  
    currentState = digitalRead(BUTTON_PIN);
    if(currentState == LOW){
      Wire.requestFrom(Addr, 7);
 
  // Read 7 bytes of data
  // staus, xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
  if(Wire.available() == 7) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
  }
 
  // Convert the data to 12-bits
  int xAccl = ((data[1] * 256) + data[2]) / 16;
  if (xAccl > 2047)
  {
    xAccl -= 4096;
  }
 
  int yAccl = ((data[3] * 256) + data[4]) / 16;
  if (yAccl > 2047)
  {
    yAccl -= 4096;
  }
 
  int zAccl = ((data[5] * 256) + data[6]) / 16;
  if (zAccl > 2047)
  {
    zAccl -= 4096;
  }
 
  // Output data to serial monitor
  Serial.print(xAccl);
  Serial.print(" "); 
  Serial.print(yAccl);
  Serial.print(" ");
  Serial.print(zAccl);
  Serial.print("\n");

   if(yAccl > 100 && yAccl < 1000){
     // bleKeyboard.press(KEY_UP_ARROW);
     bleKeyboard.press('s');
      bleKeyboard.releaseAll();
      Serial.print("s ");
    }
    if(yAccl < -300){
     // bleKeyboard.press(KEY_DOWN_ARROW);
     bleKeyboard.press('w');
      bleKeyboard.releaseAll();
      Serial.print("w ");
    }
    
    if(xAccl < -100){
      // bleKeyboard.press(KEY_LEFT_ARROW);
     bleKeyboard.press('d');
      bleKeyboard.releaseAll();
      Serial.print("d ");
    }
    if(xAccl > 100){
     // bleKeyboard.press(KEY_RIGHT_ARROW);
      bleKeyboard.press('a');
      bleKeyboard.releaseAll();
      Serial.print("a ");
    }

  }else{
    Serial.println("Oh something bad happend");
  }
  Serial.println("");
    }
}
