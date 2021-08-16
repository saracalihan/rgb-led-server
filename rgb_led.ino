#include "panel.h"
#include "server.h"

String selectedJob = "null";
int displayTime = 1;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup start...");
  setupServer();
  rgb_led leds[3] = {p.left, p.mid, p.right};
  setLeds(leds);
  Serial.println("Setup finish");
  testPanel(leds);
}


void loop()
{
  selectedJob = startServerLoop();
  Serial.println(selectedJob);
  if (selectedJob != "null") {
    if (selectedJob == "red") {
      rgbWriteAll(255, 0, 0);
    } else if (selectedJob == "green") {
      rgbWriteAll(0, 255, 0);
    } else if (selectedJob == "blue") {
      rgbWriteAll(0, 0, 255);
    } else if (selectedJob.indexOf("wave/") != -1) {
      displayTime = selectedJob.substring(5, 7).toInt();
      wave(displayTime);
    } else if (selectedJob.indexOf("lineer/") != -1) {
      displayTime = selectedJob.substring(7, 9).toInt();
      lineerAll(displayTime);
    } else if (selectedJob.indexOf("fade/") != -1) {
      displayTime = selectedJob.substring(5, 7).toInt();
      fade(displayTime);
    } else if (selectedJob.indexOf("rgb/") != -1) {
      int number = (int) strtol( &selectedJob[4], NULL, 16);
      // Split them up into r, g, b values
      int r = number >> 16;
      int g = number >> 8 & 0xFF;
      int b = number & 0xFF;
      rgbWriteAll(r, g, b);
    }
  }
}
