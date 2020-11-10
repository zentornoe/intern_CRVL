# intern_CRVL

## Imaging Source
A program that simultaneously acquires 5 images from 5 imaging source camera.

GUI : MFC, program code : C++

Developed by using Imaging Source SDK.


* * *

## COLMAP & Hole Filling

After image capture(from capturing program), create a 3D model and a Depth map using **COLMAP**.

### COLMAP
INPUT : 5 x 5 image file (each images gap : 10 cm)

OUTPUT(that I used) : 3D point cloud file(*.ply), Depth map(RGB colored)

Then, fill the holes in the depth map using the Weighted Median Filtering and disparity.

#### 1) Disparity image
<img src="https://user-images.githubusercontent.com/58382336/98517247-f0888780-22b0-11eb-9947-8846370175b6.png"  width="700" height="370">

#### 2) Depth map
<img src="https://user-images.githubusercontent.com/58382336/98517179-dc448a80-22b0-11eb-9d00-060f979b8b88.png"  width="700" height="370">

#### 3) Disparity Hole filling
<img src="https://user-images.githubusercontent.com/58382336/98517354-24fc4380-22b1-11eb-9ff4-298959954466.png"  width="700" height="370">

#### 4) Weighted Median Filtering depth map
<img src="https://user-images.githubusercontent.com/58382336/98517179-dc448a80-22b0-11eb-9d00-060f979b8b88.png"  width="700" height="370">
