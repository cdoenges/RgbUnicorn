#include <FastLED.h>

constexpr int DATA_PIN = 2;
constexpr int NUM_COLORS = 8;
constexpr int NUM_LEDS = 30;
constexpr int BRIGHTNESS = 52;

// The color sequence that we'll be animating.
constexpr uint8_t hues[NUM_COLORS] = {
    HUE_RED,
    HUE_ORANGE,
    HUE_YELLOW,
    HUE_GREEN,
    HUE_AQUA,
    HUE_BLUE,
    HUE_PURPLE,
    HUE_PINK,
};

const CRGB colors[NUM_COLORS + 1] = {
    CHSV(HUE_RED, 255, BRIGHTNESS),
    CHSV(HUE_ORANGE, 255, BRIGHTNESS),
    CHSV(HUE_YELLOW, 255, BRIGHTNESS),
    CHSV(HUE_GREEN, 255, BRIGHTNESS),
    CHSV(HUE_AQUA, 255, BRIGHTNESS),
    CHSV(HUE_BLUE, 255, BRIGHTNESS),
    CHSV(HUE_PURPLE, 255, BRIGHTNESS),
    CHSV(HUE_PINK, 255, BRIGHTNESS),
    CHSV(0, 0, 0),  // Black
};
CRGBArray<NUM_LEDS> leds;


static int random_in_range(const int low=0, const int high=100) {
    const int delta = high - low;
    const int r = rand();
    int value;

    value = r / (RAND_MAX / delta) + low;
    return value;
} // random_in_range()


static void run_up(void) {
    // Move the string of colors upwards.
    for (int dot_offset = 0;dot_offset < NUM_LEDS;dot_offset ++) {
        for (int dot = 0; dot < NUM_LEDS; dot ++) {
            CRGB color;
            if (dot < dot_offset) {
                color = CRGB::Black;
            } else if (dot >= dot_offset + NUM_COLORS) {
                color = CRGB::Black;
            } else {
                color = CHSV(hues[dot - dot_offset], 255, BRIGHTNESS + dot_offset);
            }
            leds[dot] = color;
        } // for dot
        FastLED.show();
        delay(random_in_range(75, 200));
    } // for dot_offset
} // run_up()


static void fall_down(void) {
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
        delay(random_in_range(5, 25));
    } // for dot_offset
} // fall_down()


static void fade_off(void) {
    // Fade all off.
    for (int i = 16;i > 0;i --) {
        leds.fadeToBlackBy(16);
        FastLED.show();
        delay(random_in_range(10, 20));
    }
} // fade_off()


static void sparkle(void) {
    for (int i = 0;i < 1000;i ++) {
        int led_index = random_in_range(NUM_LEDS - 8, NUM_LEDS);
        CRGB color = CHSV(random_in_range(0, 255),
                          random_in_range(128, 255),
                          random_in_range(BRIGHTNESS - 16, BRIGHTNESS + 16));

        leds[led_index] = color;
        FastLED.show();
        delay(5);
    } // for i
} // sparkle()



void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
} // setup()

void loop() {
    // put your main code here, to run repeatedly:
    run_up();

    sparkle();

    fall_down();

    fade_off();

    delay(random_in_range(500, 2500));
} // loop()
