# Hướng Dẫn Đóng Góp Phát Triển Dự Án (Contributing Guidelines)

Cảm ơn bạn đã quan tâm và muốn đóng góp cải thiện dự án **Mạch Điều Khiển 4 Relay ESP32**! Chúng tôi luôn hoan nghênh các đóng góp từ tối ưu hóa mạch in, thiết kế vỏ hộp 3D, viết thêm firmware mẫu đến hoàn thiện tài liệu.

## Quy Chuẩn Phần Cứng
- **Phiên bản KiCad**: Dự án được xây dựng và hỗ trợ tốt nhất trên **KiCad v7 / v8 / v10**.
- **Thư viện linh kiện**: Mọi Symbol, Footprint và mô hình 3D mới phải được đặt trong thư mục `lib/` với đường dẫn tương đối (Project-relative path).
- **Kiểm tra ERC / DRC**: Trước khi gửi yêu cầu Pull Request (PR), vui lòng đảm bảo đã chạy kiểm tra lỗi nguyên lý (ERC) và luật thiết kế mạch in (DRC) mà không có lỗi nghiêm trọng.
- **An toàn cách ly**: Luôn tuân thủ khoảng cách cách ly an toàn (Creepage & Clearance) ở khu vực tiếp điểm điện áp cao 220V.

## Quy Trình Gửi Đóng Góp (Pull Request)
1. Fork dự án này về tài khoản GitHub của bạn.
2. Tạo một nhánh tính năng mới (`git checkout -b feature/tinh-nang-moi`).
3. Commit các thay đổi (`git commit -m 'feat: them tinh nang XYZ'`).
4. Đẩy lên nhánh của bạn (`git push origin feature/tinh-nang-moi`).
5. Mở một **Pull Request** trên GitHub kèm theo mô tả rõ ràng về thay đổi và ảnh chụp màn hình/render 3D nếu có.
