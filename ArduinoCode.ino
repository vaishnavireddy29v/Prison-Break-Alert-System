#include <SPI.h>
#include <MFRC522.h>
int buz = 4;
int led = 16;
constexpr uint8_t RST_PIN = 0;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 2;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;
void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(15, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
}
void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 6; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "1791592141100") {
      Serial.println("Access Granted!");
      digitalWrite(15, HIGH);
      delay(100);
      digitalWrite(15, LOW);
      delay(100);
      digitalWrite(15, HIGH);
      delay(100);
      digitalWrite(15, LOW);
      delay(100);
      digitalWrite(15, HIGH);
      delay(100);
      digitalWrite(15, LOW);
      delay(100);
    } else {
      Serial.println("Access Denied!");
      digitalWrite(15, HIGH);
      digitalWrite(buz, HIGH);
      digitalWrite(led, HIGH); 
      delay(5000);
      digitalWrite(15, LOW);
      digitalWrite(buz, LOW);
      digitalWrite(led, LOW);
     
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
} 
