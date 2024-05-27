#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"
#define HOSTNAME  "esp32cam"

#include <eloquent_esp32cam.h>
#include <eloquent_esp32cam/viz/mjpeg.h>

using namespace eloq;
using namespace eloq::viz;

void setup() {
    delay(3000);
    Serial.begin(115200);
    Serial.println("Begin Stream");

    //Replace aithinker with your esp32cam model
    //Change the resolution of stream with one of you choice.
    //Default is vga 640x480 pixel
    //Camera quality can be changed.
    //Available quality: high, medium, low
    camera.pinout.aithinker();
    camera.brownout.disable();
    camera.resolution.vga();
    camera.quality.high();

    // init camera
    while (!camera.begin().isOk())
        Serial.println(camera.exception.toString());

    // connect to WiFi
    while (!wifi.connect().isOk())
        Serial.println(wifi.exception.toString());

    // start mjpeg http server
    while (!mjpeg.begin().isOk())
        Serial.println(mjpeg.exception.toString());

    Serial.println("Camera OK");
    Serial.println("WiFi OK");
    Serial.println("MjpegStream OK");
    Serial.println(mjpeg.address());
}


void loop() {
    // Leave Empty
}
