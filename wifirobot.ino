#define VISUINO_ESP8266

#include <OpenWire.h>
#include <Mitov.h>
#include <ESP8266WiFi.h>
#include <Mitov_ESP8266_WiFi.h>
#include <WiFiUDP.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Mitov_FormattedSerial.h>
#include <Wire.h>
#include <Mitov_Basic_I2C.h>
#include <Mitov_Wii_Controller.h>
#include <Mitov_Math.h>
#include <Mitov_Steering_Differential.h>
#include <Mitov_Structure.h>

// Declarations

namespace Declarations
{
Mitov::ESP8266WiFiModule TArduinoESP8266WiFiModule1;
Mitov::ESP8266ModuleRemoteAccessPoint TArduinoESP8266WiFiModuleRemoteAccessPoint1( TArduinoESP8266WiFiModule1 );
Mitov::UDPSocket<Mitov::BasicEthernetShield,WiFiUDP> TArduinoWiFiUDPSocket1( TArduinoESP8266WiFiModule1, IPAddress( 200, 200, 200, 200 ) );
Mitov::EthernetSocketBinaryInput<Mitov::UDPSocket<Mitov::BasicEthernetShield,WiFiUDP>, &TArduinoWiFiUDPSocket1> TArduinoWiFiUDPSocket1_SerialInputByte_1;
Mitov::WiiNunchuck WiiNunchuck1;
Mitov::MapRange MapRange1;
Mitov::SteeringDifferential Steering1;
Mitov::MakeStructure<8> MakeStructure1;
} // Declarations

//The setup function is called once at startup of the sketch
void setup()
{
  Declarations::MakeStructure1.Elements.push_back( new Mitov::BasicTypedStructureSinkElement<float,float> );
  Declarations::MakeStructure1.Elements.push_back( new Mitov::BasicTypedStructureSinkElement<float,float> );
  Declarations::TArduinoESP8266WiFiModuleRemoteAccessPoint1.SSID = "SmartCar1";
  Declarations::TArduinoESP8266WiFiModuleRemoteAccessPoint1.Config.IP = IPAddress( 200, 200, 200, 100 );
  Declarations::TArduinoESP8266WiFiModuleRemoteAccessPoint1.Config.Enabled = true;
  Declarations::TArduinoWiFiUDPSocket1.RemotePort = 8888;
  Wire.begin();
  Declarations::WiiNunchuck1.StickOutputPins[ 0 ].Connect( Declarations::Steering1.SteeringInputPins[ 0 ] );
  Declarations::WiiNunchuck1.StickOutputPins[ 1 ].Connect( Declarations::MapRange1.InputPin );
  Declarations::MapRange1.InputRange.Min = 0.140000000596046;
  Declarations::MapRange1.InputRange.Max = 0.889999985694885;
  Declarations::MapRange1.OutputPin.Connect( Declarations::Steering1.SteeringInputPins[ 1 ] );
  Declarations::Steering1.MotorsOutputPins[ 0 ].Connect( ((Mitov::BasicTypedStructureSinkElement<float,float> *) Declarations::MakeStructure1.Elements[ 0 ] )->InputPin );
  Declarations::Steering1.MotorsOutputPins[ 1 ].Connect( ((Mitov::BasicTypedStructureSinkElement<float,float> *) Declarations::MakeStructure1.Elements[ 1 ] )->InputPin );
  Declarations::MakeStructure1.OutputPin.Connect( Declarations::TArduinoWiFiUDPSocket1_SerialInputByte_1.InputPin );

  OpenWire::Component::_SystemInit();
}

// The loop function is called in an endless loop
void loop()
{
  OpenWire::Component::_SystemLoop();
}
