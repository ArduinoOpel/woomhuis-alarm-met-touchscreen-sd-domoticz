#include "Nextion.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"


File myFile;
File myFile1;

RTC_DS1307 rtc;

#define Password_Lenght 5

unsigned long currentMillis;
unsigned long previousMillisA = 0;
unsigned long previousMillisB = 0;
unsigned long previousMillisC = 0;
int intervalA = 5000;
int intervalB = 20000;
unsigned long intervalC = 300000;
int interA;
int interB;
int interC;



char buffer[100] = {0};

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Martijn[Password_Lenght] = "";
char Sitske[Password_Lenght] = "";
char Gast[Password_Lenght] = "";
char Master[Password_Lenght] = "0000";
byte data_count = 0, martijn_count = 0;
bool Pass_is_good;
char customKey;
int key = 0;
char customKeyold;

bool Wacht = false;
bool Actief = false;
bool Alarm = false;
bool Alarmsent = false;

int zone = 0;
bool zoneok = false;
bool zone1 = LOW;
bool zone2 = LOW;
bool zone3 = LOW;
bool zone4 = LOW;
bool zone5 = LOW;
bool zone6 = LOW;
bool zone7 = LOW;
bool zone8 = LOW;
bool zone9 = LOW;
bool zone10 = LOW;
bool zone11 = LOW;
bool zone12 = LOW;
bool zone13 = LOW;
bool zone14 = LOW;
bool zone15 = LOW;
bool zone16 = LOW;
bool Sabo = LOW;

bool zone1old = HIGH;
bool zone2old = HIGH;
bool zone3old = HIGH;
bool zone4old = HIGH;
bool zone5old = HIGH;
bool zone6old = HIGH;
bool zone7old = HIGH;
bool zone8old = HIGH;
bool zone9old = HIGH;
bool zone10old = HIGH;
bool zone11old = HIGH;
bool zone12old = HIGH;
bool zone13old = HIGH;
bool zone14old = HIGH;
bool zone15old = HIGH;
bool zone16old = HIGH;
bool Saboold = HIGH;

bool Alarm_sent = false;

bool voordeur = false;
bool gang = false;
bool serial_sent = false;

int sabo_Pin = 38;

int hal_Pin = 37;
int voordeur_Pin = 36;
int woon_Pin = 35;
int achter_deur_Pin = 34;
int voor_raam_Pin = 33;
int garage_roldeur_Pin = 32;
int balkon_deur_Pin = 31;
int zij_raam_Pin = 30;
int slaap_raam_Pin = 22;
int hobby_raam_Pin = 23;
int garage_deur_Pin = 24;
int garage_deur_2_Pin = 25;
int keuken_Pin = 26;
int zone14_Pin = 27;
int zone15_pin = 28;
int zone16_Pin = 29;


int lamp_Pin = 40;
int sirene_Pin = 41;

int buzzerPin = 8;

int page = 0;
bool inbraak;
bool actief;
bool Aan;
bool timerA;
bool timerB;
bool timerC;
bool Melding = false;
bool t2_sent1 = true;
bool t2_sent2 = true;
bool page4sent;
bool sent_zone = false;

//////////////////////////////////////page 0
void t0PopCallback(void *ptr);
void t1PopCallback(void *ptr);
//void t2PopCallback(void *ptr);
void b0PopCallback(void *ptr);
void b1PopCallback(void *ptr);
void b2PopCallback(void *ptr);
void b3PopCallback(void *ptr);
void b4PopCallback(void *ptr);
void b5PopCallback(void *ptr);
void b6PopCallback(void *ptr);
void b7PopCallback(void *ptr);
void b8PopCallback(void *ptr);
void b9PopCallback(void *ptr);
void b0PopCallback(void *ptr);
void b10PopCallback(void *ptr);
void b11PopCallback(void *ptr);
void b12PopCallback(void *ptr);
/////////////////////////////////////page 1
void b20PopCallback(void *ptr);
void b21PopCallback(void *ptr);
void b22PopCallback(void *ptr);
///////////////////////////////////////page 2
void b30PopCallback(void *ptr);
void b31PopCallback(void *ptr);
void b32PopCallback(void *ptr);
void b33PopCallback(void *ptr);
void b34PopCallback(void *ptr);
void b35PopCallback(void *ptr);
void b36PopCallback(void *ptr);
///////////////////////////////////////page 3
void b40PopCallback(void *ptr);
void t40PopCallback(void *ptr);
void t41PopCallback(void *ptr);
void t42PopCallback(void *ptr);
void t43PopCallback(void *ptr);
void t44PopCallback(void *ptr);
void t45PopCallback(void *ptr);
void t46PopCallback(void *ptr);
void t47PopCallback(void *ptr);
void t48PopCallback(void *ptr);
void t49PopCallback(void *ptr);
///////////////////////////////////////page 4
void b50PopCallback(void *ptr);
void b51PopCallback(void *ptr);
void t51PopCallback(void *ptr);
void t52PopCallback(void *ptr);
void t53PopCallback(void *ptr);
void t54PopCallback(void *ptr);
void t55PopCallback(void *ptr);
void t56PopCallback(void *ptr);
void t57PopCallback(void *ptr);
void t58PopCallback(void *ptr);
void t59PopCallback(void *ptr);
///////////////////////////////////////page 5
void b60PopCallback(void *ptr);
void b61PopCallback(void *ptr);
void n60PopCallback(void *ptr);
void n61PopCallback(void *ptr);
void n62PopCallback(void *ptr);
void n63PopCallback(void *ptr);
void b61PopCallback(void *ptr);
///////////////////////////////////////page 6
void n70PopCallback(void *ptr);
void n71PopCallback(void *ptr);
void n72PopCallback(void *ptr);
void n73PopCallback(void *ptr);
void b70PopCallback(void *ptr);
void b74PopCallback(void *ptr);
///////////////////////////////////////page 8
void b80PopCallback(void *ptr);
///////////////////////////////////////page 9
void b90PopCallback(void *ptr);
void b91PopCallback(void *ptr);
void b92PopCallback(void *ptr);
void b93PopCallback(void *ptr);
void b94PopCallback(void *ptr);
void n90PopCallback(void *ptr);
void n91PopCallback(void *ptr);
///////////////////////////////////////page 10
void b100PopCallback(void *ptr);
void b101PopCallback(void *ptr);
void b102PopCallback(void *ptr);
void b103PopCallback(void *ptr);
void b104PopCallback(void *ptr);
///////////////////////////////////////

NexPage page0    = NexPage(0, 0, "Hoofd");
NexPage page1    = NexPage(1, 0, "Hoofd1");
NexPage page2    = NexPage(2, 0, "Menu1");
NexPage page3    = NexPage(3, 0, "Zone");
NexPage page4    = NexPage(4, 0, "Hystorie");
NexPage page5    = NexPage(5, 0, "settime");
NexPage page6    = NexPage(6, 0, "codes");
NexPage page7    = NexPage(7, 0, "");
NexPage page8    = NexPage(8, 0, "Voeding");
NexPage page9    = NexPage(9, 0, "Timers");
NexPage page10    = NexPage(10, 0, "verlichting");
/////////////////////////////////////page 0
NexButton b0 = NexButton(0, 2, "b0");
NexButton b1 = NexButton(0, 3, "b1");
NexButton b2 = NexButton(0, 4, "b2");
NexButton b3 = NexButton(0, 5, "b3");
NexButton b4 = NexButton(0, 6, "b4");
NexButton b5 = NexButton(0, 7, "b5");
NexButton b6 = NexButton(0, 8, "b6");
NexButton b7 = NexButton(0, 9, "b7");
NexButton b8 = NexButton(0, 10, "b8");
NexButton b9 = NexButton(0, 11, "b9");
NexButton b10 = NexButton(0, 12, "b10");
NexButton b11 = NexButton(0, 14, "b11");
NexButton b12 = NexButton(0, 26, "b12");
NexText t0 = NexText(0, 13, "t0");
NexText t1 = NexText(0, 15, "t1");
//NexText t2 = NexText(0, 3, "t11");
////////////////////////////////////////page 1
NexButton b20 = NexButton(1, 2, "b0");
NexButton b21 = NexButton(1, 3, "b1");
NexButton b22 = NexButton(1, 4, "b2");
///////////////////////////////////////page 2
NexButton b30 = NexButton(2, 2, "b0");
NexButton b31 = NexButton(2, 3, "b1");
NexButton b32 = NexButton(2, 4, "b2");
NexButton b33 = NexButton(2, 5, "b3");
NexButton b34 = NexButton(2, 6, "b4");
NexButton b35 = NexButton(2, 7, "b5");
NexButton b36 = NexButton(2, 8, "b6");
///////////////////////////////////////page 3
NexButton b40 = NexButton(3, 2, "b0");
NexText t40 = NexText(3, 13, "t11");
NexText t41 = NexText(3, 14, "t12");
NexText t42 = NexText(3, 15, "t13");
NexText t43 = NexText(3, 16, "t14");
NexText t44 = NexText(3, 17, "t15");
NexText t45 = NexText(3, 18, "t16");
NexText t46 = NexText(3, 19, "t17");
NexText t47 = NexText(3, 20, "t18");
NexText t48 = NexText(3, 21, "t19");
NexText t49 = NexText(3, 22, "t20");
///////////////////////////////////////page 4
NexText t51 = NexText(4, 3, "t1");
NexText t52 = NexText(4, 4, "t2");
NexText t53 = NexText(4, 5, "t3");
NexText t54 = NexText(4, 6, "t4");
NexText t55 = NexText(4, 7, "t5");
NexText t56 = NexText(4, 8, "t6");
NexText t57 = NexText(4, 9, "t7");
NexText t58 = NexText(4, 10, "t8");
NexText t59 = NexText(4, 11, "t9");
NexButton b50 = NexButton(4, 2, "b0");
NexButton b51 = NexButton(4, 12, "b1");
///////////////////////////////////////page 5
NexButton b60 = NexButton(5, 2, "b0");
NexButton b61 = NexButton(5, 13, "b1");
NexNumber n60 = NexNumber(5, 3, "n0");
NexNumber n61 = NexNumber(5, 4, "n1");
NexNumber n62 = NexNumber(5, 5, "n2");
NexNumber n63 = NexNumber(5, 6, "n3");
NexNumber n64 = NexNumber(5, 7, "n4");
///////////////////////////////////////page 6
NexNumber n70 = NexNumber(6, 6, "n0");
NexNumber n71 = NexNumber(6, 7, "n1");
NexNumber n72 = NexNumber(6, 8, "n2");
NexNumber n73 = NexNumber(6, 9, "n3");
NexButton b70 = NexButton(6, 10, "b0");
NexButton b74 = NexButton(6, 11, "b4");
///////////////////////////////////////page 7
NexButton b80 = NexButton(8, 2, "b0");
///////////////////////////////////////page 8
NexButton b90 = NexButton(9, 2, "b0");
NexButton b91 = NexButton(9, 5, "b1");
NexButton b92 = NexButton(9, 6, "b2");
NexButton b93 = NexButton(9, 7, "b3");
NexButton b94 = NexButton(9, 8, "b4");
NexNumber n90 = NexNumber(6, 9, "n0");
NexNumber n91 = NexNumber(6, 10, "n1");
///////////////////////////////////////page 10
NexButton b100 = NexButton(10, 2, "b0");
NexButton b101 = NexButton(10, 3, "b1");
NexButton b102 = NexButton(10, 4, "b2");
NexButton b103 = NexButton(10, 5, "b3");
NexButton b104 = NexButton(10, 6, "b4");

NexTouch *nex_listen_list[] =
{
  &t0,
  &t1,
  // &t2,
  &t51,
  &t52,
  &t53,
  &t54,
  &t55,
  &t56,
  &t57,
  &t58,
  &t59,
  &t40,
  &t41,
  &t42,
  &t43,
  &t44,
  &t45,
  &t46,
  &t47,
  &t48,
  &t49,
  &b0,
  &b1,
  &b2,
  &b3,
  &b4,
  &b5,
  &b6,
  &b7,
  &b8,
  &b9,
  &b10,
  &b11,
  &b12,
  &b20,
  &b21,
  &b22,
  &b30,
  &b31,
  &b32,
  &b33,
  &b34,
  &b35,
  &b36,
  &b40,
  &b50,
  &b51,
  &b60,
  &b61,
  &n60,
  &n61,
  &n62,
  &n63,
  &n64,
  &b70,
  &b74,
  &b80,
  &b90,
  &b91,
  &b92,
  &b93,
  &b94,
  &b100,
  &b101,
  &b102,
  &b103,
  &b104,
  &n70,
  &n71,
  &n72,
  &n73,
  &n90,
  &n91,
  &page0,
  &page1,
  &page2,
  &page3,
  &page4,
  &page5,
  &page6,
  &page7,
  &page8,
  &page9,
  &page10,
  NULL
};

void page0PopCallback(void *ptr) {
  dbSerialPrintln("page0PopCallback");
  page0.show();
}
void page1PopCallback(void *ptr) {
  dbSerialPrintln("page1PopCallback");
  page1.show();
}
void page2PopCallback(void *ptr) {
  dbSerialPrintln("page2PopCallback");
  page2.show();
}
void page3PopCallback(void *ptr) {
  dbSerialPrintln("page3PopCallback");
  page3.show();
}
void page4PopCallback(void *ptr) {
  dbSerialPrintln("page4PopCallback");
  page4.show();
}
void page5PopCallback(void *ptr) {
  dbSerialPrintln("page5PopCallback");
  page5.show();
}
void page6PopCallback(void *ptr) {
  dbSerialPrintln("page6PopCallback");
  page6.show();
}
void page7PopCallback(void *ptr) {
  dbSerialPrintln("page8PopCallback");
  page7.show();
}
void page8PopCallback(void *ptr) {
  dbSerialPrintln("page9PopCallback");
  page8.show();
}
void page9PopCallback(void *ptr) {
  dbSerialPrintln("page10PopCallback");
  page9.show();
}
void page10PopCallback(void *ptr) {
  dbSerialPrintln("page10PopCallback");
  page10.show();
}
///////////////////////////////////////page 0

void t0PopCallback(void *ptr) {
  dbSerialPrintln("t0PopCallback");
  t0.setText("Huis alarm");
}
void t1PopCallback(void *ptr) {
  dbSerialPrintln("t1PopCallback");
  t1.setText("");
}
void b0PopCallback(void *ptr) {
  dbSerialPrintln("b0PopCallback");
  customKey = '1';
  // Serial.println("1");
}
void b1PopCallback(void *ptr) {
  dbSerialPrintln("b1PopCallback");
  customKey = '2';
  // Serial.println("2");
}
void b2PopCallback(void *ptr) {
  dbSerialPrintln("b2PopCallback");
  customKey = '3';
  // Serial.println("3");
}
void b3PopCallback(void *ptr) {
  dbSerialPrintln("b3PopCallback");
  customKey = '4';
  //  Serial.println("4");
}
void b4PopCallback(void *ptr) {
  dbSerialPrintln("b4PopCallback");
  customKey = '5';
  // Serial.println("5");
}
void b5PopCallback(void *ptr) {
  dbSerialPrintln("b5PopCallback");
  customKey = '6';
  //Serial.println("6");
}
void b6PopCallback(void *ptr) {
  dbSerialPrintln("b6PopCallback");
  customKey = '7';
  // Serial.println("7");
}
void b7PopCallback(void *ptr) {
  dbSerialPrintln("b7PopCallback");
  customKey = '8';
  // Serial.println("8");
}
void b8PopCallback(void *ptr) {
  dbSerialPrintln("b8PopCallback");
  customKey = '9';
  // Serial.println("9");
}
void b9PopCallback(void *ptr) {
  dbSerialPrintln("b9PopCallback");
  customKey = '0';
  // Serial.println("0");
}
void b10PopCallback(void *ptr) {
  dbSerialPrintln("b10PopCallback");
  dbSerialPrintln("page3PopCallback");
  page3.show();
  delay(1000);
  page = 3;
}
void b11PopCallback(void *ptr) {
  dbSerialPrintln("b11PopCallback");
  Data[data_count--] = 0; //clear array for new data
  data_count = 0;
  t1.setText("");
}
void b12PopCallback(void *ptr) {
  dbSerialPrintln("b12PopCallback");
  dbSerialPrintln("page10PopCallback");
  page10.show();
  delay(1000);
  page = 10;
}
////////////////////////////////////////////page 1
void b20PopCallback(void *ptr) {
  dbSerialPrintln("b20PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  previousMillisB = currentMillis;
  delay(1500);
  Serial3.write("14 \n");
  //delay(500);
  Wacht = true;
  page = 0;
  clearData();
}
void b21PopCallback(void *ptr) {
  dbSerialPrintln("b21PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  previousMillisB = currentMillis;
  delay(1500);
  Serial3.write("13 \n");
  //delay(500);
  Wacht = true;
  page = 0;
  clearData();
}
void b22PopCallback(void *ptr) {
  dbSerialPrintln("b22PopCallback");
  dbSerialPrintln("page0PopCallback");
  Serial3.write("40 \n");
  delay(1500);
  page0.show();
  previousMillisB = currentMillis;
  page = 0;
  clearData();
}
////////////////////////////////////////////page 2
void b30PopCallback(void *ptr) {
  dbSerialPrintln("b30PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  page = 0;
}
void b31PopCallback(void *ptr) {
  dbSerialPrintln("b31PopCallback");
  dbSerialPrintln("page4PopCallback");
  page4.show();
  page = 4;
}
void b32PopCallback(void *ptr) {
  dbSerialPrintln("b32PopCallback");
  dbSerialPrintln("page3PopCallback");
  page3.show();
  delay(1000);
  page = 3;
}
void b33PopCallback(void *ptr) {
  dbSerialPrintln("b33PopCallback");
  dbSerialPrintln("page5PopCallback");
  page5.show();
  page = 5;
}
void b34PopCallback(void *ptr) {
  dbSerialPrintln("b34PopCallback");
  dbSerialPrintln("page6PopCallback");
  page6.show();
  page = 6;

}
void b35PopCallback(void *ptr) {
  dbSerialPrintln("b35PopCallback");
  dbSerialPrintln("page9PopCallback");
  page9.show();
  page = 9;
  delay(150);
  n90.setValue(interA);
  n91.setValue(interB);
}
void b36PopCallback(void *ptr) {
  dbSerialPrintln("b36PopCallback");
  dbSerialPrintln("page8PopCallback");
  page8.show();
  page = 8;
}
////////////////////////////////////////////page 3
void b40PopCallback(void *ptr) {
  dbSerialPrintln("b40PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  page = 0;
  zone1old = HIGH;
  zone2old = HIGH;
  zone3old = HIGH;
  zone4old = HIGH;
  zone5old = HIGH;
  zone6old = HIGH;
  zone7old = HIGH;
  zone8old = HIGH;
  zone9old = HIGH;
  Saboold = HIGH;
}
void t40PopCallback(void *ptr) {
  dbSerialPrintln("t40PopCallback");
  t40.setText("");
}
void t41PopCallback(void *ptr) {
  dbSerialPrintln("t41PopCallback");
  t41.setText("test");
}
void t42PopCallback(void *ptr) {
  dbSerialPrintln("t42PopCallback");
  t42.setText("test");
}
void t43PopCallback(void *ptr) {
  dbSerialPrintln("t43PopCallback");
  t43.setText("");
}
void t44PopCallback(void *ptr) {
  dbSerialPrintln("t44PopCallback");
  t44.setText("test");
}
void t45PopCallback(void *ptr) {
  dbSerialPrintln("t45PopCallback");
  t45.setText("test");
}
void t46PopCallback(void *ptr) {
  dbSerialPrintln("t46PopCallback");
  t46.setText("");
}
void t47PopCallback(void *ptr) {
  dbSerialPrintln("t47PopCallback");
  t47.setText("test");
}
void t48PopCallback(void *ptr) {
  dbSerialPrintln("t48PopCallback");
  t48.setText("test");
}
void t49PopCallback(void *ptr) {
  dbSerialPrintln("t49PopCallback");
  t49.setText("test");
}
////////////////////////////////////////////page 4
void t51PopCallback(void *ptr) {
  dbSerialPrintln("t51PopCallback");
  t51.setText("");
}
void t52PopCallback(void *ptr) {
  dbSerialPrintln("t52PopCallback");
  t52.setText("test");
}
void t53PopCallback(void *ptr) {
  dbSerialPrintln("t53PopCallback");
  t53.setText("test");
}
void t54PopCallback(void *ptr) {
  dbSerialPrintln("t54PopCallback");
  t54.setText("");
}
void t55PopCallback(void *ptr) {
  dbSerialPrintln("t55PopCallback");
  t55.setText("test");
}
void t56PopCallback(void *ptr) {
  dbSerialPrintln("t56PopCallback");
  t56.setText("test");
}
void t57PopCallback(void *ptr) {
  dbSerialPrintln("t57PopCallback");
  t57.setText("");
}
void t58PopCallback(void *ptr) {
  dbSerialPrintln("t58PopCallback");
  t58.setText("test");
}
void t59PopCallback(void *ptr) {
  dbSerialPrintln("t59PopCallback");
  t59.setText("test");
}
void b50PopCallback(void *ptr) {
  dbSerialPrintln("b50PopCallback");
  dbSerialPrintln("page2PopCallback");
  page2.show();
  page = 3;
  page4sent = false;
}
void b51PopCallback(void *ptr) {
  dbSerialPrintln("b51PopCallback");
  SD.remove("log.txt");
  delay(500);
  myFile1 = SD.open("log.txt", FILE_WRITE);
  delay(1000);
  page2.show();
}
////////////////////////////////////////////page 5
void b60PopCallback(void *ptr) {
  dbSerialPrintln("b60PopCallback");
  dbSerialPrintln("page2PopCallback");
  page2.show();
  page = 2;
}
void b61PopCallback(void *ptr) {
  dbSerialPrintln("b61PopCallback");
  page5.show();
}
void n60PopCallback(void *ptr) {
  dbSerialPrintln("n60PopCallback");
  n60.setValue(50);
}
void n61PopCallback(void *ptr) {
  dbSerialPrintln("n61PopCallback");
  n61.setValue(50);
}
void n62PopCallback(void *ptr) {
  dbSerialPrintln("n62PopCallback");
  n62.setValue(50);
}
void n63PopCallback(void *ptr) {
  dbSerialPrintln("n63PopCallback");
  n63.setValue(50);
}
void n64PopCallback(void *ptr) {
  dbSerialPrintln("n64PopCallback");
  n64.setValue(50);
}
////////////////////////////////////////////page 6
void n70PopCallback(void *ptr) {
  dbSerialPrintln("n70PopCallback");
  n70.setValue(50);
}
void n71PopCallback(void *ptr) {
  dbSerialPrintln("n71PopCallback");
  n71.setValue(50);
}
void n72PopCallback(void *ptr) {
  dbSerialPrintln("n72PopCallback");
  n72.setValue(50);
}
void n73PopCallback(void *ptr) {
  dbSerialPrintln("n73PopCallback");
  n73.setValue(50);
}
void b70PopCallback(void *ptr) {
  dbSerialPrintln("b70PopCallback");
  if (page == 6) {
    uint32_t code;
    n70.getValue(&code);
    SD.remove("code1.txt");
    delay(500);
    myFile1 = SD.open("code1.txt", FILE_WRITE);
    delay(500);
    if (myFile1) {
      myFile1.print(code);
      myFile1.print("\n");
      delay(1000);
      myFile1.close();
      //   Serial.print(code);
      //   Serial.println("geschreven");
    }
  }
  if (page == 6) {
    uint32_t code;
    n71.getValue(&code);
    SD.remove("code2.txt");
    delay(500);
    myFile1 = SD.open("code2.txt", FILE_WRITE);
    delay(500);
    if (myFile1) {
      myFile1.print(code);
      myFile1.print("\n");
      delay(1000);
      myFile1.close();
      //    Serial.print(code);
      //    Serial.println("geschreven");
    }
  }
  if (page == 6) {
    uint32_t code;
    n72.getValue(&code);
    SD.remove("code3.txt");
    delay(500);
    myFile1 = SD.open("code3.txt", FILE_WRITE);
    delay(500);
    if (myFile1) {
      myFile1.print(code);
      myFile1.print("\n");
      delay(1000);
      myFile1.close();
      //  Serial.print(code);
      ///   Serial.println("geschreven");
    }
  }
  if (page == 6) {
    uint32_t code;
    n73.getValue(&code);
    SD.remove("code4.txt");
    delay(1000);
    myFile1 = SD.open("code4.txt", FILE_WRITE);
    delay(1000);
    if (myFile1) {
      myFile1.print(code);
      myFile1.print("\n");
      delay(1000);
      myFile1.close();
      delay(500);
      myFile = SD.open("code1.txt", FILE_READ);
      while (myFile.available() != 0) {
        String LineString = "Pissing away resources uselessly";
        LineString = myFile.readStringUntil('\n');
        LineString.toCharArray(Martijn, 5);
      }
      myFile.close();

      myFile = SD.open("code2.txt", FILE_READ);
      while (myFile.available() != 0) {
        String LineString = "Pissing away resources uselessly";
        LineString = myFile.readStringUntil('\n');
        LineString.toCharArray(Sitske, 5);
      }
      myFile.close();

      myFile = SD.open("code3.txt", FILE_READ);
      while (myFile.available() != 0) {
        String LineString = "Pissing away resources uselessly";
        LineString = myFile.readStringUntil('\n');
        LineString.toCharArray(Gast, 5);
      }
      myFile.close();

      myFile = SD.open("code4.txt", FILE_READ);
      while (myFile.available() != 0) {
        String LineString = "Pissing away resources uselessly";
        LineString = myFile.readStringUntil('\n');
        LineString.toCharArray(Master, 5);
      }
      //arduino must reset one or the other way xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
      page0.show();
      page = 0;
    }
  }
}
void b74PopCallback(void *ptr) {
  dbSerialPrintln("b74PopCallback");
  dbSerialPrintln("page2PopCallback");
  page2.show();
  page = 2;
}
////////////////////////////////////////////page 7
void b80PopCallback(void *ptr) {
  dbSerialPrintln("b80PopCallback");
  dbSerialPrintln("page2PopCallback");
  page2.show();
  page = 8;
}
////////////////////////////////////////////page 8

void b90PopCallback(void *ptr) {
  dbSerialPrintln("b90PopCallback");
  dbSerialPrintln("page2PopCallback");
  page2.show();
  page = 2;
}
void n90PopCallback(void *ptr) {
  dbSerialPrintln("n90PopCallback");
  n90.setValue(interA);
}
void n91PopCallback(void *ptr) {
  dbSerialPrintln("n91PopCallback");
  n91.setValue(interB);
}
void b91PopCallback(void *ptr) {
  dbSerialPrintln("b91PopCallback");
  intervalA = intervalA + 1000;
  page9.show();
  n90.setValue(interA);
  n91.setValue(interB);
}

void b92PopCallback(void *ptr) {
  dbSerialPrintln("b92PopCallback");
  intervalA = intervalA - 1000;
  page9.show();
  n90.setValue(interA);
  n91.setValue(interB);
}

void b93PopCallback(void *ptr) {
  dbSerialPrintln("b93PopCallback");
  intervalB = intervalB + 1000;
  page9.show();
  n90.setValue(interA);
  n91.setValue(interB);
}

void b94PopCallback(void *ptr) {
  dbSerialPrintln("b94PopCallback");
  intervalB = intervalB - 1000;
  page9.show();
  n90.setValue(interA);
  n91.setValue(interB);
}
////////////////////////////////////////////page 10
void b100PopCallback(void *ptr) {
  dbSerialPrintln("b100PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  Serial3.write("14 \n");
  delay(1500);
  page = 0;
}
void b101PopCallback(void *ptr) {
  dbSerialPrintln("b101PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  Serial3.write("13 \n");
  delay(1500);
  page = 0;
}
void b102PopCallback(void *ptr) {
  dbSerialPrintln("b102PopCallback");
  dbSerialPrintln("page0PopCallback");
  page0.show();
  page = 0;
}
void b103PopCallback(void *ptr) {
  dbSerialPrintln("b103PopCallback");
  Serial3.write("39 \n");
  delay(1500);
}
void b104PopCallback(void *ptr) {
  dbSerialPrintln("b104PopCallback");
  Serial3.write("38 \n");
  delay(1500);
}

////////////////////////////////////////////////////////////////setup/////////////////////////////////////////////////////////////////////
void setup(void) {
  nexInit();
  ///////////////////////////////page1
  t0.attachPop(t0PopCallback);
  t1.attachPop(t1PopCallback);
  b0.attachPop(b0PopCallback);
  b1.attachPop(b1PopCallback);
  b2.attachPop(b2PopCallback);
  b3.attachPop(b3PopCallback);
  b4.attachPop(b4PopCallback);
  b5.attachPop(b5PopCallback);
  b6.attachPop(b6PopCallback);
  b7.attachPop(b7PopCallback);
  b8.attachPop(b8PopCallback);
  b9.attachPop(b9PopCallback);
  b10.attachPop(b10PopCallback);
  b11.attachPop(b11PopCallback);
  b12.attachPop(b12PopCallback);
  ///////////////////////////////////page 2
  b20.attachPop(b20PopCallback);
  b21.attachPop(b21PopCallback);
  b22.attachPop(b22PopCallback);
  /////////////////////////////////////page 3
  b30.attachPop(b30PopCallback);
  b31.attachPop(b31PopCallback);
  b32.attachPop(b32PopCallback);
  b33.attachPop(b33PopCallback);
  b34.attachPop(b34PopCallback);
  b35.attachPop(b35PopCallback);
  b36.attachPop(b36PopCallback);
  ////////////////////////////////////page 4
  b40.attachPop(b40PopCallback);
  t40.attachPop(t40PopCallback);
  t41.attachPop(t41PopCallback);
  t42.attachPop(t42PopCallback);
  t43.attachPop(t43PopCallback);
  t44.attachPop(t44PopCallback);
  t45.attachPop(t45PopCallback);
  t46.attachPop(t46PopCallback);
  t47.attachPop(t47PopCallback);
  t48.attachPop(t48PopCallback);
  t49.attachPop(t49PopCallback);
  ////////////////////////////////////page 5
  t51.attachPop(t51PopCallback);
  t52.attachPop(t52PopCallback);
  t53.attachPop(t53PopCallback);
  t54.attachPop(t54PopCallback);
  t55.attachPop(t55PopCallback);
  t56.attachPop(t56PopCallback);
  t57.attachPop(t57PopCallback);
  t58.attachPop(t58PopCallback);
  t59.attachPop(t59PopCallback);
  b50.attachPop(b50PopCallback);
  b51.attachPop(b51PopCallback);
  ////////////////////////////////////page 6
  b60.attachPop(b60PopCallback);
  b61.attachPop(b61PopCallback);
  n60.attachPop(n60PopCallback);
  n61.attachPop(n61PopCallback);
  n62.attachPop(n62PopCallback);
  n63.attachPop(n63PopCallback);
  n64.attachPop(n64PopCallback);
  ///////////////////////////////////page 7
  n70.attachPop(n70PopCallback);
  n71.attachPop(n71PopCallback);
  n72.attachPop(n72PopCallback);
  n73.attachPop(n73PopCallback);
  b70.attachPop(b70PopCallback);
  b74.attachPop(b74PopCallback);
  ///////////////////////////////////page 8
  b80.attachPop(b80PopCallback);
  ///////////////////////////////////page 9
  b90.attachPop(b90PopCallback);
  b91.attachPop(b91PopCallback);
  b92.attachPop(b92PopCallback);
  b93.attachPop(b93PopCallback);
  b94.attachPop(b94PopCallback);
  ///////////////////////////////////page 10
  b100.attachPop(b100PopCallback);
  b101.attachPop(b101PopCallback);
  b102.attachPop(b102PopCallback);
  b103.attachPop(b103PopCallback);
  b104.attachPop(b104PopCallback);
  ////////////////////////////////////////////////////////////////
  page0.attachPop(page0PopCallback);
  page1.attachPop(page1PopCallback);
  page2.attachPop(page2PopCallback);
  page3.attachPop(page3PopCallback);
  page4.attachPop(page4PopCallback);
  page5.attachPop(page5PopCallback);
  page6.attachPop(page6PopCallback);
  page7.attachPop(page7PopCallback);
  page8.attachPop(page8PopCallback);
  page9.attachPop(page9PopCallback);
  page10.attachPop(page10PopCallback);



  dbSerialPrintln("setup done");

  Serial.begin(9600);
  Serial3.begin(115200);

  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    while (1);
  }

  delay(100);

  dbSerialPrintln("page0PopCallback");

  page0.show();

  pinMode(woon_Pin, INPUT);
  pinMode(hal_Pin, INPUT);
  pinMode(voordeur_Pin, INPUT);
  pinMode(achter_deur_Pin, INPUT);
  pinMode(voor_raam_Pin, INPUT);
  pinMode(garage_roldeur_Pin, INPUT);
  pinMode(balkon_deur_Pin, INPUT);
  pinMode(zij_raam_Pin, INPUT);
  pinMode(slaap_raam_Pin, INPUT);
  pinMode(hobby_raam_Pin, INPUT);
  pinMode(garage_deur_Pin, INPUT);
  pinMode(garage_deur_2_Pin, INPUT);
  pinMode(keuken_Pin, INPUT);

  pinMode(lamp_Pin, OUTPUT);
  pinMode(sirene_Pin, OUTPUT);
  digitalWrite(lamp_Pin, HIGH);
  digitalWrite(sirene_Pin, HIGH);


  // Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    //  Serial.println("initialization failed!");
    return;
  }
  //  Serial.println("initialization done.");


  myFile = SD.open("code1.txt", FILE_READ);
  while (myFile.available() != 0) {
    String LineString = "Pissing away resources uselessly";
    LineString = myFile.readStringUntil('\n');
    LineString.toCharArray(Martijn, 5);
  }
  myFile.close();

  myFile = SD.open("code2.txt", FILE_READ);
  while (myFile.available() != 0) {
    String LineString = "Pissing away resources uselessly";
    LineString = myFile.readStringUntil('\n');
    LineString.toCharArray(Sitske, 5);
  }
  myFile.close();

  myFile = SD.open("code3.txt", FILE_READ);
  while (myFile.available() != 0) {
    String LineString = "Pissing away resources uselessly";
    LineString = myFile.readStringUntil('\n');
    LineString.toCharArray(Gast, 5);
  }
  myFile.close();

  myFile = SD.open("code4.txt", FILE_READ);
  while (myFile.available() != 0) {
    String LineString = "Pissing away resources uselessly";
    LineString = myFile.readStringUntil('\n');
    LineString.toCharArray(Master, 5);
  }
  myFile.close();
}
void loop(void) {
  currentMillis = millis();
  Serial.print("previousMillisC");
  Serial.println(previousMillisC);
   Serial.print("currentMillis");
  Serial.println(currentMillis);
   Serial.print("intervalC");
  Serial.println(intervalC);

  nexLoop(nex_listen_list);
  DateTime now = rtc.now();
  //Serial.println(zone);


  zone1 = digitalRead(hal_Pin);//low is melding - high is oke
  zone2 = digitalRead(voordeur_Pin);//low is melding - high is oke
  zone3 = digitalRead(woon_Pin);//low is melding - high is oke
  zone4 = digitalRead(achter_deur_Pin);//low is melding - high is oke
  zone5 = digitalRead(voor_raam_Pin);//low is melding - high is oke
  zone6 = digitalRead(garage_roldeur_Pin);//low is melding - high is oke
  zone7 = digitalRead(balkon_deur_Pin);//low is melding - high is oke
  zone8 = digitalRead(zij_raam_Pin);//low is melding - high is oke
  zone9 = digitalRead(slaap_raam_Pin);//low is melding - high is oke
  zone10 = digitalRead(hobby_raam_Pin);//low is melding - high is oke
  zone11 = digitalRead(garage_deur_Pin);//low is melding - high is oke
  zone12 = digitalRead(garage_deur_2_Pin);//low is melding - high is oke
  zone13 = digitalRead(keuken_Pin);//low is melding - high is oke


  Sabo = digitalRead(sabo_Pin);//low is melding - high is oke
  // Serial.print(zone1);
  // Serial.println(zone2);
  //////////////////////////////////////////////////////
  if (zone1 == HIGH && gang == false) {//hal
    gang = true;
    Serial3.write("9 \n");
  }
  if (zone1 == LOW && gang == true) {
    gang = false;
    Serial3.write("10 \n");
  }
  /////////////////////////////////////////////////////////
  if (zone2 == HIGH && voordeur == false) {//voordeur
    voordeur = true;
    Serial3.write("11 \n");
    // delay(10);
  }
  if (zone2 == LOW && voordeur == true) {
    voordeur = false;
    Serial3.write("12 \n");
    //delay(10);
  }


  if (Actief == true && Wacht == false && Alarm == false) {
    if (zone1 == HIGH) {
      zone = 1;
      Wacht = true;
      previousMillisB = currentMillis;
      previousMillisC = currentMillis;
    }
    if (zone2 == HIGH) {
      zone = 2;
      Wacht = true;
      previousMillisB = currentMillis;
      previousMillisC = currentMillis;
    }
    if (zone3 == HIGH) {
      zone = 3;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("32 \n");
    }
    if (zone4 == HIGH) {
      zone = 4;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("33 \n");
    }
    if (zone5 == HIGH) {
      zone = 5;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("34 \n");
    }
    if (zone6 == HIGH) {
      zone = 6;
      previousMillisC = currentMillis;
      Wacht = true;
      Serial3.write("35 \n");
    }
    if (zone7 == HIGH) {
      zone = 7;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("36 \n");
    }
    if (zone8 == HIGH) {
      zone = 8;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("37 \n");
    }
    if (zone9 == HIGH) {
      zone = 9;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("38 \n");
    }
    if (zone10 == HIGH) {
      zone = 10;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("39 \n");
    }
    if (zone11 == HIGH) {
      zone = 11;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("40 \n");
    }
    if (zone12 == HIGH) {
      zone = 12;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("41 \n");
    }
    if (zone13 == HIGH) {
      zone = 13;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("42 \n");
    }
    if (zone14 == HIGH) {
      zone = 14;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("33 \n");
    }
    if (zone15 == HIGH) {
      zone = 15;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("44 \n");
    }
    if (zone16 == HIGH) {
      zone = 16;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("45 \n");
    }
    if (Sabo == HIGH) {
      zone = 50;
      previousMillisC = currentMillis;
      Alarm = true;
      Serial3.write("46 \n");
    }
  }

  if (Wacht == true) {
    wait();
  }
  if (Alarm == true) {
    Alarm_af();
    if (serial_sent == false) {
      if (zone == 1) {
        serial_sent = true;
        Serial3.write("30 \n");
      }
      if (zone == 2) {
        serial_sent = true;
        Serial3.write("31 \n");
      }
    }
  }
  if (Alarm == true && Alarmsent == false) {
    uint32_t code;
    code = zone;
    t0.setText("ALARM");
    Alarmsent = true;
    myFile1 = SD.open("log.txt", FILE_WRITE);
    delay(250);
    if (myFile1) {
      myFile1.print("Zone:");
      myFile1.print(code);
      myFile1.print(" ");
      myFile1.print(now.day(), DEC);
      myFile1.print('-');
      myFile1.print(now.month(), DEC);
      myFile1.print('-');
      myFile1.print(now.year(), DEC);
      myFile1.print(" ");
      myFile1.print(now.hour(), DEC);
      myFile1.print(':');
      myFile1.print(now.minute(), DEC);
      myFile1.print("\r");
      myFile1.close();
    }
  }

  ////////////////////////////////////////////////page 0
  if (page == 0) {

    if ((Wacht == false) && (Actief == false) && (Alarm == false)) {
      if (previousMillisC != 0) {
        previousMillisC = 0;
      }
      if ((zone3 == LOW) && (zone4 == LOW) && (zone5 == LOW) && (zone6 == LOW) && (zone7 == LOW) && (zone8 == LOW) && (zone9 == LOW) && (zone10 == LOW) && (zone11 == LOW) && (zone12 == LOW) && (zone13 == LOW) && (zone14 == LOW) && (zone15 == LOW) && (zone16 == LOW) && (Sabo == LOW)) {
        zoneok = true;
        if (sent_zone == false) {
          t0.setText("Alarm gereed");
          sent_zone = true;
        }
      } else {
        if (sent_zone == true) {
          zoneok = false;
          t0.setText("Alarm NIET gereed");
          sent_zone = false;
        }
      }
    }


    if (customKey != customKeyold) {
      Data[data_count] = customKey; // store char into data array
      data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
      customKey = ' ';
      if (data_count == 1) {
        dbSerialPrintln("t1PopCallback");
        t1.setText("*");
      }
      if (data_count == 2) {
        dbSerialPrintln("t1PopCallback");
        t1.setText("**");
      }
      if (data_count == 3) {
        dbSerialPrintln("t1PopCallback");
        t1.setText("***");
      }
      if (data_count == 4) {
        dbSerialPrintln("t1PopCallback");
        t1.setText("****");
      }
      timerA = true;
      previousMillisA = currentMillis;
    }




    if (data_count == Password_Lenght - 1) {
      if (!strcmp(Data, Martijn) || !strcmp(Data, Sitske) || !strcmp(Data, Gast) || !strcmp(Data, Master)) {
        if ((Wacht == false) && (Actief == false) && (Alarm == false)) { //if alarm is uit
          if (zoneok == true) {
            if (!strcmp(Data, Martijn)) { //door naar pagina 1 voor inschakelen
              Serial3.write("4 \n");
              delay(500);
              Serial3.write("19 \n");
              dbSerialPrintln("page0PopCallback");
              clearData();
              page1.show();
              page = 1;

            }
            if (!strcmp(Data, Sitske)) { //door naar pagina 1 voor inschakelen
              Serial3.write("5 \n");
              delay(500);
              Serial3.write("19 \n");
              dbSerialPrintln("page0PopCallback");
              clearData();
              page1.show();
              page = 1;
            }
            if (!strcmp(Data, Gast)) { //door naar pagina 1 voor inschakelen
              Serial3.write("6 \n");
              delay(500);
              Serial3.write("19 \n");
              dbSerialPrintln("page0PopCallback");
              clearData();
              page1.show();
              page = 1;

            }
          } else {
            clearData();
            t0.setText("Alarm NIET gereed");
          }
          if (!strcmp(Data, Master)) { //Master menu
            Serial3.write("7 \n");
            delay(500);
            dbSerialPrintln("page2PopCallback");
            clearData();
            page2.show();
            page = 2;
          }
        } else {
          if (!strcmp(Data, Martijn)) { //alarm uitschakelen
            clearData();
            zone = 0;
            Wacht = false;
            Actief = false;
            Alarm = false;
            Alarmsent = false;
            serial_sent = false;
            digitalWrite(lamp_Pin, HIGH);
            digitalWrite(sirene_Pin, HIGH);
            Serial3.write("1 \n");
            delay(500);
            Serial3.write("20 \n");
            if (Alarm_sent == true) {
              delay(500);
              Serial3.write("16 \n");
              Alarm_sent = false;
            }
            t0.setText("");
            t1.setText("");
            previousMillisB = currentMillis;
            data_count = 0;
          }
          if (!strcmp(Data, Sitske)) { //alarm uitschakelen
            clearData();
            zone = 0;
            Wacht = false;
            Actief = false;
            Alarm = false;
            Alarmsent = false;
            serial_sent = false;
            digitalWrite(lamp_Pin, HIGH);
            digitalWrite(sirene_Pin, HIGH);
            Serial3.write("2 \n");
            delay(500);
            Serial3.write("20 \n");
            if (Alarm_sent == true) {
              delay(500);
              Serial3.write("16 \n");
              Alarm_sent = false;
            }
            t0.setText("");
            t1.setText("");
            previousMillisB = currentMillis;
            data_count = 0;
          }
          if (!strcmp(Data, Gast)) { //alarm uitschakelen
            clearData();
            zone = 0;
            Wacht = false;
            Actief = false;
            Alarm = false;
            Alarmsent = false;
            serial_sent = false;
            digitalWrite(lamp_Pin, HIGH);
            digitalWrite(sirene_Pin, HIGH);
            Serial3.write("3 \n");
            delay(500);
            Serial3.write("20 \n");
            if (Alarm_sent == true) {
              delay(500);
              Serial3.write("16 \n");
              Alarm_sent = false;
            }
            t0.setText("");
            t1.setText("");
            previousMillisB = currentMillis;
            data_count = 0;
          }
        }
      } else {
        previousMillisA = currentMillis;
        clearData();
        dbSerialPrintln("t0PopCallback");
        t0.setText("Wrong Code");
        t1.setText("");
      }
    }
    customKeyold = customKey;

    if (timerA == true) {// reset pincode tijdens invoer
      if (currentMillis - previousMillisA >= intervalA) {
        //clearData();
      }
    }
  }


  ////////////////////////////////////////////////////////////////page 1 cv aan/uit
  // if (page == 1) {

  //}
  /////////////////////////////////////////////////////////page 2 menu
  //if (page == 2) {

  //}
  ///////////////////////////////////////////////////////////page 3 zone
  if (page == 3) {
    if (zone1 != zone1old) {
      zone1old = zone1;
      if (zone1 == LOW) {
        t40.setText("OK");
      } else {
        t40.setText("NOK");
      }
    }
    if (zone2 != zone2old) {
      zone2old = zone2;
      if (zone2 == LOW) {
        t41.setText("OK");
      } else {
        t41.setText("NOK");
      }
    }
    if (zone3 != zone3old) {
      zone3old = zone3;
      if (zone3 == LOW) {
        t42.setText("OK");
      } else {
        t42.setText("NOK");
      }
    }
    if (zone4 != zone4old) {
      zone4old = zone4;
      if (zone4 == LOW) {
        t43.setText("OK");
      } else {
        t43.setText("NOK");
      }
    }
    if (zone5 != zone5old) {
      zone5old = zone5;
      if (zone5 == LOW) {
        t44.setText("OK");
      } else {
        t44.setText("NOK");
      }
    }
    if (zone6 != zone6old) {
      zone6old = zone6;
      if (zone6 == LOW) {
        t45.setText("OK");
      } else {
        t45.setText("NOK");
      }
    }
    if (zone7 != zone7old) {
      zone7old = zone7;
      if (zone7 == LOW) {
        t46.setText("OK");
      } else {
        t46.setText("NOK");
      }
    }
    if (zone8 != zone8old) {
      zone8old = zone8;
      if (zone8 == LOW) {
        t47.setText("OK");
      } else {
        t47.setText("NOK");
      }
    }
    if (zone9 != zone9old) {
      zone9old = zone9;
      if (zone9 == LOW) {
        t48.setText("OK");
      } else {
        t48.setText("NOK");
      }
    }
    if (Sabo != Saboold) {
      Saboold = Sabo;
      if (Sabo == LOW) {
        t49.setText("OK");
      } else {
        t49.setText("NOK");
      }
    }
  }
  ///////////////////////////////////////////////////////////page 4 hystorie
  if (page == 4) {
    if (page4sent == false) {
      int recNum = 0;
      myFile = SD.open("log.txt");
      while (myFile.available())  {
        String list = myFile.readStringUntil('\r');
        recNum++;

        char yourMessage[25];
        list.toCharArray(yourMessage, 25) ;


        if (recNum == 1)    {
          dbSerialPrintln("t51PopCallback");
          t51.setText(yourMessage);
        }
        if (recNum == 2)    {
          dbSerialPrintln("t52PopCallback");
          t52.setText(yourMessage);
        }
        if (recNum == 3)    {
          dbSerialPrintln("t53PopCallback");
          t53.setText(yourMessage);
        }
        if (recNum == 4)    {
          dbSerialPrintln("t54PopCallback");
          t54.setText(yourMessage);
        }
        if (recNum == 5)    {
          dbSerialPrintln("t55PopCallback");
          t55.setText(yourMessage);
        }
        if (recNum == 6)    {
          dbSerialPrintln("t56PopCallback");
          t56.setText(yourMessage);
        }
        if (recNum == 7)    {
          dbSerialPrintln("t57PopCallback");
          t57.setText(yourMessage);
        }
        if (recNum == 8)    {
          dbSerialPrintln("t58PopCallback");
          t58.setText(yourMessage);
        }
        if (recNum == 9)    {
          dbSerialPrintln("t59PopCallback");
          t59.setText(yourMessage);
        }
        page4sent = true;
      }
    }

  }
  ///////////////////////////////////////////////////////////page 5
  //  if (page == 5) {

  // }
  //////////////////////////////////////////////////////////page 6
  //  if (page == 6) {

  //}
  ///////////////////////////////////////////////////////////page 7
  ///////////////////////////////////////////////////////////page 8
  //if (page == 8) {
  // }
  ///////////////////////////////////////////////////////////page 9
  if (page == 9) {
    interA = intervalA / 1000;
    interB = intervalB / 1000;
  }
  //////////////////////////////////////////////////////////

}
void wait() {
  tone(buzzerPin, 3520, 500);
  if (currentMillis - previousMillisB >= intervalB) {
    if (Actief == false) {
      Wacht = false;
      Actief = true;
      t0.setText("Woning Beveiligd");
      noTone(buzzerPin);
    } else {
      Wacht = false;
      Alarm = true;
      t0.setText("ALARM");
      noTone(buzzerPin);
    }
  }
}
void Alarm_af() {
  
  tone(buzzerPin, 2000, 500);
  digitalWrite(lamp_Pin, LOW);
  if (currentMillis - previousMillisC >= intervalC) {
    digitalWrite(sirene_Pin, HIGH);
  } else {
    digitalWrite(sirene_Pin, LOW);
  }
  if (Alarm_sent == false) {
    Serial3.write("15 \n");
    Alarm_sent = true;
  }
}
void clearData() {
  while (data_count != 0)
  { //This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
    data_count = 0;
    dbSerialPrintln("t0PopCallback");
    t1.setText("");
  }
  return;
}
