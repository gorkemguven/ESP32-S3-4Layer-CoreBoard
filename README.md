# ESP32-S3 4-Layer Core Board

High-performance 4-layer core board design based on the ESP32-S3 SoC, featuring impedance-controlled USB differential pairs and optimized power distribution.

---

## Table of Contents

- [Hardware Features](#hardware-features)
- [Pinout Map](#pinout-map)
- [Getting Started](#getting-started)
- [Firmware / Examples](#firmware--examples)
- [License](#license)

---

## Hardware Features

### 4-Layer PCB Stack-Up

The board uses a controlled-impedance 4-layer stack-up for signal integrity and low-noise power delivery:

| Layer | Name         | Function                                        |
|-------|--------------|-------------------------------------------------|
| L1    | Signal Top   | High-speed signals, USB differential pair, components |
| L2    | Ground Plane | Solid copper pour — primary return path / shield |
| L3    | Power Plane  | 3.3 V and other supply rails                    |
| L4    | Signal Bot   | Low-speed signals, indicator LEDs, connectors   |

**Stack-up parameters (JLCPCB JLC7628 prepreg + 1080 core):**

| Dielectric Layer | Thickness | Material     |
|------------------|-----------|--------------|
| L1 copper        | 35 µm (1 oz) | —          |
| L1–L2 prepreg    | 0.21 mm   | JLC 7628     |
| L2 copper        | 35 µm (1 oz) | —          |
| Core             | 1.065 mm  | FR-4         |
| L3 copper        | 35 µm (1 oz) | —          |
| L3–L4 prepreg    | 0.21 mm   | JLC 7628     |
| L4 copper        | 35 µm (1 oz) | —          |
| **Board total**  | **~1.6 mm** | —           |

### Impedance Control

- **USB 2.0 differential pair (D+ / D−):** 90 Ω differential impedance on L1, referenced to the L2 ground plane.
- **Single-ended traces (GPIO, SPI, I²C):** 50 Ω characteristic impedance on L1/L4.
- **Power planes** use stitching vias along the board perimeter and around high-current components for low-inductance return paths.

### USB-C Connector

- Integrated **USB Type-C** receptacle (USB 2.0 only).
- CC1 / CC2 lines pulled down with 5.1 kΩ resistors for host-mode power negotiation.
- ESD protection TVS diode on VBUS and data lines.
- Supports **USB Serial/JTAG** built into the ESP32-S3 (no external USB-to-UART bridge required for programming).

### Power Supply

- Input: **5 V via USB-C** (up to 500 mA with a standard USB host).
- On-board LDO regulates 5 V → **3.3 V** for the ESP32-S3, Flash, and PSRAM.
- Bulk decoupling: 100 µF electrolytic + multiple 100 nF ceramic capacitors per supply rail.

### ESP32-S3 SoC

- Dual-core Xtensa LX7 @ up to 240 MHz
- 512 KB SRAM, 16 KB RTC SRAM
- Integrated 2.4 GHz Wi-Fi (802.11b/g/n) and Bluetooth 5 (LE)
- USB OTG / USB Serial-JTAG controller
- 44 programmable GPIOs

### Onboard Peripherals

| Peripheral      | Component       | Interface | GPIO        |
|-----------------|-----------------|-----------|-------------|
| RGB LED         | WS2812B         | 1-Wire    | GPIO 48     |
| User LED        | Green LED       | —         | GPIO 2      |
| User Button     | Tactile switch  | —         | GPIO 0 (BOOT) |
| UART debug      | USB-C (internal JTAG/UART) | USB | — |

---

## Pinout Map

> Pin numbers refer to **ESP32-S3** GPIO numbers.

### Left Header (J1) — 20 pins

| Pin # | GPIO  | Default Function        | Notes                      |
|-------|-------|-------------------------|----------------------------|
| 1     | GND   | Ground                  |                            |
| 2     | 3V3   | 3.3 V output            | Max 300 mA draw            |
| 3     | 5V    | 5 V USB input           | Direct from USB-C VBUS     |
| 4     | IO4   | GPIO / ADC1_CH3         |                            |
| 5     | IO5   | GPIO / ADC1_CH4         |                            |
| 6     | IO6   | GPIO / ADC1_CH5         |                            |
| 7     | IO7   | GPIO / ADC1_CH6         |                            |
| 8     | IO15  | GPIO / ADC2_CH4         |                            |
| 9     | IO16  | GPIO / U1RXD (UART1)    |                            |
| 10    | IO17  | GPIO / U1TXD (UART1)    |                            |
| 11    | IO18  | GPIO / USB D−           | 90 Ω diff pair             |
| 12    | IO19  | GPIO / USB D+           | 90 Ω diff pair             |
| 13    | IO20  | GPIO / U1RXD            |                            |
| 14    | IO21  | GPIO / U1TXD            |                            |
| 15    | IO35  | GPIO / SPI MOSI         | SPI2                       |
| 16    | IO36  | GPIO / SPI MISO         | SPI2                       |
| 17    | IO37  | GPIO / SPI CLK          | SPI2                       |
| 18    | IO38  | GPIO / SPI CS           | SPI2                       |
| 19    | IO39  | GPIO / I²C SDA          | I²C0                       |
| 20    | IO40  | GPIO / I²C SCL          | I²C0                       |

### Right Header (J2) — 20 pins

| Pin # | GPIO  | Default Function        | Notes                      |
|-------|-------|-------------------------|----------------------------|
| 1     | GND   | Ground                  |                            |
| 2     | IO1   | GPIO / ADC1_CH0         |                            |
| 3     | IO2   | GPIO / User LED         | Active HIGH                |
| 4     | IO3   | GPIO / ADC1_CH2         |                            |
| 5     | IO8   | GPIO / ADC1_CH7         |                            |
| 6     | IO9   | GPIO / ADC1_CH8 / Touch |                            |
| 7     | IO10  | GPIO / ADC1_CH9 / Touch |                            |
| 8     | IO11  | GPIO / ADC2_CH0         |                            |
| 9     | IO12  | GPIO / ADC2_CH1         |                            |
| 10    | IO13  | GPIO / ADC2_CH2         |                            |
| 11    | IO14  | GPIO / ADC2_CH3         |                            |
| 12    | IO41  | GPIO                    |                            |
| 13    | IO42  | GPIO / MTDI (JTAG)      |                            |
| 14    | IO43  | GPIO / U0TXD (UART0)    | USB-CDC fallback TX        |
| 15    | IO44  | GPIO / U0RXD (UART0)    | USB-CDC fallback RX        |
| 16    | IO45  | GPIO / Strapping        | Boot mode                  |
| 17    | IO46  | GPIO / Strapping        | Boot mode (input only)     |
| 18    | IO47  | GPIO                    |                            |
| 19    | IO48  | RGB LED data            | WS2812B — do not drive externally |
| 20    | EN    | Chip Enable / Reset     | Active HIGH; pull LOW to reset |

---

## Getting Started

### Requirements

- [Arduino IDE 2.x](https://www.arduino.cc/en/software) **or** [PlatformIO](https://platformio.org/)
- ESP32 Arduino core ≥ 3.0 — install via Arduino Board Manager: `esp32 by Espressif Systems`
- USB-C cable

### Flashing via USB-C (no additional programmer needed)

1. Hold the **BOOT** button (GPIO 0), press and release **EN/RST**, then release **BOOT**.  
   *The ESP32-S3 USB-JTAG/Serial controller will enumerate as a COM/ttyACM port.*
2. Select **ESP32S3 Dev Module** in Arduino IDE (or `esp32-s3-devkitc-1` in PlatformIO).
3. Set **USB Mode** → *Hardware CDC and JTAG* and **Upload Speed** → *921600*.
4. Open the example sketch, click **Upload**.

---

## Firmware / Examples

### HelloWorld — RGB LED & Serial Test

Located in [`firmware/HelloWorld/HelloWorld.ino`](firmware/HelloWorld/HelloWorld.ino).

This sketch performs a **post-assembly hardware verification test**:

- Cycles the onboard WS2812B RGB LED through Red → Green → Blue.
- Prints diagnostic messages over the USB Serial port (115200 baud).

```cpp
// Quick preview — see the full sketch in firmware/HelloWorld/
#include <Adafruit_NeoPixel.h>

#define RGB_LED_PIN 48
#define RGB_LED_COUNT 1

Adafruit_NeoPixel led(RGB_LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  led.begin();
  Serial.println("ESP32-S3 Core Board — Hello World!");
}

void loop() {
  led.setPixelColor(0, led.Color(255, 0, 0)); led.show(); delay(500); // Red
  led.setPixelColor(0, led.Color(0, 255, 0)); led.show(); delay(500); // Green
  led.setPixelColor(0, led.Color(0, 0, 255)); led.show(); delay(500); // Blue
  led.setPixelColor(0, led.Color(0,   0,   0)); led.show(); delay(500); // Off
}
```

**Required Arduino Library:** `Adafruit NeoPixel` — install via Arduino Library Manager.

---

## License

This project is licensed under the **GNU General Public License v3.0**.  
See the [`LICENSE`](LICENSE) file for the full text.

> Hardware designs (schematics, PCB layout) are additionally released under the  
> [CERN Open Hardware Licence Version 2 – Strongly Reciprocal (CERN-OHL-S v2)](https://ohwr.org/cern_ohl_s_v2.txt).
