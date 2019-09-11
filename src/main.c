/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:40:05 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/11 21:49:48 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	make_little_default_scene(t_scene *scene)
{
	scene->count_obj = (cl_int)2;
	scene->count_light = (cl_int)1;
	
	scene->light[0].type_num = (cl_int)DIRECT;
	scene->light[0].intensity = (cl_double3){{0.8, 0.8, 0.8}};
	scene->light[0].v = (cl_double3){{1, 4, 7}};

	scene->light[1].type_num = (cl_int)POINT;
	scene->light[1].intensity = (cl_double3){{0.8, 0.8, 0.8}};
	scene->light[1].v = (cl_double3){{0, -5, 4}};

	scene->light[2].type_num = (cl_int)POINT;
	scene->light[2].intensity = (cl_double3){{0.8, 0.8, 0.8}};
	scene->light[2].v = (cl_double3){{2, 1, 0}};

	// scene->obj[0].fig_type = (cl_int)SPHERE;
	// scene->obj[0].shape.sphere.cent = (cl_double3){{0, 0, 4}};
	// scene->obj[0].color = (cl_double3){{255, 255, 255}};
	// scene->obj[0].shape.sphere.radius = (cl_double)1;
	// scene->obj[0].specular = (cl_int)-1;

	// scene->obj[0].reflective = (cl_double)0;
	// scene->obj[0].trans = (cl_double)0;
	// scene->obj[0].rotation = (cl_double3){{50 * M_PI / 180.0, 50 * M_PI / 180.0, 0 * M_PI / 180.0}};
	// scene->obj[0].text_no = 0;

	scene->obj[0].fig_type = (cl_int)SPHERE;
	scene->obj[0].shape.sphere.cent = (cl_double3){{0, 0, 10}};
	scene->obj[0].color = (cl_double3){{255, 255, 255}};
	scene->obj[0].shape.sphere.radius = (cl_double)0.5;
	scene->obj[0].rotation = (cl_double3){{150.0 * M_PI / 180.0, 120.0 * M_PI / 180.0, 50.0 * M_PI / 180.0}};
	scene->obj[0].specular = (cl_int)-1;
	scene->obj[0].reflective = (cl_double)0;
	scene->obj[0].trans = (cl_double)0;
	scene->obj[0].ior = (cl_double)1.4;
	scene->obj[0].text_no = 0;

	scene->obj[1].fig_type = (cl_int)SPHERE;
	scene->obj[1].shape.sphere.cent = (cl_double3){{0, 0, 5}};
	scene->obj[1].rotation = (cl_double3){{150.0 * M_PI / 180.0, 120.0 * M_PI / 180.0, 50.0 * M_PI / 180.0}};
	scene->obj[1].color = (cl_double3){{255, 0, 0}};
	scene->obj[1].shape.sphere.radius = (cl_double)1;
	scene->obj[1].specular = (cl_int)-1;
	scene->obj[1].reflective = (cl_double)0;
	scene->obj[1].trans = (cl_double)0.1;
	scene->obj[1].ior = (cl_double)1;
	scene->obj[1].text_no = 0;
}

void	init_pov(t_pov *pov)
{
	pov->d = D;
	pov->vw = VW;
	pov->vh = VH;

	pov->cx = cos(0);
	pov->sx = sin(0);
	pov->cy = cos(0);
	pov->sy = sin(0);

	pov->coord = (cl_double3){{0, 0, 0}};
}

int		main(int argc, char **argv)
{
	t_rt	rt;

	if (init_sdl(&rt.sdl))
		return (1);

	rt.envi.txt_count = 1;
	rt.envi.txt = read_texture("envi/8k_earth_daymap.jpg", &rt.envi.txt_par);
	rt.envi.bump = read_texture("envi/earth_bump_map.jpg", &rt.envi.bump_par);
	printf("%i %i\n", rt.envi.bump_par.w, rt.envi.bump_par.h);
	if (rt.envi.txt == 0)
		return (error_message(RED"texture failure"COLOR_OFF));
	if (rt.envi.bump == 0)
		return (error_message(RED"texture failure"COLOR_OFF));
	
	if (init_cl(&rt.cl))
		return (1);
	if (create_program_and_kernels(&rt.cl))
		return (1);
	init_pov(&rt.pov);
	make_little_default_scene(&rt.scene);

	// if (ft_parse_xml(argv[1], &rt.scene, &rt.pov))
		// return (1);


	if (set_up_memory(&rt, &rt.cl))
		return (1);
	there_will_be_loop(&rt);
	// ft_xml_save("sss.xml", &rt.scene, &rt.pov);
	close_sdl(&rt.sdl);
	freed_up_memory(&rt.cl);
	return (0);
}
