import ctypes
import sys
import time
from PyQt6.QtWidgets import (
    QApplication, QWidget, QLabel, QVBoxLayout, QPushButton, QFileDialog, QProgressBar, QMessageBox, QLineEdit
)
from PyQt6.QtCore import Qt, QThread, pyqtSignal
from PyQt6.QtGui import QPixmap
import cv2
import numpy as np

# Load thư viện C
svd_lib = ctypes.CDLL("./svd_compression.so")
svd_lib.compress_image.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]

def compress_image(input_path, k, output_path):
    svd_lib.compress_image(input_path.encode('utf-8'), k, output_path.encode('utf-8'))

class CompressThread(QThread):
    progress = pyqtSignal(int)
    done = pyqtSignal(str)
    
    def __init__(self, input_file, k, output_file):
        super().__init__()
        self.input_file = input_file
        self.k = k
        self.output_file = output_file
    
    def run(self):
        for i in range(1, 51):  # Mô phỏng tiến trình chạy
            time.sleep(0.05)
            self.progress.emit(i * 2)
        compress_image(self.input_file, self.k, self.output_file)
        self.done.emit(self.output_file)

class CompressingTool(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("SVD Image Compression Tool")
        self.setStyleSheet("background-color: #222; color: white; font-size: 16px;")
        self.resize(600, 600)

        layout = QVBoxLayout()
        
        self.logo_label = QLabel(self)
        pixmap = QPixmap("logo_bk.png")
        self.logo_label.setPixmap(pixmap)
        self.logo_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(self.logo_label)

        self.label = QLabel("Image Compression Tool")
        self.label.setStyleSheet("font-size: 24px; font-weight: bold;")
        self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(self.label)

        self.choose_file_btn = QPushButton("Choose Image File")
        self.choose_file_btn.setStyleSheet("background: blue; color: white; padding: 12px; border-radius: 5px;")
        self.choose_file_btn.clicked.connect(self.choose_file)
        layout.addWidget(self.choose_file_btn)

        self.image_preview = QLabel()
        layout.addWidget(self.image_preview)
        
        self.k_input = QLineEdit()
        self.k_input.setPlaceholderText("Enter compression level (any positive integer)")
        self.k_input.setStyleSheet("background: white; color: black; padding: 5px; font-size: 14px;")
        layout.addWidget(self.k_input)

        self.compress_btn = QPushButton("Compress Image")
        self.compress_btn.setStyleSheet("background: green; color: white; padding: 12px; border-radius: 5px;")
        self.compress_btn.clicked.connect(self.start_compression)
        layout.addWidget(self.compress_btn)

        self.progress = QProgressBar()
        self.progress.setValue(0)
        layout.addWidget(self.progress)

        self.setLayout(layout)
        
        self.selected_file = ""

    def choose_file(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Choose Image", "", "Images (*.png *.jpg *.jpeg)")
        if file_name:
            self.choose_file_btn.setText(file_name)
            self.selected_file = file_name
            pixmap = QPixmap(file_name).scaled(300, 300, Qt.AspectRatioMode.KeepAspectRatio)
            self.image_preview.setPixmap(pixmap)
    
    def start_compression(self):
        if not self.selected_file:
            QMessageBox.warning(self, "Warning", "Please choose an image first!")
            return
        
        try:
            k = int(self.k_input.text())
            if k <= 0:
                raise ValueError
        except ValueError:
            QMessageBox.warning(self, "Warning", "Please enter a valid positive integer for compression level!")
            return
        
        output_file = "compressed_image.jpg"
        
        self.thread = CompressThread(self.selected_file, k, output_file)
        self.thread.progress.connect(self.progress.setValue)
        self.thread.done.connect(self.show_done)
        self.thread.start()
    
    def show_done(self, file_name):
        QMessageBox.information(self, "Done", f"Compression completed! Saved as {file_name}")
        pixmap = QPixmap(file_name).scaled(300, 300, Qt.AspectRatioMode.KeepAspectRatio)
        self.image_preview.setPixmap(pixmap)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CompressingTool()
    window.show()
    sys.exit(app.exec())
