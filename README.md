# RT

## Notes

Libft as submodule.

Use ```git submodule update --init``` to initialize.

## Features
- CPU multithreading
  - Threadpooling (threads stand by waiting for new tasks instead of being created again always when needed)
- Camera and object start positions controlled with scene files
- Usable shapes:
  - Cone
  - Cylinder
  - Plane
  - Sphere
  - .obj mesh files (that can be exported from Blender for example)
    - Vertexes, texture/UV coordinates and normals are used for trifaces
- Bounding boxes (mesh objects and their trifaces are recursively boxed to make raytracing exponentially faster)
- Controls
  - Move camera with arrow keys
- Hot reload (refresh scene when scene file is modified
- Shadows
  - Off
  - On
- Shading (objects are brightest when light comes from surface normal direction)
  - Off
  - On
- Speculars (bright spots when light is mirrored to camera in small angle, will be automatically bigger if light is made bigger with soft shadow radius)
  - Off
  - On
  - Surface matte / shine percentage per object
- Opacity (objects can be partially or completely transparent)
  - Off
  - On
  - Percentage per object
- Refraction (light will bend if it hits refractive object)
  - Off
  - On
  - Adjustable per object (adjustable 1f-2f, where 1 = air, 1.33 = water, 1.5 glass)
- Reflection (objects can be partially or completely mirrorlike)
  - Off
  - On
  - Adjustable per object
- Fresnel (object with transparency behave like mirrored when looked at from low angle)
  - Automatically on with refractive objects
- Bounces (maximum raycst recursions for reflective and refractive objects)
- Window width and height
- Multiple light sources
  - Ambient light
    - Rgb colors
  - Spherical spot lights
    - Rgb colors
    - Without or with light falloff (based on inverse-square law)
    - With harsh or soft shadows (makes light seem bigger)
      - Light radius (how big area of shadow is soft, simulates bigger lights)
      - Measure points (how many bounce points are used)
