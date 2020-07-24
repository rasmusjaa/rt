# RT

## Notes

Libft as submodule.

Use ```git submodule update --init``` to initialize.

## Features
- CPU multithreading
  - Threadpooling (threads stand by waiting for new tasks instead of being created again always when needed)
- Camera and object start positions controlled with scene files
- Multiple shapes:
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
- Shadows (can be turned off globally)
- Shading (objects are brightest when light comes from surface normal direction, can be turned off globally)
- Speculars (bright spots when light is mirrored to camera in small angle, will be automatically bigger if light is made bigger with soft shadow radius, can be turned off globally)
  - Surface matte / shine percentage can be adjusted per object
- Opacity (objects can be partially or completely transparent, can be turned off globally)
  - Percentage can be adjusted per object
- Refraction (light will bend if it hits refractive object, can be turned off globally)
  - Refraction value can be adjusted per object (adjustable 1f-2f, where 1 = air, 1.33 = water, 1.5 glass)
- Reflection (objects can be partially or completely mirrorlike, can be turned off globally)
  - Reflection percentage can be adjusted per object
- Fresnel (object with transparency behave like mirrored when looked at from low angle)
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
  - Direction (for cones, cylinders and planes)
  - Radius (for spheres and cylinders)
  - Angle (for cones)
  - RGB colors
  - Rotation
  - Scale (for spheres, cones and mesh files)
  - Opacity, refrection, reflaction and shine amount
