# Sơ Đồ Chân (Pinout) & Cấu Trúc Phần Cứng ESP32 4-Channel Relays

## 1. Bảng Ánh Xạ Chân Điều Khiển 4 Kênh Relay

Vi điều khiển ESP32 điều khiển từng kênh relay thông qua tầng cách ly quang Optocoupler và transistor đệm dòng.

| Kênh | Chân ESP32 | Optocoupler | Transistor kích | LED Trạng thái | Diode dập xung | Cổng kết nối (Domino) | Mức kích hoạt |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Relay 1** | `GPIO 21` | U5 (PC817) | Q2 (BC547A) | D2 (Đỏ) | D3 (1N4007) | J1 (NO, COM, NC) | Mức CAO (`HIGH`) |
| **Relay 2** | `GPIO 19` | U6 (PC817) | Q3 (BC547A) | D4 (Đỏ) | D5 (1N4007) | J2 (NO, COM, NC) | Mức CAO (`HIGH`) |
| **Relay 3** | `GPIO 18` | U7 (PC817) | Q4 (BC547A) | D6 (Đỏ) | D7 (1N4007) | J3 (NO, COM, NC) | Mức CAO (`HIGH`) |
| **Relay 4** | `GPIO 5`  | U8 (PC817) | Q5 (BC547A) | D8 (Đỏ) | D9 (1N4007) | J4 (NO, COM, NC) | Mức CAO (`HIGH`) |

*Ghi chú*: Mạch được thiết kế kích ở **Mức CAO** (Xuất tín hiệu `HIGH` sẽ làm sáng LED bên trong Optocoupler, kích dẫn Transistor BC547A đóng cuộn hút Relay và làm sáng LED đỏ báo hiệu).

---

## 2. Ý Nghĩa Các Tiếp Điểm Trên Cọc Đấu Nối Domino (5.08mm)

Mỗi kênh Relay đi ra 1 cọc domino 3 chân có nhãn:
- **NO (Normally Open - Thường mở)**: Tiếp điểm hở mạch khi relay chưa được kích hoạt, đóng mạch khi relay có điện.
- **COM (Common - Chân chung)**: Chân chung để đấu nguồn điện cấp cho tải.
- **NC (Normally Closed - Thường đóng)**: Tiếp điểm đóng mạch khi relay chưa được kích hoạt, hở mạch khi relay có điện.

---

## 3. Kiến Trúc Cung Cấp Nguồn Điện

| Đường nguồn | Nguồn cấp vào | IC điều chỉnh | Dòng tối đa | Mục đích sử dụng |
| :--- | :--- | :--- | :--- | :--- |
| **+5V (VBUS)** | Cổng USB Type-C | Qua cầu chì F1 (500mA PTC) | ~500mA - 1A | Cấp nguồn cuộn hút 4 Relay (SRD-05VDC-SL-C) |
| **+3.3V** | Từ đường 5V | IC Hạ áp AMS1117-3.3 (U1) | 1A | Cấp nguồn cho ESP32-WROOM-32, IC nạp CH340C |
| **GND** | Cổng USB Type-C | Mặt phẳng GND chung | - | Mass toàn hệ thống |

---

## 4. Mạch Tự Động Nạp (Auto-Download) & Nút Nhấn

| Tín hiệu / Linh kiện | Chân ESP32 | Chức năng |
| :--- | :--- | :--- |
| **TXD (CH340C TX)** | `GPIO 3` (RXD0) | Nhận dữ liệu UART0 từ máy tính vào ESP32 |
| **RXD (CH340C RX)** | `GPIO 1` (TXD0) | Truyền dữ liệu UART0 từ ESP32 lên máy tính |
| **DTR / RTS** | `EN` / `GPIO 0` | Tín hiệu tự động reset / vào bootloader qua Q1 (MBT3904DW1) |
| **Nút SW1 (RESET)** | `EN` (CHIP_PU) | Nút reset phần cứng (Mức THẤP, có trở kéo 10k và tụ lọc nhiễu 0.1uF) |
| **Nút SW2 (BOOT)** | `GPIO 0` | Nút kích hoạt chế độ Bootloader thủ công (Mức THẤP, có trở kéo 10k) |

---

## 5. Bảng Chân Cấu Hình Khởi Động ESP32 (Strapping Pins)

| Chân GPIO | Trạng thái mặc định | Kết nối trên mạch | Lưu ý khi lập trình |
| :--- | :--- | :--- | :--- |
| `GPIO 0` | Kéo lên (+3.3V qua 10k) | Nối nút SW2 / Mạch nạp Q1 | Kéo xuống LOW lúc khởi động để vào chế độ nạp ROM |
| `GPIO 2` | Kéo xuống LOW nội | Bỏ trống | Giữ ở mức LOW hoặc thả nổi khi nạp firmware |
| `GPIO 5` | Mức CAO lúc boot | **Kích Relay 4** | Có xung phát ra lúc ESP32 vừa bật nguồn, hoạt động bình thường |
| `GPIO 12` | Kéo xuống LOW (MTDI) | Bỏ trống | Chọn điện áp Flash 3.3V |
| `GPIO 15` | Mức CAO (MTDO) | Bỏ trống | Bật/tắt chế độ in log bootloader qua UART |
