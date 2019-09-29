#include "kernel.hh"

double2	intersect_triangle(double3 eye, double3 dir, t_triangle_data triangle)
{
	double3 v0v1 = triangle.v1 - triangle.v0;
	double3 v0v2 = triangle.v2 - triangle.v0;
	double3	pvec = cross(dir, v0v2);
	double	det = dot(v0v1, pvec);
	if (fabs(det) < EPSILON)
		return (-BIG_VALUE);
	det = 1 / det;
	double3	tvec = eye - triangle.v0;
	double	u = dot(tvec, pvec) * det;
	if (u < 0)
		return (-BIG_VALUE);
	double3 qvec = cross(tvec, v0v1); 
	double	v = dot(dir, qvec) * det;
	if (v < 0 || u + v > 1)
		return (-BIG_VALUE);
	double	t = dot(v0v2, qvec) * det;
	return (t);
}

double2	intersect_rectangle(double3 eye, double3 dir, t_rectangle_data rectangle)
{
	double2	res;
	t_triangle_data data;

	data = (t_triangle_data){rectangle.v0, rectangle.v1, rectangle.v2};
	res = intersect_triangle(eye, dir, data);
	if (res[0] > 0 && res[0] < BIG_VALUE - 1)
		return (res[0]);
	data = (t_triangle_data){rectangle.v0, rectangle.v2, rectangle.v3};
	res = intersect_triangle(eye, dir, data);
	return (res[0]);
}

double2	intersect_disk(double3 eye, double3 dir, t_disk_data disk)
{
	double3	oc = eye - disk.cent;
	double	a;
	double	b;

	a = dot(oc, disk.normal);
	b = dot(dir, disk.normal);
	if (b == 0 || a * b > 0)
		return (-BIG_VALUE);
	double t = -a / b;
	double3	p = dir * t + oc;
	if (dot(p, p) > disk.radius * disk.radius)
		return (-BIG_VALUE);
	return ((double2)(-a / b, -BIG_VALUE));
}

double2	intersect_sphere(double3 eye, double3 dir, t_sphere_data sphere)
{
	double3	oc = eye - sphere.cent;
	double	a;
	double	b;
	double	c;
	double	d;
	double2	roots;
	
	a = dot(dir, dir);
	b = dot(oc, dir);
	c = dot(oc, oc) - sphere.radius * sphere.radius;
	
	d = b * b - a * c;
	if (d < 0)
		return (-BIG_VALUE);
	d = sqrt(d);
	roots = (double2)((-b + d) / a, (-b - d) / a);
	return (roots);
}

double2	intersect_plane(double3 eye, double3 dir, t_plane_data plane)
{
	double3	oc = eye - plane.dot;
	double	a;
	double	b;

	a = dot(oc, plane.normal);
	b = dot(dir, plane.normal);
	if (b == 0 || a * b > 0)
		return (BIG_VALUE);
	return((double2)(-a / b, -BIG_VALUE));
}

double2	intersect_cylin(double3 eye, double3 dir, t_cylin_data cylin)
{
	double3	oc = eye - cylin.dot;
	double	a;
	double	b;
	double	c;
	double	d;
	double2	roots;
	double	scalar = dot(dir, cylin.dir);
	double	scalar2 = dot(oc, cylin.dir);
	double	m;
	
	a = dot(dir, dir) - scalar * scalar;
	b = dot(dir, oc) - (scalar * scalar2);
	c = dot(oc, oc) - scalar2 * scalar2 - cylin.radius * cylin.radius;
	d = b * b - a * c;
	if (d < 0)
		return (-BIG_VALUE);
	d = sqrt(d);
	roots = ((double2)((-b + d),(-b - d))) / a;
	m = roots[0] * scalar + scalar2;
	if (m < cylin.mmin || m > cylin.mmax)
		roots[0] = -BIG_VALUE;
	m = roots[1] * scalar + scalar2;
	if (m < cylin.mmin || m > cylin.mmax)
		roots[1] = -BIG_VALUE;
	return(roots);
}

double2	intersect_cone(double3 eye, double3 dir, t_cone_data cone)
{
	double3	oc = eye - cone.vertex;
	double	a;
	double	b;
	double	c;
	double	d;
	double2	roots;
	double	scalar = dot(dir, cone.dir);
	double	scalar2 = dot(oc,cone.dir);
	double	tangent2 = cone.tangent * cone.tangent;
	double	m;


	a = dot(dir, dir) - (1.0 + tangent2) * (scalar * scalar);
	b = (dot(dir, oc) - (1.0 + tangent2) * (scalar * scalar2));
	c = dot(oc, oc) - (1.0 + tangent2) * scalar2 * scalar2 ;
	d = b * b - a * c;
	if (d < 0)
		return (-BIG_VALUE);
	d = sqrt(d);
	roots = ((double2)((-b + d),(-b - d)) / a);
	m = roots[0] * scalar + scalar2;
	if (m < cone.mmin || m > cone.mmax)
		roots[0] = -BIG_VALUE;
	m = roots[1] * scalar + scalar2;
	if (m < cone.mmin || m > cone.mmax)
		roots[1] = -BIG_VALUE;
	return(roots);
}

double2	intersect_ellipse(double3 eye, double3 dir, t_ellipse_data ellipse)
{
	double	k = ellipse.dist_btwn_cent;
	double	r2 = ellipse.radius_sum * ellipse.radius_sum;

	double3	oc = eye - ellipse.cent;
	double	a1 = 2 * k * dot(dir, ellipse.dir);
	double	a2 = r2 + 2 * k * dot(oc, ellipse.dir) - k;
	double	a = 4 * r2 * dot(dir, dir) - a1 * a1;
	double	b = 4 * r2 * dot(dir, oc) - a1 * a2;
	double	c = 4 * r2 * dot(oc, oc) - a2 * a2;

	double d = b * b - a * c;
	if (d < 0)
		return (-BIG_VALUE);
	d = sqrt(d);
	return ((double2)((-b + d),(-b - d))) / a;
}

double3	calculate_normal(t_fig fig, double3 intersect_point, t_raytrace_tree curr_node)
{
	double3		tmp;//dot - intersect.point
	double3		tmp_2;
	double		tmp_3;
	double3		normal;
	double		b;
	double		a;

	switch (fig.fig_type)
	{
		case SPHERE:
			normal = intersect_point - fig.shape.sphere.cent;
			normal = normalize(normal);
			break ;
		case PLANE:
			normal = fig.shape.plane.normal;
			break ;
		case CYLIN:
			tmp = fig.shape.cylin.dot - intersect_point;
			normal = normalize((dot(tmp, fig.shape.cylin.dir) * fig.shape.cylin.dir) - tmp);
			break ;
		case CONE:
			tmp = fig.shape.cone.vertex - intersect_point;
			normal = normalize(((dot(tmp, tmp) / dot(tmp, fig.shape.cone.dir)) * fig.shape.cone.dir) - tmp);
			break ;
		case TRIANGLE:
			tmp = fig.shape.triangle.v0 - fig.shape.triangle.v1;
			tmp_2 = fig.shape.triangle.v0 - fig.shape.triangle.v2;
			normal = normalize(cross(tmp, tmp_2));
			break ;
		case DISK:
			normal = fig.shape.disk.normal;
			break ;
		case RECTANGLE:
			tmp = fig.shape.rectangle.v0 - fig.shape.rectangle.v1;
			tmp_2 = fig.shape.rectangle.v0 - fig.shape.rectangle.v2;
			normal = normalize(cross(tmp, tmp_2));
			break ;
		case ELLIPSE:
			tmp = fig.shape.ellipse.cent + fig.shape.ellipse.dir * fig.shape.ellipse.dist_btwn_cent / 2;
			tmp_2 = intersect_point - tmp;
			tmp_3 = fig.shape.ellipse.dist_btwn_cent * fig.shape.ellipse.dist_btwn_cent / 4; //c ^ 2
			b = fig.shape.ellipse.radius_sum * fig.shape.ellipse.radius_sum / 4 - tmp_3;
			a = tmp_3 + b;
			normal = normalize(tmp_2 - fig.shape.ellipse.dir * (1 - b / a) * dot(tmp_2, fig.shape.ellipse.dir));
			break ;
	}
	if (fig.fig_type == PLANE || fig.fig_type == DISK || fig.fig_type == RECTANGLE || fig.fig_type == TRIANGLE)
		if (dot(curr_node.dir , normal) >= 0)
			normal = -normal;
	return (normal);
}

double3	get_obj_dot(t_fig fig)
{
	double3	res;

	switch (fig.fig_type)
	{
			case SPHERE:	res = fig.shape.sphere.cent;	break;
			case PLANE:		res = fig.shape.plane.dot;		break;
			case CYLIN:		res = fig.shape.cylin.dot;		break;
			case CONE:		res = fig.shape.cone.vertex;	break;
			case TRIANGLE:	res = fig.shape.triangle.v0;	break;
			case DISK:		res = fig.shape.disk.cent;		break;
			case RECTANGLE:	res = fig.shape.rectangle.v0;	break;
	}
	return (res);
}

double2	cut_result_with_personal_planes(double2 prev, t_fig fig, double3 eye, double3 dir)
{
	double			h_plane;
	double			h_point;
	double3			intersect_point;
	t_plane_data	cut;
	double3			obj_dot;

	if (fig.cutting)
	{
		cut = fig.cutting_plane;
		obj_dot = get_obj_dot(fig);
		h_plane = -(dot(cut.normal, (cut.dot + obj_dot)));
		if (prev[0] > -BIG_VALUE)
		{
			intersect_point = eye + dir * prev[0];
			h_point = -(dot(cut.normal, intersect_point));
			if (h_plane > h_point)
				prev[0] = -BIG_VALUE;
		}
		if (prev[1] > -BIG_VALUE)
		{
			intersect_point = eye + dir * prev[1];
			h_point = -(dot(cut.normal, intersect_point));
			if (h_plane > h_point)
				prev[1] = -BIG_VALUE;
		}
	}
	return (prev);
}

double2		cut_with_sphere(double2 prev, double3 *point, t_sphere_data sphere)
{
	double3		shifted;

	if (prev[0] > -BIG_VALUE + 1)
	{
		shifted = point[0] - sphere.cent;
		if (dot(shifted, shifted) <= sphere.radius * sphere.radius)
			prev[0] = -BIG_VALUE;
	}
	if (prev[1] > -BIG_VALUE + 1)
	{
		shifted = point[1] - sphere.cent;
		if (dot(shifted, shifted) <= sphere.radius * sphere.radius)
			prev[1] = -BIG_VALUE;
	}
	return (prev);
}

double2		cut_with_plane(double2 prev, double3 *point, t_plane_data plane)
{
	double		h_plane;
	double		h_point;

	h_plane = -(dot(plane.normal, plane.dot));
	if (prev[0] > -BIG_VALUE)
	{
		h_point = -(dot(plane.normal, point[0]));
		if (h_plane > h_point)
			prev[0] = -BIG_VALUE;
	}
	if (prev[1] > -BIG_VALUE)
	{
		h_point = -(dot(plane.normal, point[1]));
		if (h_plane > h_point)
			prev[1] = -BIG_VALUE;
	}
	return (prev);
}

double2		cut_with_cylin(double2 prev, double3 *point, t_negative_fig cylin)
{
	double3		shifted;

	if (prev[0] > -BIG_VALUE + 1)
	{
		shifted = point[0] - cylin.shape.cylin.dot;
		shifted = new_basis(shifted, cylin.rotation_matrix);
		if (shifted[2] < cylin.shape.cylin.mmax && shifted[2] > cylin.shape.cylin.mmin)
			if (shifted[0] * shifted[0] + shifted[1] * shifted[1] <= cylin.shape.cylin.radius * cylin.shape.cylin.radius)
				prev[0] = -BIG_VALUE;
	}
	if (prev[1] > -BIG_VALUE + 1)
	{
		shifted = point[1] - cylin.shape.cylin.dot;
		shifted = new_basis(shifted, cylin.rotation_matrix);
		if (shifted[2] < cylin.shape.cylin.mmax && shifted[2] > cylin.shape.cylin.mmin)
			if (shifted[0] * shifted[0] + shifted[1] * shifted[1] <= cylin.shape.cylin.radius * cylin.shape.cylin.radius)
				prev[1] = -BIG_VALUE;
	}
	return (prev);
}

double2		cut_result_with_negative_obj(double2 prev, __global t_scene *scene, double3 eye, double3 dir)
{
	int		i = -1;
	double3	intersect_point[2];
	
	if (prev[0] > -BIG_VALUE + 1)
		intersect_point[0] = eye + dir * prev[0];
	if (prev[1] > -BIG_VALUE + 1)
		intersect_point[1] = eye + dir * prev[1];

	while (++i < scene->count_neg_obj)
	{
		switch (scene->neg_obj[i].fig_type)
		{
			case SPHERE:
				prev = cut_with_sphere(prev, intersect_point, scene->neg_obj[i].shape.sphere);
			break;
			case PLANE:
				prev = cut_with_plane(prev, intersect_point, scene->neg_obj[i].shape.plane);
			break;
			case CYLIN:
				prev = cut_with_cylin(prev, intersect_point, scene->neg_obj[i]);
			break;
			default:
			break;
		}
	}
	return (prev);
}

void				cut_4_roots(double3 eye, double3 dir, double4 res, \
								__global t_scene *scene, int *closest_obj, \
								double *closest_dist, double mini, \
								double maxi, t_fig fig, int fig_no)
{
	int		i;
	double2	res1 = (double2)(res[0], res[1]);
	double2	res2 = (double2)(res[2], res[3]);

	res1 = cut_result_with_personal_planes(res1, fig, eye, dir);
	if (scene->count_neg_obj > 0)
		res1 = cut_result_with_negative_obj(res1, scene, eye, dir);

	res2 = cut_result_with_personal_planes(res2, fig, eye, dir);
	if (scene->count_neg_obj > 0)
		res2 = cut_result_with_negative_obj(res2, scene, eye, dir);

	res = (double4)(res1, res2);

	i = -1;
	while (++i < 4)
	{
		if (res[i] > mini && res[i] < maxi && res[i] < *closest_dist)
		{
			*closest_dist = res[i];
			*closest_obj = fig_no;
		}
	}
}

t_obj_and_dist		check_closest_inter(double3 eye, double3 dir, \
										__global t_scene *scene, \
										double mini, double maxi)
{
	double2	res;
	double4	torus_res;
	double	closest_dist = BIG_VALUE;
	int		closest_obj = -1;
	int		i;
	t_fig 	fig;

	i = -1;
	while (++i < scene->count_obj)
	{
		fig = scene->obj[i];
		switch (fig.fig_type)
		{
			case SPHERE:	res = intersect_sphere(eye, dir, fig.shape.sphere);			break;
			case PLANE:		res = intersect_plane(eye, dir, fig.shape.plane);			break;
			case CYLIN:		res = intersect_cylin(eye, dir, fig.shape.cylin);			break;
			case CONE:		res = intersect_cone(eye, dir, fig.shape.cone);				break;
			case TRIANGLE:	res = intersect_triangle(eye, dir, fig.shape.triangle);		break;
			case DISK:		res = intersect_disk(eye, dir, fig.shape.disk);				break;
			case RECTANGLE:	res = intersect_rectangle(eye, dir, fig.shape.rectangle);	break;
			case ELLIPSE:	res = intersect_ellipse(eye, dir, fig.shape.ellipse);		break;
			//case TORUS:		torus_res =  intersect_torus(eye, dir, fig, ...))		break;
		}

		if (fig.fig_type == TORUS)
		{
			//cut_4_roots(eye, dir, torus_res, scene, \
					&closest_obj, &closest_dist, mini, maxi, fig, i);
		}
		else
		{
			res = cut_result_with_personal_planes(res, fig, eye, dir);
			if (scene->count_neg_obj > 0)
				res = cut_result_with_negative_obj(res, scene, eye, dir);
			if (res[0] > mini && res[0] < maxi && res[0] < closest_dist)
			{
				closest_dist = res[0];
				closest_obj = i;
			}
			if (res[1] > mini && res[1] < maxi && res[1] < closest_dist)
			{
				closest_dist = res[1];
				closest_obj = i;
			}
		}

	}
	return ((t_obj_and_dist){closest_obj, closest_dist});
}
