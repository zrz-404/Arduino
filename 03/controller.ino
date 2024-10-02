#include <Adafruit_NeoPixel.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

void setup()
{
    Serial.begin(115200);
    WIFI.begin(ssid, password);

    
}