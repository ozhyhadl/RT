#include "kernel.h"

__kernel void	click_kernel(__global t_scene *scene,
							int	x,
							int	y,
							t_pov pov,
							__global int *id)
{
	double3	direction;

	direction = normalize(canvas_to_viewport(x - pov.w /2 , y - pov.h / 2, pov.w, pov.h, pov));
	direction = rotate_camera(direction, pov);

	t_obj_and_dist	obj_and_dist = check_closest_inter(pov.coord, direction, scene, 1, BIG_VALUE);
	*id = obj_and_dist.obj;
}
