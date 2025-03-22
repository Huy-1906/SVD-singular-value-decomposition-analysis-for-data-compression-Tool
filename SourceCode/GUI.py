import sys
from PyQt6.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QFileDialog, QVBoxLayout, QSpinBox, QHBoxLayout
)
from PyQt6.QtGui import QPixmap
from PyQt6.QtCore import Qt
import os
from svd_backend import compress_image

class ImageCompressorGUI(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()
        self.image_path = ""

    def initUI(self):
        self.setWindowTitle("Photo Compressing Tool by using SVD")
        self.setGeometry(100, 100, 600, 400)

        # Label hiển thị ảnh gốc
        self.label_original = QLabel("Ảnh Gốc", self)
        self.label_original.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.label_original.setStyleSheet("border: 1px solid black;")

        # Label hiển thị ảnh đã nén
        self.label_compressed = QLabel("Ảnh Nén", self)
        self.label_compressed.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.label_compressed.setStyleSheet("border: 1px solid black;")

        # Nút chọn file ảnh
        self.btn_choose_file = QPushButton("Chọn Ảnh PNG", self)
        self.btn_choose_file.clicked.connect(self.openFileDialog)

        # Nút chạy nén ảnh
        self.btn_compress = QPushButton("Nén Ảnh", self)
        self.btn_compress.clicked.connect(self.compressImage)

        # SpinBox chọn giá trị K
        self.spin_k = QSpinBox(self)
        self.spin_k.setRange(1, 300)  # Giá trị K có thể chỉnh từ 1 - 300
        self.spin_k.setValue(50)

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.label_original)
        layout.addWidget(self.btn_choose_file)

        hbox = QHBoxLayout()
        hbox.addWidget(QLabel("Hệ số K:"))
        hbox.addWidget(self.spin_k)
        layout.addLayout(hbox)

        layout.addWidget(self.btn_compress)
        layout.addWidget(self.label_compressed)
        self.setLayout(layout)

    def openFileDialog(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "Chọn Ảnh", "", "PNG Images (*.png)")
        if file_path:
            self.image_path = file_path
            self.showImage(file_path, self.label_original)

    def compressImage(self):
        if not self.image_path:
            return

        k = self.spin_k.value()
        output_path = os.path.splitext(self.image_path)[0] + f"_compressed_K{k}.png"

        compressed_img_path = compress_image(self.image_path, k, output_path)
        self.showImage(compressed_img_path, self.label_compressed)

    def showImage(self, image_path, label):
        pixmap = QPixmap(image_path)
        pixmap = pixmap.scaled(300, 200, Qt.AspectRatioMode.KeepAspectRatio)
        label.setPixmap(pixmap)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ImageCompressorGUI()
    window.show()
    sys.exit(app.exec())
