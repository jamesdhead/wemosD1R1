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
#include <Mitov_CommonMux.h>
#include <Mitov_Timing.h>
#include <Mitov_LogicFlipFlops.h>

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
Mitov::ToggleSwitch<float, float> AnalogToggleSwitch1;
Mitov::ToggleSwitch<float, float> AnalogToggleSwitch2;
Mitov::MapRange MapRange2;
Mitov::MapRange MapRange3;
Mitov::DetectEdge DetectEdge1;
Mitov::TFlipFlop TFlipFlop1;
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
  Declarations::WiiNunchuck1.AngleOutputPins[ 0 ].Connect( Declarations::MapRange2.InputPin );
  Declarations::WiiNunchuck1.AngleOutputPins[ 1 ].Connect( Declarations::MapRange3.InputPin );
  Declarations::WiiNunchuck1.StickOutputPins[ 0 ].Connect( Declarations::AnalogToggleSwitch1.FalseInputPin );
  Declarations::WiiNunchuck1.StickOutputPins[ 1 ].Connect( Declarations::MapRange1.InputPin );
  Declarations::WiiNunchuck1.ButtonOutputPins[ 1 ].Connect( Declarations::DetectEdge1.InputPin );
  Declarations::MapRange1.InputRange.Min = 0.140000000596046;
  Declarations::MapRange1.InputRange.Max = 0.889999985694885;
  Declarations::MapRange1.OutputPin.Connect( Declarations::AnalogToggleSwitch2.FalseInputPin );
  Declarations::Steering1.MotorsOutputPins[ 0 ].Connect( ((Mitov::BasicTypedStructureSinkElement<float,float> *) Declarations::MakeStructure1.Elements[ 0 ] )->InputPin );
  Declarations::Steering1.MotorsOutputPins[ 1 ].Connect( ((Mitov::BasicTypedStructureSinkElement<float,float> *) Declarations::MakeStructure1.Elements[ 1 ] )->InputPin );
  Declarations::MakeStructure1.OutputPin.Connect( Declarations::TArduinoWiFiUDPSocket1_SerialInputByte_1.InputPin );
  Declarations::AnalogToggleSwitch1.OutputPin.Connect( Declarations::Steering1.SteeringInputPins[ 0 ] );
  Declarations::AnalogToggleSwitch2.OutputPin.Connect( Declarations::Steering1.SteeringInputPins[ 1 ] );
  Declarations::MapRange2.InputRange.Min = 0.300000011920929;
  Declarations::MapRange2.InputRange.Max = 0.600000023841858;
  Declarations::MapRange2.OutputPin.Connect( Declarations::AnalogToggleSwitch1.TrueInputPin );
  Declarations::MapRange3.InputRange.Min = 0.189999997615814;
  Declarations::MapRange3.InputRange.Max = 0.699999988079071;
  Declarations::MapRange3.OutputPin.Connect( Declarations::AnalogToggleSwitch2.TrueInputPin );
  Declarations::DetectEdge1.OutputPin.Connect( Declarations::TFlipFlop1.ClockInputPin );
  Declarations::TFlipFlop1.OutputPin.Connect( Declarations::AnalogToggleSwitch2.SelectInputPin );
  Declarations::TFlipFlop1.OutputPin.Connect( Declarations::AnalogToggleSwitch1.SelectInputPin );

  OpenWire::Component::_SystemInit();
}

// The loop function is called in an endless loop
void loop()
{
  OpenWire::Component::_SystemLoop();
}
