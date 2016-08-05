//------------------------------------------------------------------------------
// Arduino with RFID-reader (125 kHz) on software UART
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
//------------------------------------------------------------------------------
#define RX_PIN 5 // Arduino RX pin (connect it with TX pin of RFID-reader)
#define TX_PIN 6 // Arduino TX pin (connect it with RX pin of RFID-reader)
#define DEBUG  1 // Enable or disable (1/0) debug information output
//------------------------------------------------------------------------------
SoftwareSerial RFID = SoftwareSerial(RX_PIN, TX_PIN);
//------------------------------------------------------------------------------
char c;                       // Current character readable ID
String msg;                   // String to get current card ID
String ids = "740027389CF7";  // String to store allowed cards
//------------------------------------------------------------------------------
void setup()  
{
  Serial.begin(9600);             // Setup COM-port (hardware UART) with PC
  Serial.println("Serial Ready"); // Send (print) status to PC
  RFID.begin(9600);               // Setup COM-port with RFID-reader
  Serial.println("RFID Ready");   // Hah, we will send ALL our info to PC 
}
//------------------------------------------------------------------------------
void loop() 
{  
  msg = "";
  while (RFID.available() > 0) { // While RFID send some data
    c = RFID.read();             // Read next character
    msg += c;                    // Add it to all string of ID
    delay(10);                   // (!) Too long or too short delay
  }                              //     makes reading incorrectly!  
  msg = msg.substring(1,13);     // Remove the odd symbols (SoT, EoT)
  if (msg.length() > 11)         // Don't allow invalid IDs
    verificate();                // Check card ID with our storage
}
//------------------------------------------------------------------------------
void verificate() 
{
  if (DEBUG) Serial.println(msg);      // Print card ID to PC [DEBUG]
  if (ids.indexOf(msg) >= 0)           // If ID exist in storage then index
    Serial.println("Access granted."); // position of msg in ids always >= 0
  else                                 // Only if ID doesn't exist in storage
    Serial.println("Access denied.");  // then ids.indexOf(msg) return -1
}
//------------------------------------------------------------------------------
//                                                       By SnipGhost 05.08.2016
//------------------------------------------------------------------------------
