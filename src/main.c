/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:40:05 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/12 23:00:07 by ozhyhadl         ###   ########.fr       */
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
	scene->obj[0].normal_map_no = 1;

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
	scene->obj[1].normal_map_no = -1;	
}


int		main(int argc, char **argv)
{
	t_rt	rt;

	if (init_start_params(&rt))
		return (error_message(RED"couldnt init params"COLOR_OFF));
	if (init_sdl(&rt.sdl, rt.pov.w, rt.pov.h))
		return (1);
	if (read_textures(&rt))
		return (1);
	if (init_cl(&rt.cl))
		return (1);
	if (create_program_and_kernels(&rt.cl))
		return (1);
	make_little_default_scene(&rt.scene);

	// if (ft_parse_xml(argv[1], &rt.scene, &rt.pov))
		// return (1);


	if (set_up_memory(&rt, &rt.cl))
		return (1);
	there_will_be_loop(&rt);
	// ft_xml_save("sss.xml", &rt.scene, rt.pov);
	close_sdl(&rt.sdl);
	freed_up_memory(&rt.cl);
	return (0);
}
