# Internship in CRVL ( Computer and Robot Vision Lab. )
※ For security reasons, **I can't upload all the program codes**.

## Imaging Source
A program that simultaneously acquires 5 images from 5 imaging source camera.

Developed by using Imaging Source SDK.

| OS| GUI | Program Language |
|:---:|:---:|:---:|
| Windows 10 | MFC | C++|




* * *

## COLMAP & Hole Filling

After image capture(from capturing program), create a 3D model and a Depth map using **COLMAP**.

### 1. Device ( Cameras )
**Imaging Source cameras**

<img src="https://user-images.githubusercontent.com/58382336/98678629-35401b80-23a2-11eb-8dca-1740b499f675.png"  width="300" height="160">          <img src="https://user-images.githubusercontent.com/58382336/98679207-01192a80-23a3-11eb-9660-9b8d48a3bcc7.png"  width="380" height="160">


### 2. 5x5 Images
<img src="https://user-images.githubusercontent.com/58382336/98681554-35421a80-23a6-11eb-81d6-613147f48862.png"  width="700" height="450">

### 3. Flow Chart
<img src="https://user-images.githubusercontent.com/58382336/98679165-f52d6880-23a2-11eb-9d72-cb5c4d12cdeb.png"  width="700" height="450">


### 4. COLMAP
INPUT : 5 x 5 image file (each images gap : 10 cm)

OUTPUT(that I used) : 3D point cloud file(*.ply), Depth maps(RGB colored), Disparity images

Then, fill the holes in the depth map using the Weighted Median Filtering and disparity.

#### 1) Disparity image
<img src="https://user-images.githubusercontent.com/58382336/98517247-f0888780-22b0-11eb-9947-8846370175b6.png"  width="700" height="370">

#### 2) Depth map
<img src="https://user-images.githubusercontent.com/58382336/98517179-dc448a80-22b0-11eb-9d00-060f979b8b88.png"  width="700" height="370">

### 5. Hole Filling

#### 1) RGB image that used in WFM
<img src="https://user-images.githubusercontent.com/58382336/98680245-79ccb680-23a4-11eb-965d-31c8cc28cbde.png"  width="700" height="370">

#### 2) After Hole filling & WFM disparity image
<img src="https://user-images.githubusercontent.com/58382336/98680257-7cc7a700-23a4-11eb-8665-55334172449d.png"  width="700" height="370">


* * * 

## Real Sense SDK
| OS | SDK | Program Laguage |
|:---:|:---:|:---:|
| Ubuntu 18.04 | Intel RealSense SDK | C++ |


|Used device |
|:---:|
|Intel RealSense - T265(IMU, Twin Fisheye Cameras) & D435(Color & Depth Cameras)|
|Jetson Nano|

### 1. What I Want ?
Based on the previous 5x5 images processing technique, the internship period ended while developing a program to acquire and store images 1 frame per second for processing depth and color video(continuous discarity images).
