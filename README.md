# RT

![Desert Image](https://github.com/wehard/rt/blob/master/resources/screenshots/desert.jpg)

## Installation

Tested on MacOS Mojave/Catalina and Linux Ubuntu.
Requires MinilibX (for example this works https://github.com/pbondoer/MinilibX.git )
Run make on MinilibX and on copy libmlx.a (from root after make) to /usr/local/lib and mlx.h (from sierra dir on MacOS Catalina) to /usr/local/include
Clone this repository, run make and run program with ./RT [scene_file], for example ./RT resources/scenes/cat_house.csv

## Notes

Object of this project was to create scenes with ray tracing method and implement lots of extra functionality in addition to basic object drawing. 

Allowed functions were: open, read, write, close, malloc, free, perror, strerror, exit, all functions of the math library (-lm man man 3 math), all functions of the MinilibX or their equivalent in another graphic library and necessary funcions for extra functions. For extras we used pthread.h for multithreading, sys/stat.h to see if file was updated, stdarg.h to make multiple pointer free function, and time.h to count our rending times. Eveything else was made from scratch.

![Christmas Ball](https://github.com/wehard/rt/blob/master/resources/screenshots/sasus_christmas.jpg)

## Features
- CPU multithreading
  - Threadpooling (threads stand by waiting for new tasks instead of being created again always when needed)
- Camera and object start positions controlled with scene files
- Multiple shapes:
  - Cone
  - Cylinder
  - Plane (and disc, just fill radius field for plane)
  - Sphere
  - .obj mesh files (that can be exported from Blender for example)
    - Vertexes, texture/UV coordinates and normals are used for trifaces
- Bounding boxes (mesh objects and their trifaces are recursively boxed to make raytracing exponentially faster)
- Controls
  - Move camera with arrow keys
- Hot reload (refresh scene when scene file is modified
- Shadows (can be turned off globally)
  - Object transparency affects shadows
- Shading (objects are brightest when light comes from surface normal direction, can be turned off globally)
- Speculars (bright spots when light is mirrored to camera in small angle, will be automatically bigger if light is made bigger with soft shadow radius, can be turned off globally)
  - Surface matte / shine percentage can be adjusted per object
- Opacity (objects can be partially or completely transparent, can be turned off globally)
  - Percentage can be adjusted per object
- Refraction (light will bend if it hits refractive object, can be turned off globally)
  - Refraction value can be adjusted per object (adjustable 1f-2f, where 1 = air, 1.33 = water, 1.5 glass)
- Reflection (objects can be partially or completely mirrorlike, can be turned off globally)
  - Reflection percentage can be adjusted per object
- Fresnel (object with transparency behave like mirror when looked at from low angle)
  - Automatically on with refractive objects
- Bounces (maximum raycast recursions for reflective and refractive objects)
- Adjustable window width and height
- Multiple light sources
  - Ambient light
    - RGB colors
  - Spherical spot lights
    - RGB colors
    - Without or with light falloff (based on inverse-square law)
    - With harsh or soft shadows (makes light seem bigger)
      - Light radius (how big area of shadow is soft, simulates bigger lights)
      - Measure points (how many bounce points are used)
- Shape modifications
  - Position
  - Radius (for spheres and cylinders)
  - Angle (for cones)
  - RGB colors
  - Rotation
  - Scale (for spheres, cones and mesh files)
  - Material
- Material modifications
  - RGB colors (can overlay texture)
  - Shine (specular amount)
  - Opacity
  - Refraction (index)
  - Reflection
  - Surface displacement
    - Explode (randomize surface of sphere, cone, cylinder and plane)
    - Bump map for sphere radius (not smooth, breaks sphere a bit)
  - Texture
- Texture modifications
  - Procedural textures
    - Checkers
      -Texture setting 1 changes size relative to uv. Good starting value is 0.2
    - Bricks
      -Texture setting 1 changes the amount rows in uv. Setting 2 changes the size of mortar relative to brick heigth. 
        Good starting values are 10 and 0.33.
    - Perlin noise
      -Texture Setting 1 is the amount of octaves. (1 - 10) Settings 2 and 3 are persistance and frequency.
    - Sky texture
  - Camera modifications
    - Position and rotation
    - Depth of field
      - Focal length
      - Aperture
    - Aspect ratio (automatically calculated, but can also be stretched)
    - Fied off view
    - Perspective and ortographic types
  - RGB colors for procedural textures
  - Texture from file (.xpm .ppm)
