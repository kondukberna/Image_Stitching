## Clone the repository
```
git clone https://github.com/kondukberna/Image_Stitching.git
```

## Build
```
mkdir build && build
cmake ..
make
```

## Run

Have to use firstly -resize flag with the resize rate. If you want to use an image with the original size, it can be set to 1.

```
./imagestitcher -resize 0.5 -direction horizontal /images/DSC02930.JPG /images/DSC02930.JPG /images/DSC02931.JPG /images/DSC02932.JPG /images/DSC02933.JPG 
```

## Result

Horizontal images are from this [dataset](https://cs.adelaide.edu.au/~tjchin/apap/#Datasets). Vertical images are from this [dataset](https://github.com/visionxiang/Image-Stitching-Dataset#SPHP). 

# Horizontal Result

![](https://github.com/kondukberna/Image_Stitching/blob/main/images/StitchedImage.jpg)

# Vertical Result

![](https://github.com/kondukberna/Image_Stitching/blob/main/images/StitchedImage-Vertical.jpg)
