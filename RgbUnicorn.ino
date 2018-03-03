#include <FastLED.h>

constexpr int DATA_PIN = 2;
constexpr int NUM_COLORS = 8;
constexpr int NUM_LEDS = 30;
constexpr int BRIGHTNESS = 48;

// The color sequence that we'll be animating.
const CRGB colors[NUM_COLORS] = {
    CHSV(HUE_RED, 255, BRIGHTNESS),
    CHSV(HUE_ORANGE, 255, BRIGHTNESS),
    CHSV(HUE_YELLOW, 255, BRIGHTNESS),
    CHSV(HUE_GREEN, 255, BRIGHTNESS),
    CHSV(HUE_AQUA, 255, BRIGHTNESS),
    CHSV(HUE_BLUE, 255, BRIGHTNESS),
    CHSV(HUE_PURPLE, 255, BRIGHTNESS),
    CHSV(HUE_PINK, 255, BRIGHTNESS),
};
CRGBArray<NUM_LEDS> leds;


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
} // setup()

void loop() {
    // put your main code here, to run repeatedly:
    // Move the string of colors upwards.
    for (int dot_offset = 0;dot_offset < NUM_LEDS;dot_offset ++) {
        for (int dot = 0; dot < NUM_LEDS; dot ++) {
            CRGB color;
            if (dot < dot_offset) {
                color = CRGB::Black;
            } else if (dot >= dot_offset + NUM_COLORS) {
                color = CRGB::Black;
            } else {
                color = colors[dot - dot_offset];
            }
            leds[dot] = color;
        } // for dot
        FastLED.show();
        delay(100);
    } // for dot_offset

    // Now the colors fall back down.
    for (int dot_offset = NUM_LEDS;dot_offset >= 0;dot_offset --) {
        for (int dot = 0; dot < NUM_LEDS; dot ++) {
            CRGB color;
            if (dot < dot_offset) {
                color = CRGB::Black;
            } else if (dot >= dot_offset + NUM_COLORS) {
                color = CRGB::Black;
            } else {
                color = colors[dot - dot_offset];
            }
            leds[dot] = color;
        } // for dot
        FastLED.show();
        delay(10);
    } // for dot_offset

    // All off.
    memset(leds, 0, sizeof(leds));
//    for (int dot = 0;dot < NUM_LEDS;dot ++) {
//        leds[dot] = CRGB::Black;
//    } // for dot
    FastLED.show();
    delay(500);
} // loop()
