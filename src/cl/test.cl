#include "kernel.hh"

double3	reflected_ray(double3 normal, double3 prim_ray)
{
	return (prim_ray - 2 * dot(normal, prim_ray) * normal);
}

double3	beers_law(double distance, double3 obj_absorb)
{
	return (exp(obj_absorb * (-distance)));
}

double fresnel(double3 prim_ray, double3 normal, double n1)
{
	double cosX = -dot(prim_ray, normal); 
	double n2 = 1.00029;
	if (cosX > 0)
		swap(&n1, &n2);
	double r0 = (n1 - n2) / (n1 + n2);
	r0 *= r0;
	if (n1 > n2)
	{
		double n = n1 / n2;
		double sinT2 = n * n * (1.0 - cosX * cosX);
		if (sinT2 > 1.0)
			return 1.0;
		cosX = sqrt(1.0 - sinT2);
	}
	double x = 1.0 - cosX;
	double ret = r0 + (1.0 - r0) * x * x * x * x * x;
	return (ret);
}

double3	refract_ray(double3 prim_ray, double3 normal, double ior_new)
{
	double		cosi = dot(normal, prim_ray);
	double		ior_prev = 1.00029;
	double		k;

	if (cosi < 0)
	{
		cosi = -cosi;
	}
	else
	{
		normal = -normal;
		swap(&ior_prev, &ior_new);
	}
	double		eta = ior_prev / ior_new;

	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? 0 : eta * prim_ray + (eta * cosi - sqrt(k)) * normal);
}

double3	get_intersity_after_shadow_rays(double3 intersect_point, double3 light_dir, \
										__global t_scene *scene, double min_range, \
										double max_range, __global t_light *light)
{
	double3			local_intensity;
	t_obj_and_dist	obj_and_dist;
	double			intensity_level;

	local_intensity = light->intensity;
	intensity_level = length(local_intensity);
	while (intensity_level > MINIMUM_INTENSITY)
	{
		obj_and_dist = check_closest_inter(intersect_point, light_dir, scene, min_range, max_range);
	
		if (obj_and_dist.obj != -1)
		{
			local_intensity *= scene->obj[obj_and_dist.obj].trans;
			intensity_level *= scene->obj[obj_and_dist.obj].trans;
			intersect_point = intersect_point + light_dir * obj_and_dist.dist;
		}
		else
			break ;
	}
	return (local_intensity);
}		

double3	calculate_light(__global t_scene *scene, double3 eye, \
						double3 dir, double3 normal, double3 intersect_point, \
						t_fig fig, __global uint *texture, __global t_txt_params *txt_params, double2 texture_space_coords)
{
	int		i;
	__global t_light	*light;
	double	t_max;
	double3	intensity = 0;
	double3	light_dir;
	double	scalar;
	double3	reflect_ray;
	double3	local_intensity;
	double3	new_normal;
	double	light_len;
	double3	pix_color;
	
	if (fig.normal_map_no > -1)
	{
		double3	A = (double3)(1, 0, 0);
		double3	t = normalize(cross(A, normal));
		double3 b = normalize(cross(normal, t));
		double3	normal_from_map = uint_to_double3(get_texture_pixel(texture_space_coords, texture, txt_params[fig.normal_map_no], fig.normal_map_no));
		double3 du = normal_from_map[0] / 255 * 2 - 1;
		double3 dv = normal_from_map[1] / 255 * 2 - 1;
		new_normal = normalize(normal - du * t + dv * b);
	}
	else if (fig.noise == 4)
	{
		double3	A = (double3)(1, 0, 0);
		double3	t = normalize(cross(A, normal));
		double3 b = normalize(cross(normal, t));
		double3	noise = ft_noise2(texture_space_coords);
		noise = (double3)(fabs(150 - noise[0]), 140 * (sin(noise[1] / 255 * 2 * M_PI) + 1), 100 * (cos(noise[2] / 255 * 2 * M_PI) + 1));
		double3 du = noise[0] / 255 * 2 - 1;
		double3 dv = noise[1] / 255 * 2 - 1;
		new_normal = normalize(normal - du * t + dv * b);
	}
	else
		new_normal = normal;
	
	
	if (fig.text_no > -1)
		pix_color = uint_to_double3(get_texture_pixel(texture_space_coords, texture, txt_params[fig.text_no], fig.text_no));
	else if (fig.noise == 0)
	{
		pix_color = ft_noise(texture_space_coords);
		pix_color = (double3)(fabs(150 - pix_color[0]), 140 * (sin(pix_color[1] / 255 * 2 * M_PI) + 1), 100 * (cos(pix_color[2] / 255 * 2 * M_PI) + 1));
	}
	else if (fig.noise == 1)
		pix_color = ft_noise1(texture_space_coords);
	else if (fig.noise == 2)
	{
		pix_color = ft_noise2(texture_space_coords);
		pix_color = (double3)(fabs(50 - pix_color[0]), 40 * (sin(pix_color[1] / 255 * 2 * M_PI) + 1), 255 * (cos(pix_color[2] / 255 * 2 * M_PI) + 1));
	}
	else if (fig.noise == 3)
	{
		pix_color = ft_noise3(texture_space_coords);
		pix_color = (double3)(fabs(150 - pix_color[0]), 255 * (sin(pix_color[1] / 255 * 2 * M_PI) + 1), 40 * (cos(pix_color[2] / 255 * 2 * M_PI) + 1));
	}
	else
		pix_color = fig.color;

	i = -1;
	while (++i < scene->count_light)
	{
		light = scene->light + i;
		if (light->type_num == AMBIENT)
			intensity += light->intensity;
		else
		{
			if (light->type_num == POINT)
				light_dir = light->v - intersect_point;
			else
				light_dir = light->v;
			t_max = (light->type_num == POINT) ? 1 : BIG_VALUE;
			local_intensity = get_intersity_after_shadow_rays(intersect_point, light_dir, scene, EPSILON, t_max, light);
			if (length(local_intensity) < MINIMUM_INTENSITY)
				continue ;
			light_len = length(light_dir);
			if (fig.specular > 0)
			{						
				reflect_ray = reflected_ray(new_normal, light_dir);
				scalar = dot(reflect_ray, dir);
				if (scalar > 0)
				{
					scalar = pow(scalar / (length(-dir) * length(reflect_ray)), fig.specular);
					if (light->type_num == POINT)
						scalar /= light_len;
					intensity += local_intensity * scalar;
				}
			}
			scalar = dot(new_normal, light_dir);
			if (scalar > 0)
			{
				scalar = (scalar / light_len);
				if (light->type_num == POINT)
					scalar /= light_len;
				intensity += scalar * local_intensity;
			}
		}
	}
	return (pix_color * intensity);
}

double3		ray_trace(double3 eye, double3 dir, __global t_scene *scene, double min_range, double max_range, __global uint *texture, __global t_txt_params *txt_params, float *zbuff)
{
	double3		normal;
	double3		local_color;

	int			count = 1;
	int			curr = 0;
	double3		color = 0;
	double		trans;
	double2		texture_space_coords;

	double3		intersect_point;
	t_obj_and_dist	obj_and_dist;
	

	t_fig				fig;
	t_raytrace_tree		curr_node;

	t_raytrace_tree		tree[tree_nodes];
	
	tree[0].part_of_primary_ray = 1;
	tree[0].start = eye;
	tree[0].dir = dir;
	tree[0].min_range = min_range;
	tree[0].max_range = max_range;

	while (curr < count)
	{
		curr_node = tree[curr];
		obj_and_dist = check_closest_inter(curr_node.start, curr_node.dir, scene, curr_node.min_range, curr_node.max_range);
		if (obj_and_dist.obj != -1)
		{
			fig = scene->obj[obj_and_dist.obj];
			intersect_point = curr_node.start + curr_node.dir * obj_and_dist.dist;
			if ((fig.normal_map_no > -1) || (fig.text_no > -1) || (fig.transparancy_map_no > -1) || fig.noise > -1)
				texture_space_coords = get_texture_space_coords(intersect_point, fig);
			if (fig.transparancy_map_no == -1)
				trans = fig.trans;
			else
			{
				trans = uint_to_double3(get_texture_pixel(texture_space_coords, texture, txt_params[fig.transparancy_map_no], fig.transparancy_map_no))[0];
				trans = 1 - trans / 255;
			}
			normal = calculate_normal(fig, intersect_point, curr_node);

			local_color = calculate_light(scene, curr_node.start, curr_node.dir, normal, intersect_point, fig, texture, txt_params, texture_space_coords);
			local_color *= curr_node.part_of_primary_ray;
			double fren = 0;
			fren = fresnel(curr_node.dir, normal, fig.ior);
			if (trans > 0 && count < tree_nodes)
			{
				tree[count].part_of_primary_ray = curr_node.part_of_primary_ray * (1 - fren) * trans;
				if (tree[count].part_of_primary_ray > MINIMUM_INTENSITY)
				{
					local_color *= (1 - trans);
					tree[count].start = intersect_point;
					tree[count].dir = normalize(refract_ray(curr_node.dir, normal, fig.ior));
					tree[count].min_range = EPSILON;
					tree[count].max_range = BIG_VALUE;
					count++;	
				}
			}
			if (fig.reflective > 0 && count < tree_nodes)
			{
				tree[count].part_of_primary_ray = curr_node.part_of_primary_ray * (fig.reflective * (1 - trans) + trans * fren);
				if (tree[count].part_of_primary_ray > MINIMUM_INTENSITY)
				{
					local_color *= (1 - fig.reflective);
					tree[count].start = intersect_point;
					tree[count].dir = reflected_ray(normal, curr_node.dir);
					tree[count].min_range = EPSILON;
					tree[count].max_range = BIG_VALUE;
					count++;
				}
			}
			color += local_color;
			if (curr == 0)
				*zbuff = length(intersect_point - eye);
			curr++;
		}
		else
		{
			color += BACKGROUND_COLOR * curr_node.part_of_primary_ray;
			if (curr == 0)
				*zbuff = BIG_VALUE;
			curr++;
			continue ;
		}
	}
	return (color);
}

double3	canvas_to_viewport(int x, int y, int w, int h, t_pov pov)
{
	return ((double3){(double)x * pov.vw / w, \
								-(double)y * pov.vh / h, (double)pov.d});
}

__kernel void	test_kernel(__global t_scene *scene,
							__global uint *canvas,
							t_pov pov,
							__global uint *texture,
							__global t_txt_params *txt_params,
							__global float *zbuffer)
{
	int	id = get_global_id(0);
	int	x = id % pov.w;
	int	y = id / pov.w;
	double3	direction;
	float	zbuff;
	double3	color;

	direction = normalize(canvas_to_viewport(x - pov.w /2 , y - pov.h / 2, pov.w, pov.h, pov));
	direction =	new_basis(direction, pov.pov_rm);
	color = ray_trace(pov.coord, direction, scene, 0.1, BIG_VALUE, texture, txt_params, &zbuff);
	color = trim_color(color);
	
	canvas[id] = color_to_canvas(color);
	zbuffer[id] = zbuff;
}
