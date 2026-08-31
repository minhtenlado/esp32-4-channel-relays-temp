# Bảng Danh Mục Linh Kiện (BOM) - Mạch Điều Khiển 4 Relay ESP32

Danh mục linh kiện đầy đủ cho mạch điều khiển 4 Relay cách ly quang ESP32-WROOM-32.

| STT | Số lượng | Ký hiệu (Designator) | Giá trị / Tên linh kiện | Đóng gói (Footprint) | Chức năng / Mô tả chi tiết |
| :---: | :---: | :--- | :--- | :--- | :--- |
| 1 | 1 | `U4` | ESP32-WROOM-32 | Module SMD | Vi điều khiển 32-bit Wi-Fi & Bluetooth Dual-Core |
| 2 | 4 | `K1, K2, K3, K4` | SRD-05VDC-SL-C | THT Relay | Relay 5VDC SPDT (Đóng ngắt 10A 250VAC / 10A 30VDC) |
| 3 | 4 | `U5, U6, U7, U8` | PC817 | SMDIP-4 | Optocoupler cách ly quang bảo vệ vi điều khiển |
| 4 | 4 | `Q2, Q3, Q4, Q5` | BC547A / NPN | SOT-23 | Transistor NPN đóng ngắt cuộn hút 5V của Relay |
| 5 | 4 | `D3, D5, D7, D9` | 1N4007 | MELF / DO-213AB | Diode dập xung điện áp ngược khi ngắt cuộn dây (1A 1000V) |
| 6 | 4 | `D2, D4, D6, D8` | LED Đỏ | 0805 SMD | Đèn LED hiển thị trạng thái kích hoạt Kênh 1 - 4 |
| 7 | 1 | `D1` | LED Vàng | 0805 SMD | Đèn LED báo nguồn 3.3V của mạch |
| 8 | 4 | `J1, J2, J3, J4` | Domino 3 Chân (Terminal) | Bước chân 5.08mm | Cọc đấu nối ra tải điện (NO - Thường mở, COM - Chung, NC - Thường đóng) |
| 9 | 1 | `USB1` | Type-C 16-Pin | HRO-TYPE-C-31-M-12 | Cổng USB Type-C cấp nguồn 5V và nạp dữ liệu |
| 10 | 1 | `U2` | CH340C | SOIC-16 | IC chuyển đổi USB sang UART tích hợp sẵn dao động thạch anh |
| 11 | 1 | `Q1` | MBT3904DW1 | SOT-363 / SC-70-6 | Cặp transistor NPN kép trong mạch tự động nạp & reset |
| 12 | 1 | `U1` | AMS1117-3.3 | SOT-223-3 | IC ổn áp tuyến tính 3.3V 1A cấp nguồn cho ESP32 |
| 13 | 1 | `U3` | PRTR5V0U2X | SOT-143 | Diode TVS chống tĩnh điện ESD cho 2 đường dữ liệu USB |
| 14 | 1 | `F1` | Cầu chì PTC 500mA | 1206 SMD | Cầu chì tự phục hồi chống quá dòng cổng USB |
| 15 | 2 | `SW1, SW2` | Nút nhấn nhả (Tactile) | SKQG SMD 6x6mm | Nút bấm RESET (SW1) và nút BOOT (SW2) |
| 16 | 8 | `R9, R10, R11, R12, R13, R14, R15, R16` | 1kΩ 1% | 0805 SMD | Điện trở hạn dòng cho LED opto và phân cực cực B transistor |
| 17 | 3 | `R6, R7, R8` | 10kΩ 1% | 0805 SMD | Điện trở kéo lên (Pull-up) cho chân EN, IO0 và BOOT |
| 18 | 2 | `R2, R3` | 5.1kΩ 1% | 0805 SMD | Điện trở kéo xuống cấu hình nhận diện cổng USB Type-C (CC1, CC2) |
| 19 | 2 | `R4, R5` | 22Ω 1% | 0805 SMD | Điện trở phối hợp trở kháng trên đường dữ liệu USB D+ / D- |
| 20 | 1 | `R1` | 2kΩ 1% | 0805 SMD | Điện trở hạn dòng cho đèn LED báo nguồn D1 |
| 21 | 3 | `C1, C2, C7` | 22µF 16V | 0805 SMD | Tụ gốm lọc nguồn chính đường 5V và 3.3V |
| 22 | 6 | `C3, C4, C5, C6, C8, C9` | 0.1µF (100nF) 50V | 0805 SMD | Tụ gốm lọc nhiễu cao tần (Decoupling) |

> **Ghi chú**: Các điện trở và tụ điện SMD sử dụng chuẩn chân **0805** giúp việc hàn thủ công bằng mỏ hàn tay dễ dàng và đẹp mắt.
