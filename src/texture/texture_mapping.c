/*
**
** Sphere mapping
**
*/

typedef struct  s_uv
{
    double u;
    double v;
}               t_uv;

t_uv    sphere_uv(t_vec3 point)
{
    t_uv uv;
    t_vec3 normal;

    normal = vec3_normalize(vec3_sub(point, new_vec3(0, 0, 0)));
    uv.u = atan2(normal.x, normal.y) / (M_PI * 2) + 0.5;
    uv.v = normal.y * 0.5 + 0.5;
    return (uv);
}

t_uv    cylinder_uv(t_vec3 point, double max, double min)
{
    t_uv uv;
    t_vec3 normal;
    
    normal = vec3_normalize(vec3_sub(point, new_vec3(0, 0, 0)));
    uv.u = atan2(normal.x, normal.y) / (M_PI * 2) + 0.5;
    uv.v = (normal.y - min) / (max - min);
    return (uv);
}
