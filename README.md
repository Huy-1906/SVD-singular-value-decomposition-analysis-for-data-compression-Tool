# SVD (singular value decomposition) analysis for data compression Tool
Copyright © 2025 Ho Chi Minh City University of Technology, HCMUT
> By:\
> Ly Gia Huy \<huy.lygiahuy2024bk@hcmut.edu.vn\> \
> and \
> Mai Quoc Khang \<tkhang.maiquoc2005@hcmut.edu.vn\>\
## Table of Contents
- [A. Overview](#Overview)  
- [B. Usage](#usage)  
- [C. Contributing](#contributing)  

## Overview
SVD (Singular Value Decomposition) is a method used in linear algebra to decompose a matrix into three simpler matrices, making it easier to analyze and manipulate.

U: This part tells you about the people (like their general preferences). \
Σ: This part shows how important each factor is (how much each rating matters).\
Vᵀ: This part tells you about the products (how similar they are to each other)

Name    | A   | B|
|-------|-----|-----|
| 1| 5  | 3   |
| 2| 4  | 2   |
| 3| 2  | 5   |

SVD breaks this table into three smaller parts: one that shows people’s preferences, one that shows the importance of each movie, and one that shows how similar the movies are to each other
Mathematically, the SVD of a matrix A (of size m×n) is represented as:
```bash
 A = UΣVᵀ
 ```

## Usage
## LIBRARIES NEED TO BE DOWNLOADED BEFORE USING (For Linux)
### 1. PyQt6
```bash
sudo apt install python3-pyqt6
```
### 2. libpng
```bash
sudo apt-get install libpng-dev

```
### 3. LAPACK
```bash
sudo apt-get install liblapack-dev
```
### 4. Numpy 
```bash
https://phoenixnap.com/kb/install-numpy
```
### 5. PIL (Pillow)
```bash
https://www.geeksforgeeks.org/how-to-install-pil-on-linux/
```
### LIBRARIES NEED TO BE DOWNLOADED BEFORE USING (For Windows)
### 1. PyQt6
```bash
pip install PyQt6
```
### 2. libpng
```bash
vcpkg install libpng
```
### 3. LAPACK
```bash
vcpkg install lapack
```
### 4. Numpy 
```bash
pip install numpy
```
### 5. PIL (Pillow)
```bash
pip install pillow
```
## The core of this program
1. Input image with png type
2. Form RGB channels \
-> we have R, G, B channels as matrices \
3. Use SVD algorithm to compress each channel
call the channels respectively R, G, B.
4. Select compression level
𝑘
GUI: enter coefficient k to compress.
5. Merge those channels and save them in image format with <name>_compressed.png
---
## How to use it
1. Run python code in GUI.py in SourceCode folder
2. Choose any photo with png type to compress
3. Input the K value in range [1,300] (Depending how strong your computer is, keep waiting until It's done, dont quit, dont give up like the way you spy on your crush ;3)
4. The compressed photo will be located in your SourceCode folder, you can change in it by modify the GUI.py if you want 
5. That's it!

## Contributing
2352384	Lương Đức HUy	huy.luong2352384@hcmut.edu.vn \
2452124	Lương Nguyễn Chí Bảo	bao.luongchi2452124@hcmut.edu.vn \
2452391	Lý Gia Huy	huy.lygiahuy2024bk@hcmut.edu.vn \
2352474	Mai Quốc Khang	khang.maiquoc2005@hcmut.edu.vn \
2452687	Ngô Hoàng Long	long.ngohoang23@hcmut.edu.vn \
2452446	Ngô Lê Kha	kha.ngo10@hcmut.edu.vn \
2452538	Nguyễn Anh Khoa	khoa.nguyenkonichiwa@hcmut.edu.vn

# Summary of the guidelines:
- One pull request per issue;
- Choose the right base branch;
- Include tests and documentation;
- Clean up "oops" commits before submitting;




