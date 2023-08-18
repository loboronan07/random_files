import cv2
import numpy as np
import matplotlib.pyplot as plt


def get_cumulative(histogram):
    cumulative = np.cumsum(histogram, dtype=np.float32)
    return cumulative / histogram.sum()


def get_hist_map(inp_histogram, ref_histogram):
    pix_map = np.zeros(256)

    k = 0
    for i, val in enumerate(inp_histogram):
        while k < 255 and ref_histogram[k] < val:
            k += 1

        pix_map[i] = k

    return np.array(pix_map, dtype=np.uint8)


def map_image(image, image_map):
    new_img = np.zeros_like(image, dtype=np.uint8)
    r, c = image.shape

    for i in range(r):
        for j in range(c):
            new_img[i, j] = image_map[image[i, j]]

    return new_img


def histogram_specification(inp_image, ref_image):
    inp_pixels = np.array(inp_image, dtype=np.uint8).ravel()
    ref_pixels = np.array(ref_image, dtype=np.uint8).ravel()

    inp_hist = np.histogram(inp_pixels, 255, [0, 255])[0]
    ref_hist = np.histogram(ref_pixels, 255, [0, 255])[0]

    inp_c = get_cumulative(inp_hist)
    ref_c = get_cumulative(ref_hist)

    img_map = get_hist_map(inp_c, ref_c)

    return map_image(inp_image, img_map)


inp_img = cv2.imread('inp_image.webp', 0)
ref_img = cv2.imread('ref_image.webp', 0)

new_img = histogram_specification(inp_img, ref_img)

fig, ax = plt.subplots(3, 2)

for i, img in enumerate([inp_img, ref_img, new_img]):
    ax[i, 0].imshow(img)
    ax[i, 1].plot(cv2.calcHist([img], [0], None, [255], [0, 255]))

plt.imshow(new_img, cmap='gray')
plt.show()
