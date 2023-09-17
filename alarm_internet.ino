#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD };
byte ip[] {192, 168, 0, 104};
EthernetClient client;
char server[] = "192.168.0.100";

int READ;
bool serial = false;

void setup() {
  // Serial.begin(115200);
  Serial3.begin(115200);
  Wire.begin();
  Ethernet.begin(mac, ip);

}
void loop() {
  if (Serial3.available()) {
    String s = Serial3.readStringUntil('\n');
    READ = s.toInt();
    delay(5);
    s = ' ';
  }

  if (READ > 40) {
    if (READ = ! 46) {
      READ = 0;
    }
  }


  if (READ != 0) {
    if (READ == 1) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=1&svalue=Martijn_uitgeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 2) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=1&svalue=Sitske_uitgeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 3) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=2&svalue=Gast_uitgeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 4) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=3&svalue=Martijn_ingeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 5) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=3&svalue=Sitske_ingeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 6) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Gast_ingeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 7) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Master_menu");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 9) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=69&switchcmd=On");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        // Serial.println("sent");
      }
    }
    if (READ == 10) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=69&switchcmd=Off");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        // Serial.println("sent");
      }
    }
    if (READ == 11) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=71&switchcmd=On");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        // Serial.println("sent");
      }
    }
    if (READ == 12) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=71&switchcmd=Off");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        //Serial.println("sent");
      }
    }
    if (READ == 13) {
      READ = 0;
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=setsetpoint&idx=19&setpoint=21");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        //Serial.println("sent");
      }
    }
    if (READ == 14) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=setsetpoint&idx=19&setpoint=18");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        //  Serial.println("sent");
      }
    }
    if (READ == 15) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=68&switchcmd=On&passcode=Opelvectra08");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        //  Serial.println("sent");
      }
    }
    if (READ == 16) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=68&switchcmd=Off&passcode=Opelvectra08");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        //  Serial.println("sent");
      }
    }
    if (READ == 17) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=2&svalue=Gast2_ingeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 18) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=2&svalue=Gast2_uitgeschakelt");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 19) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=52&switchcmd=On");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 20) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=52&switchcmd=Off");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }

    if (READ == 29) {
      // if (master == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        // client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Master_menu");
        client.print("GET /json.htm?type=command&param=udevice&idx=94&nvalue=4&svalue=Hal");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        // master = true;
      }
    }
    if (READ == 30) {
      //if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Gang");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }
    if (READ == 31) {
      //if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Voordeur");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

    if (READ == 32) {
      // if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Woonkamer");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

    if (READ == 33) {
      // if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Achterdeur");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

    if (READ == 34) {
      // if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Voorraam");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

    if (READ == 35) {
      // if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=GarageDeur");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

    if (READ == 36) {
      //if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Balkon");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

    if (READ == 37) {
      //if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Zijraam");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }
    if (READ == 38) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=70&switchcmd=On");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 39) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=switchlight&idx=70&switchcmd=Off");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 40) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=1&svalue=Reset");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.172");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = false;
      }
    }
    if (READ == 46) {
      //if (serial == false) {
      if (client.connect(server, 8080)) {
        READ = 0;
        client.print("GET /json.htm?type=command&param=udevice&idx=67&nvalue=4&svalue=Sabotage");
        client.println(" HTTP/1.1"); // Part of the GET request
        client.println("Host: 192.168.0.109");
        client.println("Connection: close");
        client.println(); // Empty line
        client.println(); // Empty line
        client.stop();    // Closing connection to server
        serial = true;
      }
    }

  }
}
