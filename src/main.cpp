#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 19
#define DATA_PIN 0
#define ONESEC 1015

#define MIN_CLR CRGB::Green
#define TEN_CLR CRGB::Blue
#define SEC_CLR CRGB::Red

int sec = 0;

CRGB leds[NUM_LEDS];

void display(void);
void write_min(int min);
void write_tens(int ten);
void write_sec(int sec);
void countdown(void);

void setup() {
	Serial.begin(115200);
	delay(1000);

	pinMode(DATA_PIN, OUTPUT);

	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(255);
	FastLED.clear(true);

    delay(1000);

	fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(100);
    }

	FastLED.clear(true);
	delay(1000);

	countdown();
}

void loop() {
	display();
	delay(ONESEC);

	sec = (sec + 1) % 420;
}

void display() {
	FastLED.clear();

	write_min(sec / 60);
	write_tens((sec % 60) / 10);
	write_sec(sec % 10);

	FastLED.show();
}

void write_min(int min) {
	for (int i = 1; i <= min; i++) {
		leds[5 - i] = MIN_CLR;
	}
}

void write_tens(int ten) {
	for (int i = 0; i < ten; i++) {
		leds[5 + i] = TEN_CLR;
	}
}

void write_sec (int sec) {
	for (int i = 1; i <= sec; i++) {
		leds[19 - i] = SEC_CLR;
	}
}

void countdown(void) {
	for (int i = 5; i > 0; i--) {
		FastLED.clear();
		write_sec(i);
		FastLED.show();

		delay(ONESEC);
	}
}