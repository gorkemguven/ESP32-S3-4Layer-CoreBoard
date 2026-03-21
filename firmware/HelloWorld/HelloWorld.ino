/**
 * HelloWorld.ino
 * -----------------------------------------------------------------------
 * Post-assembly hardware verification sketch for the ESP32-S3 4-Layer
 * Core Board.
 *
 * What it tests
 * -------------
 *  1. USB Serial communication — prints a startup banner and a live
 *     loop counter at 115200 baud.
 *  2. Onboard WS2812B RGB LED (GPIO 48) — cycles through Red, Green,
 *     Blue, and Off with a 500 ms dwell on each colour.
 *  3. Onboard user LED (GPIO 2) — mirrors the RGB colour phase so you
 *     can confirm the basic GPIO output path even without a Serial port.
 *
 * Required library
 * ----------------
 *  Adafruit NeoPixel  (install via Arduino Library Manager)
 *
 * Board settings (Arduino IDE)
 * ----------------------------
 *  Board      : ESP32S3 Dev Module
 *  USB Mode   : Hardware CDC and JTAG
 *  Upload Spd : 921600
 *
 * License: GPL-3.0  — see repository root LICENSE file
 * -----------------------------------------------------------------------
 */

#include <Adafruit_NeoPixel.h>

// ── Pin definitions ───────────────────────────────────────────────────
#define RGB_LED_PIN    48   // WS2812B data line
#define RGB_LED_COUNT   1   // single LED on the core board
#define USER_LED_PIN    2   // green user LED (active HIGH)

// ── Timing ────────────────────────────────────────────────────────────
#define DWELL_MS      500   // ms per colour phase

// ── NeoPixel object ───────────────────────────────────────────────────
Adafruit_NeoPixel rgbLed(RGB_LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// ── Colour table (R, G, B) ────────────────────────────────────────────
struct Colour { uint8_t r, g, b; const char* name; };

static const Colour colours[] = {
    {255,   0,   0, "RED"  },
    {  0, 255,   0, "GREEN"},
    {  0,   0, 255, "BLUE" },
    {  0,   0,   0, "OFF"  },
};
static const uint8_t NUM_COLOURS = sizeof(colours) / sizeof(colours[0]);

// ── State ─────────────────────────────────────────────────────────────
static uint8_t  colourIndex = 0;
static uint32_t lastChange  = 0;
static uint32_t loopCount   = 0;

// ─────────────────────────────────────────────────────────────────────
void setup() {
    // Serial
    Serial.begin(115200);
    // Brief wait so a newly-enumerated USB-CDC port has time to open
    delay(1500);

    Serial.println();
    Serial.println("=====================================================");
    Serial.println("  ESP32-S3 4-Layer Core Board — Hello World!");
    Serial.println("  Hardware verification sketch");
    Serial.println("=====================================================");
    Serial.printf("  RGB LED pin : GPIO %d\n", RGB_LED_PIN);
    Serial.printf("  User LED pin: GPIO %d\n", USER_LED_PIN);
    Serial.printf("  Dwell time  : %d ms per colour\n", DWELL_MS);
    Serial.println("-----------------------------------------------------");
    Serial.println("  Cycling colours: RED → GREEN → BLUE → OFF ...");
    Serial.println();

    // User LED
    pinMode(USER_LED_PIN, OUTPUT);
    digitalWrite(USER_LED_PIN, LOW);

    // NeoPixel
    rgbLed.begin();
    rgbLed.setBrightness(64);  // ~25 % — comfortable for bare viewing
    rgbLed.clear();
    rgbLed.show();

    lastChange = millis();
}

// ─────────────────────────────────────────────────────────────────────
void loop() {
    uint32_t now = millis();

    if (now - lastChange >= DWELL_MS) {
        const Colour& c = colours[colourIndex];

        // Drive RGB LED
        rgbLed.setPixelColor(0, rgbLed.Color(c.r, c.g, c.b));
        rgbLed.show();

        // Mirror on user LED: ON for any non-black colour, OFF otherwise
        digitalWrite(USER_LED_PIN, (c.r || c.g || c.b) ? HIGH : LOW);

        // Log to Serial
        Serial.printf("[%6lu] Loop #%lu  →  Colour: %-6s  (R=%3d G=%3d B=%3d)\n",
                      now, ++loopCount, c.name, c.r, c.g, c.b);

        colourIndex = (colourIndex + 1) % NUM_COLOURS;
        lastChange  = now;
    }
}
