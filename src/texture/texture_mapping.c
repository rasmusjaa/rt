
#include "rt.h"
/*
**
** Sphere mapping
**
*/


t_vec2    sphere_uv(t_vec3 point)
{
    t_vec2 uv;
    t_vec3 normal;

    normal = ft_normalize_vec3(ft_sub_vec3(point, ft_make_vec3(0, 0, 0)));
    uv.x = atan2(normal.x, normal.z) / (M_PI * 2.0) + 0.5;
    uv.y = normal.y * 0.5 + 0.5;
    return (uv);
}

t_vec2    cylinder_uv(t_vec3 point, double max, double min, double size)
{
    t_vec2 uv;
    t_vec3 normal;
    
    normal = ft_normalize_vec3(ft_sub_vec3(point, ft_make_vec3(0, 0, 0)));
    uv.x = atan2(normal.x, normal.y) / (M_PI * 2.0) + 0.5;
    //uv.y = (normal.y - min) / (max - min);
    min = 0;
	max = 0;
	uv.y = point.y size;
	
	return (uv);
}

t_vec2	plane_uv(t_vec3 point)
{
	t_vec2 uv;

	uv.x = point.x - floor(point.x);
	uv.y = point.z - floor(point.z);
	return (uv);
}
