// Using ABP for now.
//#define OTAA

#ifndef LORA_TTNMAPPER_TBEAM_CONFIG_INCLUDED
#define LORA_TTNMAPPER_TBEAM_CONFIG_INCLUDED

#define CFG_eu868 1

#ifndef OTAA
// UPDATE WITH YOUR TTN KEYS AND ADDR.
// Setting for ABP
static PROGMEM u1_t NWKSKEY[16] = { 0x17, 0x43, 0x91, 0xC6, 0xB4, 0xDC, 0xE1, 0x91, 0x3D, 0xBF, 0xEF, 0x0E, 0xD1, 0xF5, 0xB0, 0xB2 }; // LoRaWAN NwkSKey, network session key 
static u1_t PROGMEM APPSKEY[16] = { 0xB0, 0xFB, 0x5B, 0xE7, 0x5C, 0x20, 0x6B, 0x79, 0xEF, 0x5C, 0xB5, 0x51, 0x4C, 0xDF, 0xBE, 0xD6 }; // LoRaWAN AppSKey, application session key 
static const u4_t DEVADDR = 0x260B08DB; // LoRaWAN end-device address (DevAddr)
#else
// Settings from OTAA device
static const u1_t PROGMEM DEVEUI[8]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } ; // Device EUI, hex, lsb
static const u1_t PROGMEM APPEUI[8]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // Application EUI, hex, lsb
static const u1_t PROGMEM APPKEY[16] = { 0x12, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23, 0x45, 0x67, 0x89, 0x01 }; // App Key, hex, msb

void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}
#endif

#endif //LORA_TTNMAPPER_TBEAM_CONFIG_INCLUDED
