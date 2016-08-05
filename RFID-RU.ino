//------------------------------------------------------------------------------
// Arduino и RFID-сканер (125 кГц) на программном UART
//------------------------------------------------------------------------------
#include <SoftwareSerial.h>
//------------------------------------------------------------------------------
#define RX_PIN 5 // Arduino RX пин (соединить с TX пином RFID-сканера)
#define TX_PIN 6 // Arduino TX пин (соединить с RX пином RFID-сканера)
#define DEBUG  1 // Включает или отключает (1/0) вывод отладочной информации
//------------------------------------------------------------------------------
SoftwareSerial RFID = SoftwareSerial(RX_PIN, TX_PIN);
//------------------------------------------------------------------------------
char c;                       // Текущий символ считываемого ID
String msg;                   // Строка для получения всего текущего ID
String ids = "740027389CF7";  // Строка для хранения разрешенных ID
//------------------------------------------------------------------------------
void setup()  
{
  Serial.begin(9600);             // Установка COM-порта (hardware UART) с ПК
  Serial.println("Serial Ready"); // Отправка (печать) статуса на ПК
  RFID.begin(9600);               // Установка COM-порта с RFID-сканером
  Serial.println("RFID Ready");   // Хах, мы будем отправлять ВСЕ данные на ПК
}
//------------------------------------------------------------------------------
void loop() 
{  
  msg = "";
  while (RFID.available() > 0) { // Покуда RFID-сканер шлет данные
    c = RFID.read();             // Считываем следующий символ ID
    msg += c;                    // Добавляем его к общей строке с ID
    delay(10);                   // (!) Слишком длинная или короткая задержка
  }                              //     приводит к некорректному считыванию!  
  msg = msg.substring(1,13);     // Удаляем ненужные символы (SoT, EoT)
  if (msg.length() > 11)         // Не разрешаем проверять поврежденные ID
    verificate();                // Сверяем ID карты с нашим хранилищем
}
//------------------------------------------------------------------------------
void verificate() 
{
  if (DEBUG) Serial.println(msg);      // Печатаем ID карты на ПК [DEBUG]
  if (ids.indexOf(msg) >= 0)           // Если ID есть в хранилище, то
    Serial.println("Access granted."); // позиция msg в нем всегда >= 0
  else                                 // И только если ID нет в хранилище,
    Serial.println("Access denied.");  // то ids.indexOf(msg) вернет -1
}
//------------------------------------------------------------------------------
//                                                       By SnipGhost 05.08.2016
//------------------------------------------------------------------------------