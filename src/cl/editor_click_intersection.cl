#include "kernel.hh"

__kernel void	click_kernel(__global t_scene *scene,
							int	x,
							int	y,
							t_pov pov,
							__global int *id)
{
	double3	direction;

	direction = normalize(canvas_to_viewport(x - pov.w /2 , y - pov.h / 2, pov.w, pov.h, pov));
	direction = new_basis(direction, pov.pov_rm);

	t_obj_and_dist	obj_and_dist = check_closest_inter(pov.coord, direction, scene, 1, BIG_VALUE);
	*id = obj_and_dist.obj;
}

double3	ft_noise1 (double2 coords)
{
	double3 color;
	double z;

	z = floor(sin(coords[0] * 2 * M_PI) + sin(coords[1] * 2 * M_PI ));
	color = (double3){((int)z >> 16) & 0xFF, ((int)z >> 8) & 0xFF, ((int)z & 0xFF)};
	return (color);
}

double cos_interpole(double a, double b, double x)
{
	double	ft = x * 3.1415927;
	double	f = (1 - cos(ft)) * 0.5;
	return (a * (1 - f) + b * f);
}

double noise(int x, int y)
{
	int n = x + y * 57;
	return (random[n % 100]);
}

double	intrapolate_noise(double2 coords)
{
	int int_x = (int)coords[0];
	double f_x = coords[0] - int_x;
	int int_y = (int)coords[1];
	double f_y = coords[1] - int_y;
	double v1 = noise(int_x, int_y);
	double v2 = noise(int_x + 1, int_y);
	double v3 = noise(int_x, int_y + 1);
	double v4 = noise(int_x + 1, int_y + 1);
	double i1 = cos_interpole(v1 , v2 , f_x);
	double i2 = cos_interpole(v3 , v4 , f_x);
	return (cos_interpole(i1 , i2 , f_y));
}

double3 ft_noise(double2 coords)
{
	double	total = 0;
	double	p = 20;
	int		i;
	int		num_of_octaves = 5;
	double frequency;
	double amplitute;
	
	i = -1;
	while (++i < num_of_octaves)
	{
		frequency = 2 * i;
		amplitute = p * i;
		total = total + intrapolate_noise(coords * frequency) * amplitute;
	}
	return (total);
}

double3 ft_noise2(double2 coords)
{
	double	total = 0;
	double	p = 50;
	int		i;
	int		num_of_octaves = 6;
	double frequency;
	double amplitute;
	
	i = -1;
	while (++i < num_of_octaves)
	{
		frequency = 2 * i;
		amplitute = p * i;
		total = total + intrapolate_noise(coords * frequency) * amplitute;
	}
	return (total);
}			

double noise2(int x, int y)
{
	int n = x * 10 + y * 47;
	return (random[n % 100]);
}

double	intrapolate_noise2(double2 coords)
{
	int int_x = (int)coords[0];
	double f_x = coords[0] - int_x;
	int int_y = (int)coords[1];
	double f_y = coords[1] - int_y;
	double v1 = noise2(int_x, int_y);
	double v2 = noise2(int_x + 1, int_y);
	double v3 = noise2(int_x, int_y + 1);
	double v4 = noise2(int_x + 1, int_y + 1);
	double i1 = cos_interpole(v1, v2, f_x);
	double i2 = cos_interpole(v3, v4, f_x);
	return (cos_interpole(i1, i2, f_y));
}

double3 ft_noise3(double2 coords)
{
	double	total = 0;
	double	p = 70;
	int		i;
	int		num_of_octaves = 5;
	double frequency;
	double amplitute;
	
	i = -1;
	while (++i < num_of_octaves)
	{
		frequency = i;
		amplitute = p * i;
		total = total + intrapolate_noise2(coords * frequency) * amplitute;
	}
	return (total);
}
