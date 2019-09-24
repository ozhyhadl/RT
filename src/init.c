/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:49:27 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/22 17:23:37 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	init_pov(t_pov *pov)
{
	pov->w = WIN_WIDTH;
	pov->h = WIN_HEIGHT;
	pov->d = D;
	pov->vw = 1.155 * D;
	pov->vh = pov->vw * pov->h / pov->w;

	pov->coord = (cl_double3){{0, 0, 0}};
	pov->dir = (cl_double3){{0, 0, 0}};

	pov->cx = cos(pov->dir.s[0]);
	pov->sx = sin(pov->dir.s[0]);
	pov->cy = cos(pov->dir.s[1]);
	pov->sy = sin(pov->dir.s[1]);
	return (0);
}

int			init_start_params(t_rt *rt)
{
	int		i;

	rt->envi.textures_size = 0;
	rt->envi.txt_count = 0;
	rt->envi.txt = 0;
	

	init_pov(&rt->pov);
	rt->filters.motion = 0;
	i = -1;
	while (++i < MAX_OBJ_COUNT)
	{
		rt->filters.obj_movement[i].move = 0;
		rt->filters.obj_movement[i].dir = (cl_double3){{0, 0, 0}};
	}

	rt->filters.colors = ft_memalloc(sizeof(cl_double3) * rt->pov.w * rt->pov.h);
	rt->filters.buff = ft_memalloc(sizeof(cl_double3) * rt->pov.w * rt->pov.h);
	i = -1;
	return (0);
}

int			read_textures(t_rt *rt)
{
	if (read_texture("envi/8k_earth_daymap.jpg", &rt->envi))
		return (error_message(RED"texture failure"COLOR_OFF));
	if (read_texture("envi/earth_bump_map.jpg", &rt->envi))
		return (error_message(RED"texture failure"COLOR_OFF));
	if (read_texture("envi/123.png", &rt->envi))
		return (error_message(RED"texture failure"COLOR_OFF));
	if (read_texture("envi/waffles.jpg", &rt->envi))
		return (error_message(RED"texture failure"COLOR_OFF));
	if (read_texture("envi/perforated_2.jpg", &rt->envi))
		return (error_message(RED"texture failure"COLOR_OFF));
	if (read_texture("envi/icecream.jpg", &rt->envi))
		return (error_message(RED"texture failure"COLOR_OFF));
	return (0);	
}
