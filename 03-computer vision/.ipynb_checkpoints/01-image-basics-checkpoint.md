# Image Basics
This section is to get used to Numpy and OpenCV for image manipulation. Here states the codes use case by case

## 1. Goals
- Slice and Index elements from arrays
- Open and display images using Numpy, OpenCV

## 2. Numpy 
### 2.1. Opening an image
```python
from PIL import Image # Python Image Library

pic = Image.open('YOUR IMAGE')
pic_arr = np.asarray(pic)      # width x height x 3 (RGB)
```

### 2.2. RGB adjusts
```python
# Getting each intensity of RGB
pic_red = pic_arr[:, :, 0]
pic_green = pic_arr[:, :, 1]
pic_blue = pic_arr[:, :, 2]

plt.imshow(pic_red, cmap='gray') # shows the intensity, cmap defaults to a gradient color map
```

## 3. OpenCV
OpenCV is a Open Source library for real-time Computer Vision, developed by Intel. This contains many CV algorithms including object detection and tracking. 

OpenCV provides `imshow()` to open an image with a new window, but it interferes with jupytor kernel and makes it crash when exiting the window.
  - `cv2` provides fast and interactive window
    - suits for streaming/video/moving images  
  - Use `python` script instead

| ⚠️ no intellisense for conda environment

### 3.1. Opening an image
```python
# 1. Opening an image
# By default, OpenCV opens images in BGR format (historical reason)
# To convert it to RGB, use cv2.cvtColor
pic = cv2.imread('images/00-puppy.jpg')
pic = cv2.cvtColor(pic, cv2.COLOR_BGR2RGB)

# conversion isn't needed for gray-scale (1 byte per pixel)
pic_gray = cv2.imread('images/00-puppy.jpg', cv2.IMREAD_GRAYSCALE)
```


### 3.2. Image Manipulation
```python
# Resizing: note that 1 is for width and 0 for height
pic_small = cv2.resize(pic, (pic.shape[1]//10, pic.shape[0]//10))

# Flipping: 0: vertical, 1: horizontal, -1: both
pic_flip = cv2.flip(pic, 1) 
```

### 3.3. Saving an image
```python
cv2.imwrite('images/00-puppy-gray.jpg', pic_gray)
```

### 3.4. Drawing Shapes
- SEE: [OpenCV: Drawing Functions](https://docs.opencv.org/4.x/dc/da5/tutorial_py_drawing_functions.html)
```python
image_blank = np.zeros(shape=(512, 512, 3), dtype=np.uint16)
cv2.rectangle(
    image_blank, 
    pt1=(100, 100), 
    pt2=(300, 300), 
    color=(255, 0, 0), 
    thickness=5
)
cv2.circle(
    image_blank, 
    center=(400, 400), 
    radius=10, 
    color=(0, 255, 0), 
    thickness=5
)
# ...
```

### 3.5. Drawing Text/Polygon