#include <Arduino.h>
#include <stdlib.h>
#include "WiFi.h"
#include "esp_system.h"

//----- ROS -----//
#include <ros.h>
#include <rosserial_arduino/Move.h>
// #include <rosserial_arduino/Adc.h>

const char* ssid = "VENTURINI";
const char* password = "tplink10";

IPAddress server(192, 168, 2, 111);
WiFiClient client;

class WiFiHardware {

  public:
  WiFiHardware() {};

  void init() {
    // do your initialization here. this probably includes TCP server/client setup
    client.connect(server, 11411);
  }

  // read a byte from the serial port. -1 = failure
  int read() {
    // implement this method so that it reads a byte from the TCP connection and returns it
    //  you may return -1 is there is an error; for example if the TCP connection is not open
    return client.read();         //will return -1 when it will works
  }

  // write data to the connection to ROS
  void write(uint8_t* data, int length) {
    // implement this so that it takes the arguments and writes or prints them to the TCP connection
    for(int i=0; i<length; i++)
      client.write(data[i]);
  }

  // returns milliseconds since start of program
  unsigned long time() {
     return millis(); // easy; did this one for you
  }
};


ros::NodeHandle_<WiFiHardware>  nh;
rosserial_arduino::Move move_msg;
ros::Publisher movePub("move", &move_msg);

// rosserial_arduino::Adc adc_msg;
// ros::Publisher p("adc", &adc_msg);

void setup(){
  Serial.begin(57600);
  Serial.println();

   Serial.print("Connecting to ");
   Serial.print(ssid);
  ///
  // Connect the ESP32 the the wifi AP
  WiFi.begin(ssid, password);
  //WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  //---Set the connection to rosserial socket server----------//
  // Set the connection to rosserial socket server
  nh.initNode();
  nh.advertise(movePub);

  // Check nh.Connected

  while(nh.connected() == 0)
  {
  nh.spinOnce();
  Serial.println("Not Connected to rosserial socket server");
  delay(100);
  }
  Serial.println("Connected to rosserial socket server");
  ////

}

//------------------- Loop ---------------------//
void loop(){
  Serial.println("LOOP STARTED !");
  move_msg.vel[0] = 1;
  move_msg.time = 1;

  movePub.publish(&move_msg);

  nh.spinOnce();
  delay(1000);
}
