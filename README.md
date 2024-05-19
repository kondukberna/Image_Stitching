## Clone the repository
'''
git clone https://github.com/kondukberna/Image_Stitching.git
'''

## Build
'''
cd end2end && mkdir build && build
cmake ..
make
'''

## Run

Have to use firstly -resize flag with the resize rate. If you want to use an image with the original size, it can be set to 1.

'''
./imagestitcher -resize 0.5 /images/DSC02930.JPG /images/DSC02930.JPG /images/DSC02931.JPG /images/DSC02932.JPG /images/DSC02933.JPG 
'''

## Result

Images are from this [dataset](https://cs.adelaide.edu.au/~tjchin/apap/#Datasets). 

![](https://github.com/kondukberna/Image_Stitching/blob/main/images/StitchedImage.jpg)
