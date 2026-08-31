<div align="center">

# ⚡ ESP32 4-Channel Opto-Isolated Relay Board

An open-source, production-ready **ESP32-based 4-Channel Relay Controller** designed in KiCad. Featuring full optical isolation, USB Type-C programming with auto-reset, ESD protection, and safety creepage slots for smart home automation and industrial IoT switching.

[![KiCad](https://img.shields.io/badge/Designed%20with-KiCad-blue?logo=kicad&logoColor=white)](https://www.kicad.org/)
[![Hardware](https://img.shields.io/badge/Hardware-CERN--OHL--P%20v2-green)](LICENSE)
[![Firmware](https://img.shields.io/badge/Firmware-MIT-yellow)](LICENSE)
[![ESP32](https://img.shields.io/badge/MCU-ESP32--WROOM--32-red?logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Home Assistant](https://img.shields.io/badge/Home%20Assistant-ESPHome%20Ready-41BDF5?logo=homeassistant&logoColor=white)](firmware/esphome/esp32_4ch_relay.yaml)

<br/>

<img src="images/board_3d_top.png" alt="ESP32 4-Channel Relay Board 3D Top View" width="750"/>

</div>

---

## 🌟 Key Features

- 🧠 **Dual-Core ESP32 Microcontroller**: ESP32-WROOM-32 with 2.4 GHz Wi-Fi & Bluetooth LE 4.2.
- 🔌 **4x Independent SPDT Relays**: Songle SRD-05VDC-SL-C switching up to **10A @ 250VAC / 10A @ 30VDC**.
- 🛡️ **Galvanic Opto-Isolation**: PC817 optocouplers isolate 3.3V microcontroller logic from noisy 5V relay coils.
- ⚡ **USB Type-C Interface**: Modern Type-C port (HRO-TYPE-C-31-M-12) for both 5V power supply and serial flashing.
- 🔄 **Auto-Flash & Reset Circuit**: Onboard CH340C USB-UART bridge with MBT3904DW1 dual-transistor auto-download logic (no manual button pressing required).
- 🔒 **Hardware Protection**:
  - 500mA Resettable PTC Polyfuse (`F1`).
  - PRTR5V0U2X TVS Diode Array ESD protection on USB data lines (`U3`).
  - 1N4007 flyback suppression diodes across all relay coils (`D3, D5, D7, D9`).
  - High-voltage isolation slots (creepage air gaps) between relay contacts and low-voltage digital circuits.
- 💡 **Visual LED Feedback**:
  - Yellow Power LED (`D1`).
  - 4x Red Channel Activation LEDs (`D2, D4, D6, D8`).
- 📶 **Optimized RF Antenna**: Unobstructed PCB antenna placement with dedicated RF keep-out area.

---

## 📸 Gallery & PCB Layout

<div align="center">
  <table>
    <tr>
      <td align="center"><b>3D Top View</b></td>
      <td align="center"><b>3D Bottom View</b></td>
    </tr>
    <tr>
      <td><img src="images/board_3d_top.png" width="380" alt="Top 3D View"/></td>
      <td><img src="images/board_3d_bottom.png" width="380" alt="Bottom 3D View"/></td>
    </tr>
    <tr>
      <td colspan="2" align="center"><b>PCB 2D Layout & Routing</b></td>
    </tr>
    <tr>
      <td colspan="2" align="center"><img src="images/pcb_layout_2d.png" width="600" alt="PCB Layout"/></td>
    </tr>
  </table>
</div>

---

## 📋 Technical Specifications

| Parameter | Specification |
| :--- | :--- |
| **Microcontroller** | ESP32-WROOM-32 (Xtensa 32-bit LX6 dual-core, up to 240 MHz) |
| **Input Power** | 5V DC via USB Type-C Receptacle |
| **Operating Logic Level** | 3.3V DC (Onboard AMS1117-3.3 Linear Regulator) |
| **Relay Channels** | 4 Channels (Form C - SPDT: NO, COM, NC) |
| **Relay Model** | SRD-05VDC-SL-C (5VDC Nominal Coil) |
| **Contact Rating (AC)**| 10A 250VAC / 10A 125VAC |
| **Contact Rating (DC)**| 10A 30VDC / 10A 28VDC |
| **Connectors** | 4x 3-Pin 5.08mm Pitch Screw Terminals |
| **Isolation Type** | PC817 Phototransistor Optocoupler + PCB Isolation Slots |
| **USB-UART Chip** | CH340C (Built-in Crystal) |
| **Firmware Ecosystem** | Arduino IDE, ESP-IDF, PlatformIO, ESPHome, Tasmota |

---

## 📌 Pinout & GPIO Mapping

| Function | ESP32 GPIO | Active State | Optocoupler | Driver | Status Indicator | Output Connector |
| :--- | :---: | :---: | :---: | :---: | :---: | :--- |
| **Relay 1** | `GPIO 21` | HIGH | U5 (PC817) | Q2 (BC547A) | `D2` (Red LED) | **J1** (NO, COM, NC) |
| **Relay 2** | `GPIO 19` | HIGH | U6 (PC817) | Q3 (BC547A) | `D4` (Red LED) | **J2** (NO, COM, NC) |
| **Relay 3** | `GPIO 18` | HIGH | U7 (PC817) | Q4 (BC547A) | `D6` (Red LED) | **J3** (NO, COM, NC) |
| **Relay 4** | `GPIO 5`  | HIGH | U8 (PC817) | Q5 (BC547A) | `D8` (Red LED) | **J4** (NO, COM, NC) |
| **UART RX**  | `GPIO 3`  | - | - | - | CH340C TXD | Internal USB-UART |
| **UART TX**  | `GPIO 1`  | - | - | - | CH340C RXD | Internal USB-UART |
| **BOOT SW**  | `GPIO 0`  | LOW | - | - | `SW2` Button | Manual Bootloader |
| **RESET SW** | `EN`      | LOW | - | - | `SW1` Button | System Reset |
| **Power LED**| `+3.3V`   | Constant | - | - | `D1` (Yellow LED) | Power Rail |

👉 For full signal breakdowns and strapping pin documentation, see [docs/PINOUT.md](docs/PINOUT.md).

---

## 🗂️ Project File Structure

```text
.
├── esp32-4-channel-relays.kicad_pro   # KiCad 7/8/10 Project file
├── esp32-4-channel-relays.kicad_sch   # KiCad Schematic file
├── esp32-4-channel-relays.kicad_pcb   # KiCad PCB Layout file
├── schematic.pdf                      # Exported Schematic in PDF
├── images/                            # 3D board renders & PCB layout captures
│   ├── board_3d_top.png
│   ├── board_3d_bottom.png
│   └── pcb_layout_2d.png
├── lib/                               # Project-specific KiCad libraries
│   ├── 3dmodel/                       # 3D STEP & WRL CAD models
│   ├── footprint/                     # Custom KiCad footprints
│   └── symbol/                        # Custom KiCad schematic symbols
├── docs/                              # Hardware documentation
│   ├── BOM.md                         # Bill of Materials (Markdown table)
│   ├── BOM.csv                        # Bill of Materials (CSV format)
│   └── PINOUT.md                      # Detailed Pinout reference
├── firmware/                          # Ready-to-flash sample firmware
│   ├── arduino/esp32_4ch_relay_web/   # Arduino Sketch with Web Interface & REST API
│   └── esphome/esp32_4ch_relay.yaml   # ESPHome Home Assistant configuration
├── .github/                           # GitHub actions CI & issue templates
├── .gitignore                         # KiCad and build output ignore rules
├── CONTRIBUTING.md                    # Guidelines for contributing
├── LICENSE                            # CERN-OHL-P v2 & MIT License
└── README.md                          # Main project documentation
```

---

## 🚀 Quick Start & Firmware Setup

### 1. Arduino Web Interface
A lightweight, modern web server sketch is provided in [`firmware/arduino/esp32_4ch_relay_web/`](firmware/arduino/esp32_4ch_relay_web/esp32_4ch_relay_web.ino).

1. Open `esp32_4ch_relay_web.ino` in Arduino IDE.
2. Select **Board**: `ESP32 Dev Module`.
3. Update your Wi-Fi credentials:
   ```cpp
   const char* WIFI_SSID = "YOUR_WIFI_SSID";
   const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
   ```
4. Connect the board via USB Type-C and click **Upload** (auto-reset circuit handles programming mode automatically).
5. Open your browser and navigate to `http://esp32-relay.local` or the assigned IP address.

### 2. Home Assistant (ESPHome)
For native Home Assistant integration:

1. Install [ESPHome](https://esphome.io/).
2. Open [`firmware/esphome/esp32_4ch_relay.yaml`](firmware/esphome/esp32_4ch_relay.yaml).
3. Flash the firmware via USB:
   ```bash
   esphome run firmware/esphome/esp32_4ch_relay.yaml
   ```
4. Home Assistant will auto-discover all 4 relay entities instantly!

---

## ⚠️ High-Voltage Electrical Safety Notice

> [!WARNING]
> **HIGH VOLTAGE WARNING**: Switching mains AC electricity (110V - 250V AC) is hazardous and can cause serious injury or death.
> - Ensure all power is disconnected before connecting or servicing screw terminals.
> - Always house the PCB inside a non-conductive, fire-retardant enclosure when switching AC mains.
> - Verify that your load current does not exceed the relay and PCB trace thermal ratings.

---

## 📦 Bill of Materials (BOM)

A complete list of components with manufacturer footprint details is available:
- 📄 [View BOM Markdown Table](docs/BOM.md)
- 📊 [Download BOM CSV](docs/BOM.csv)
- 📑 [View Schematic PDF](schematic.pdf)

---

## 📄 License & Credits

- **Hardware Design**: Licensed under the **[CERN-OHL-P v2](https://cern-ohl.web.cern.ch/)** (CERN Open Hardware Licence Version 2 - Permissive).
- **Firmware & Documentation**: Licensed under the **[MIT License](LICENSE)**.
- **Designed by**: **Phan Huỳnh Văn Đô** (`2023 - 2026`).
