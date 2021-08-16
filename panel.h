typedef struct led
{
  int pin;
  int ch;
} led;

typedef struct rgb_led
{
  led r;
  led g;
  led b;
} rgb_led;

typedef struct panel
{
  rgb_led left;
  rgb_led mid;
  rgb_led right;
} panel;

// panel -> rgb_led(s) -> led -> pin|ch

panel p = {{
    {15, 6}, {32, 7}, {33, 8} //left led
  }, {
    {25, 3}, {26, 4}, {27, 5} // middle led
  }, {
    {14, 0}, {12, 1}, {13, 2} // right led
  }
};

int dutyCycle;
/* Setting PWM Properties */
const int PWMFreq = 5000; /* 5 KHz */
const int PWMChannel = 0;
const int PWMResolution = 12;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);

uint8_t color = 0;          // a value from 0 to 255 representing the hue
uint32_t R, G, B;           // the Red Green and Blue color components
uint8_t brightness = 255;  // 255 is maximum brightness, but can be changed.  Might need 256 for common anode to fully turn off.

void setLeds(rgb_led leds[]) {
  for (int i = 0; i < 3; i++) {
    ledcAttachPin(leds[i].r.pin, leds[i].r.ch);
    ledcAttachPin(leds[i].g.pin, leds[i].g.ch);
    ledcAttachPin(leds[i].b.pin, leds[i].b.ch);
    ledcSetup(leds[i].r.ch, PWMFreq, PWMResolution);
    ledcSetup(leds[i].g.ch, PWMFreq, PWMResolution);
    ledcSetup(leds[i].b.ch, PWMFreq, PWMResolution);
  }
}

void rgbWrite(rgb_led rgb, int r, int g, int b) {
  r = MAX_DUTY_CYCLE - map(r, 0, 256, 0, MAX_DUTY_CYCLE);
  g = MAX_DUTY_CYCLE - map(g, 0, 256, 0, MAX_DUTY_CYCLE);
  b = MAX_DUTY_CYCLE - map(b, 0, 256, 0, MAX_DUTY_CYCLE);

  ledcWrite(rgb.r.ch, r);
  ledcWrite(rgb.g.ch, g);
  ledcWrite(rgb.b.ch, b);
}

void rgbWriteAll(int r, int g, int b) {
  rgbWrite(p.left, r, g, b);
  rgbWrite(p.mid, r, g, b);
  rgbWrite(p.right, r, g, b);
}

void testPanel(rgb_led leds[]) {
  for (int i = 0; i < 3; i++) {
    rgbWrite(leds[i], 0, 0, 0);
    delay(500);
    rgbWrite(leds[i], 255, 0, 0);
    delay(500);
    rgbWrite(leds[i], 0, 255, 0);
    delay(500);
    rgbWrite(leds[i], 0, 0, 255);
    delay(500);
    rgbWrite(leds[i], 255, 255, 255);
  }
}

void lineerAll(int delayCoefficient) {
  int delayTime = 2 * delayCoefficient;
  //red
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    rgbWriteAll(dutyCycle, 0, 0);
    delay(delayTime);
  }
  for (dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    rgbWriteAll(dutyCycle, 0, 0);
    delay(delayTime);
  }

  //green
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    rgbWriteAll(0, dutyCycle, 0);
    delay(delayTime);
  }
  for (dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    rgbWriteAll(0, dutyCycle, 0);
    delay(delayTime);
  }

  //blue
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    rgbWriteAll(0, 0, dutyCycle);
    delay(delayTime);
  }
  for (dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    rgbWriteAll(0, 0, dutyCycle);
    delay(delayTime);
  }
}

void lineer(rgb_led led) {
  //red
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    rgbWrite(led, dutyCycle, 0, 0);
    delay(20);
  }
  for (dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    rgbWrite(led, dutyCycle, 0, 0);
    delay(20);
  }

  //green
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    rgbWrite(led, 0, dutyCycle, 0);
    delay(20);
  }
  for (dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    rgbWrite(led, 0, dutyCycle, 0);
    delay(20);
  }

  //blue
  for (dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    rgbWrite(led, 0, 0, dutyCycle);
    delay(20);
  }
  for (dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    rgbWrite(led, 0, 0, dutyCycle);
    delay(20);
  }
}

void hueToRGB(uint8_t hue, uint8_t brightness)
{
  uint16_t scaledHue = (hue * 6);
  uint8_t segment = scaledHue / 256; // segment 0 to 5 around the
  // color wheel
  uint16_t segmentOffset =
    scaledHue - (segment * 256); // position within the segment

  uint8_t complement = 0;
  uint16_t prev = (brightness * ( 255 -  segmentOffset)) / 256;
  uint16_t next = (brightness *  segmentOffset) / 256;

  if (true)
  {
    brightness = 255 - brightness;
    complement = 255;
    prev = 255 - prev;
    next = 255 - next;
  }

  switch (segment) {
    case 0:      // red
      R = brightness;
      G = next;
      B = complement;
      break;
    case 1:     // yellow
      R = prev;
      G = brightness;
      B = complement;
      break;
    case 2:     // green
      R = complement;
      G = brightness;
      B = next;
      break;
    case 3:    // cyan
      R = complement;
      G = prev;
      B = brightness;
      break;
    case 4:    // blue
      R = next;
      G = complement;
      B = brightness;
      break;
    case 5:      // magenta
    default:
      R = brightness;
      G = complement;
      B = prev;
      break;
  }
}

void fade(int delayCoefficient) {
  int delayTime = 20 * delayCoefficient;
  for (color = 0; color < 255; color++) { // Slew through the color spectrum
    hueToRGB(color, brightness);  // call function to convert hue to RGB
    rgbWriteAll(R,G,B);
    delay(delayTime); // 200ms full cycle of rgb over 256 colors takes 26 seconds
  }
}

void wave(int delayCoefficient) {
  int step = 8;
  int delayTime = 20 * delayCoefficient;
  for (color = 0; color < 255; color++) { // Slew through the color spectrum
    hueToRGB(color, brightness);  // call function to convert hue to RGB
    rgbWrite(p.left,R,G,B);
    hueToRGB(color+step, brightness);
    rgbWrite(p.mid,R,G,B);
    hueToRGB(color+ (step*2), brightness);
    rgbWrite(p.right,R,G,B);
    delay(delayTime); // 200ms full cycle of rgb over 256 colors takes 26 seconds
  }
}
