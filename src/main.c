/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:40:05 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 13:57:18 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		main(int argc, char **argv)
{
	t_rt	rt;

	if (init_start_params(&rt))
		return (error_message(RED"Couldnt init params"COLOR_OFF));
	if (argc == 2)
	{
		if (ft_parse_xml(argv[1], &rt.scene, &rt.pov, &rt))
			return (1);
	}
	else
		return (print_usage());
	if (init_sdl(&rt.sdl, rt.pov.w, rt.pov.h))
		return (1);
	if (init_but(&rt))
		return (1);
	if (init_cl(&rt.cl))
		return (1);
	if (create_program_and_kernels(&rt.cl))
		return (1);
	if (set_up_memory(&rt, &rt.cl))
		return (1);
	there_will_be_loop(&rt);
	close_sdl(&rt.sdl);
	freed_up_memory(&rt.cl, &rt);
	return (0);
}
