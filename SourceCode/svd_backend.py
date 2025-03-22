import numpy as np
from PIL import Image
import os

def open_image(image_path):
    """ Mở ảnh PNG và tách thành 3 kênh màu R, G, B """
    im_orig = Image.open(image_path).convert("RGB")
    im = np.array(im_orig)

    a_red = im[:, :, 0]
    a_green = im[:, :, 1]
    a_blue = im[:, :, 2]

    return a_red, a_green, a_blue, im_orig


def compress_single_channel(channel_matrix, k):
    """ Nén 1 kênh màu bằng SVD """
    u, s, vh = np.linalg.svd(channel_matrix, full_matrices=False)
    s_k = np.zeros((k, k))
    np.fill_diagonal(s_k, s[:k])
    compressed = np.dot(u[:, :k], np.dot(s_k, vh[:k, :]))
    return np.clip(compressed, 0, 255).astype(np.uint8)


def compress_image(image_path, k, output_path):
    """ Nén toàn bộ ảnh bằng SVD với hệ số K """
    a_red, a_green, a_blue, original = open_image(image_path)

    # Nén từng kênh màu
    red_compressed = compress_single_channel(a_red, k)
    green_compressed = compress_single_channel(a_green, k)
    blue_compressed = compress_single_channel(a_blue, k)

    # Hợp nhất thành ảnh mới
    im_r = Image.fromarray(red_compressed)
    im_g = Image.fromarray(green_compressed)
    im_b = Image.fromarray(blue_compressed)
    new_image = Image.merge("RGB", (im_r, im_g, im_b))

    # Lưu ảnh
    new_image.save(output_path)

    return output_path
