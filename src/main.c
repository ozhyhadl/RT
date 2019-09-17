/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:40:05 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/17 15:11:12 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	make_little_default_scene(t_scene *scene)
{
	scene->count_obj = (cl_int)3;
	scene->count_light = (cl_int)4;
	
	scene->light[0].type_num = (cl_int)DIRECT;
	scene->light[0].intensity = (cl_double3){{0, 0, 0}};
	scene->light[0].v = (cl_double3){{1, 4, 7}};

	scene->light[1].type_num = (cl_int)POINT;
	scene->light[1].intensity = (cl_double3){{5, 5, 5}};
	scene->light[1].v = (cl_double3){{0, 1, 10}};

	scene->light[2].type_num = (cl_int)POINT;
	scene->light[2].intensity = (cl_double3){{5, 5, 5}};
	scene->light[2].v = (cl_double3){{10, 1, -5}};

	scene->light[3].type_num = (cl_int)POINT;
	scene->light[3].intensity = (cl_double3){{5, 5, 5}};
	scene->light[3].v = (cl_double3){{10, 10, -5}};

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
	scene->obj[0].shape.sphere.cent = (cl_double3){{2.5, 0, 10}};
	scene->obj[0].color = (cl_double3){{0, 0, 0}};
	scene->obj[0].shape.sphere.radius = (cl_double)0;
	scene->obj[0].rotation = (cl_double3){{100 * M_PI / 180.0, 100 * M_PI / 180.0, 100 * M_PI / 180.0}};
	scene->obj[0].rotation_martix = build_rotation_matrix_form_angles(scene->obj[0].rotation);
	scene->obj[0].specular = (cl_int)-1;
	scene->obj[0].reflective = (cl_double)0;
	scene->obj[0].trans = (cl_double)0;
	scene->obj[0].ior = (cl_double)1.4;
	scene->obj[0].text_no = -1;
	scene->obj[0].normal_map_no = -1;
	scene->obj[0].txt_offset = (cl_double2){{0, 0}};
	scene->obj[0].txt_scale = (cl_double2){{1, 1}};

	scene->obj[1].fig_type = (cl_int)SPHERE;
	scene->obj[1].shape.sphere.cent = (cl_double3){{-3, 1, 5}};
	scene->obj[1].shape.sphere.radius = (cl_double)2;

	// scene->obj[1].fig_type = (cl_int)PLANE; //hasnt draw from one side
	// scene->obj[1].shape.plane.dot = (cl_double3){{0, -1, 0}};
	// scene->obj[1].shape.plane.normal = (cl_double3){{0, 0, 1}};

	// scene->obj[1].fig_type = (cl_int)CYLIN;
	// scene->obj[1].shape.cylin.dot = (cl_double3){{0, -1, 0}};
	// scene->obj[1].shape.cylin.dir = (cl_double3){{0, 0, 1}};
	// scene->obj[1].shape.cylin.radius = (cl_int)1.5;

	// scene->obj[1].fig_type = (cl_int)CONE;
	// scene->obj[1].shape.cone.vertex = (cl_double3){{0, -1, 0}};
	// scene->obj[1].shape.cone.dir = (cl_double3){{0, 0, 1}};
	// scene->obj[1].shape.cone.tangent = (cl_double)0.3;
	scene->obj[1].rotation = (cl_double3){{150.0 * M_PI / 180.0, 120.0 * M_PI / 180.0, 50.0 * M_PI / 180.0}};
	scene->obj[1].rotation_martix = build_rotation_matrix_form_angles(scene->obj[1].rotation);
	scene->obj[1].color = (cl_double3){{255, 0, 0}};
	scene->obj[1].specular = (cl_int)1000;
	scene->obj[1].reflective = (cl_double)1;
	scene->obj[1].trans = (cl_double)1;
	scene->obj[1].ior = (cl_double)1.3;
	scene->obj[1].text_no = -1;
	scene->obj[1].normal_map_no = -1;
	scene->obj[1].txt_offset = (cl_double2){{0, 0}};
	scene->obj[1].txt_scale = (cl_double2){{1, 1}};

	scene->obj[2].fig_type = (cl_int)PLANE;
	scene->obj[2].shape.plane.dot = (cl_double3){{0, -1, 0}};
	scene->obj[2].shape.plane.normal = (cl_double3){{0, 1, 0}};
	scene->obj[2].rotation = (cl_double3){{M_PI / 2, 0, 0}};
	scene->obj[2].rotation_martix = build_rotation_matrix_form_angles(scene->obj[2].rotation);
	scene->obj[2].color = (cl_double3){{255, 0, 0}};
	scene->obj[2].specular = (cl_int)1000;
	scene->obj[2].reflective = (cl_double)0;
	scene->obj[2].trans = (cl_double)0;
	scene->obj[2].ior = (cl_double)1;
	scene->obj[2].text_no = 2;
	scene->obj[2].normal_map_no = -1;
	scene->obj[2].txt_offset = (cl_double2){{0, 0}};
	scene->obj[2].txt_scale = (cl_double2){{1, 1}};
	
}

int		main(int argc, char **argv)
{
	t_rt	rt;

	if (argc == 2)
	{
		if (ft_parse_xml(argv[1], &rt.scene, &rt.pov))
			return (1);
	}
	else if (argc == 1)
		make_little_default_scene(&rt.scene);
	else
		return (print_usage());
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
	if (set_up_memory(&rt, &rt.cl))
		return (1);
	there_will_be_loop(&rt);
	// ft_xml_save("sss.xml", &rt.scene, rt.pov);
	close_sdl(&rt.sdl);
	freed_up_memory(&rt.cl);
	return (0);
}
