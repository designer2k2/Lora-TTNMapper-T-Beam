#include "gps.h"

HardwareSerial GPSSerial(1);

void gps::init() {
  GPSSerial.setRxBufferSize(2048);  // Default is 256
  GPSSerial.begin(115200, SERIAL_8N1, GPS_TX, GPS_RX);
  GPSSerial.setTimeout(2);

  // CFG-PRT to 115200 Baudrate
  byte packet[] = {
    0xB5,  // sync char 1
    0x62,  // sync char 2
    0x06,  // class
    0x00,  // id
    0x14,  // length
    0x00,  //
    0x01,  // payload
    0x00,  // payload
    0x00,  // payload
    0x00,  // payload
    0xD0,  // payload
    0x08,  // payload
    0x00,  // payload
    0x00,  // payload
    0x00,  // payload
    0xC2,  // payload
    0x01,  // payload
    0x00,  // payload
    0x07,  // payload
    0x00,  // payload
    0x03,  // payload
    0x00,  // payload
    0x00,  // payload
    0x00,  // payload
    0x00,  // payload
    0x00,  // payload

    0xC0,  // CK_A
    0x7E,  // CK_B
  };

  for (byte i = 0; i < sizeof(packet); i++)
  {
    //GPSSerial.write(packet[i]);
  }

  //delay(100);
  //GPSSerial.flush();
  //GPSSerial.updateBaudRate(115200);
}

void gps::encode() {
  int data;
  unsigned long previousMillis = millis();

  while ((previousMillis + 100) > millis()) {
    while (GPSSerial.available()) {
      char data = GPSSerial.read();
      tGps.encode(data);
      //Serial.print(data);
    }
  }
  //Serial.println("");
}

void gps::buildPacket(uint8_t txBuffer[9]) {
  LatitudeBinary = ((tGps.location.lat() + 90) / 180.0) * 16777215;
  LongitudeBinary = ((tGps.location.lng() + 180) / 360.0) * 16777215;

  sprintf(t, "Lat: %f", tGps.location.lat());
  Serial.println(t);

  sprintf(t, "Lng: %f", tGps.location.lng());
  Serial.println(t);

  txBuffer[0] = (LatitudeBinary >> 16) & 0xFF;
  txBuffer[1] = (LatitudeBinary >> 8) & 0xFF;
  txBuffer[2] = LatitudeBinary & 0xFF;

  txBuffer[3] = (LongitudeBinary >> 16) & 0xFF;
  txBuffer[4] = (LongitudeBinary >> 8) & 0xFF;
  txBuffer[5] = LongitudeBinary & 0xFF;

  altitudeGps = tGps.altitude.meters();
  txBuffer[6] = (altitudeGps >> 8) & 0xFF;
  txBuffer[7] = altitudeGps & 0xFF;

  hdopGps = tGps.hdop.value() / 10;
  txBuffer[8] = hdopGps & 0xFF;
}

void gps::gdisplay(uint16_t txBuffer2[5]) {
  txBuffer2[0] = tGps.satellites.value();
  txBuffer2[1] = tGps.speed.kmph();
  txBuffer2[2] = tGps.course.deg();
  txBuffer2[3] = tGps.altitude.meters();
  txBuffer2[4] = tGps.hdop.value() / 10;
}

bool gps::checkGpsFix() {
  encode();
  if (tGps.location.isValid() && tGps.location.age() < 4000 && tGps.hdop.isValid() && tGps.hdop.value() <= 600 && tGps.hdop.age() < 4000 && tGps.altitude.isValid() && tGps.altitude.age() < 4000) {
    Serial.println("Valid gps Fix.");
    return true;
  } else {
    Serial.print("No gps Fix. ");
    Serial.print(tGps.failedChecksum());
    Serial.print(" Failed Checksums, ");
    Serial.print(tGps.charsProcessed());
    Serial.println(" Chars Ok");
    return false;
  }
}
