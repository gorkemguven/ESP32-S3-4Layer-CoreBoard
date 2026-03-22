# ESP32-S3 Multi-Sensor & High-Performance Development Board

## 1. Project Overview
This repository contains the complete hardware design for a high-performance development board powered by the **ESP32-S3-WROOM-1-N16R2** ($16\text{MB}$ Flash / $2\text{MB}$ PSRAM). This board is engineered for advanced IoT applications, environmental monitoring, and analog signal processing, featuring a robust power management system and high-fidelity sensor integration on a **4-layer PCB**.

---

## 2. Technical Specifications

### 2.1 Core System
*   **Microcontroller:** ESP32-S3 Dual-core Xtensa LX7 MCU, Wi-Fi & BLE 5.0.
*   **Memory:** $16\text{MB}$ Quad SPI Flash and $2\text{MB}$ PSRAM.
*   **External Storage:** 
    *   **MicroSD Card:** Integrated via SPI with dedicated pull-up resistors and decoupling.
    *   **External Flash:** **W25Q32JVSSIQ** ($32\text{M-bit}$) for redundant data logging or specific firmware needs.

### 2.2 Power Management & Battery
The power stage is designed for high reliability and seamless power transitions:
*   **Battery Charger:** **MCP73871** with System Power Path Management, allowing simultaneous battery charging and system operation.
*   **Protection:** VPCC (Voltage Proportional Charge Control) set to **$4.92\text{V}$** to prevent source collapse.
*   **Regulation:** **XC6220B331MR-G** high-current LDO providing a stable **$3.3\text{V}$** rail at up to **$1\text{A}$**.
*   **Input:** USB-C ($SS-52400-002$) with $5.1\text{k}\Omega$ resistors on CC lines for universal power delivery compatibility.
*   **Visual Indicators:** Dedicated LEDs for Charging (Red), Charge Complete (Green), and Power Good (Blue).

### 2.3 Sensors & Analog Input
*   **Environmental:** **BME280** (I2C) for high-precision pressure, temperature, and humidity sensing ($0\text{x}76$ address).
*   **Audio:** **MAX4466** low-noise microphone pre-amplifier with integrated $10\text{Hz}-20\text{kHz}$ bandwidth support.
*   **Light Sensing:** **TEMT6000X01** ambient light sensor for precise illuminance measurements.
*   **Signal Integrity:** Separate **Analog Ground (GNDA)** plane connected via a $0\Omega$ bridge to minimize digital switching noise in analog measurements.

### 2.4 Communication & Programming
*   **USB-to-UART:** **CP2102N** for high-speed serial communication (up to $3\text{Mbps}$).
*   **ESD Protection:** **USBLC6-2SC6** monolithic ESD protection on USB Data ($D+/D-$) and VBUS lines.
*   **Auto-Program Circuit:** Dual **BC817** NPN transistor logic for seamless "Auto-Reset" and "Boot" entry during firmware flashing.

---

## 3. PCB Design Details
*   **Layer Count:** 4 Layers (Signal - GND - VCC - Signal).
*   **Stack-up Strategy:** Internal Ground and Power planes to ensure low EMI and high power integrity for Wi-Fi/BT peaks.
*   **Impedance Control:** USB data lines are routed as **$90\Omega$** differential pairs.
*   **Passive Components:** Optimized decoupling using a mix of **X7R Ceramic** ($0.1\text{ }\mu\text{F}$ / $1\text{ }\mu\text{F}$) and **Low-ESR Tantalum** ($10\text{ }\mu\text{F}$ / $22\text{ }\mu\text{F}$) capacitors.

---

## 4. Repository Structure
*   `PROJE.kicad_sch`: Hierarchical schematic design files.
*   `PROJE.kicad_pcb`: 4-layer PCB layout with optimized trace routing.
*   `/docs`: Full schematic in PDF format and comprehensive Bill of Materials (BOM).

---

## 5. About the Author
**Görkem Güven**  
Electrical & Electronics Engineering Student  
*Muğla Sıtkı Koçman University*  
Expertise in Embedded Systems, Hardware Design, and Mixed-Signal PCB Layout.

---

