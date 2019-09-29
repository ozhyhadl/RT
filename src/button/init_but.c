/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_but.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:53:56 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 12:09:20 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	apply_surface(SDL_Surface *dest, t_rt *rt)
{
	int i;

	i = 0;
	while (i != COUNT_BUTT)
	{
		if (rt->butt[i].available)
			SDL_BlitScaled(rt->butt[i].image, NULL, dest, &rt->butt[i].offset);
		i++;
	}
}

int		load_btt(const char *path, int type, t_button *butt, t_pov pov)
{
	int i;
	int	d;

	i = type;
	if ((butt->image = IMG_Load(path)) == NULL)
		return (error_message(RED"BUTT: invalid img"COLOR_OFF));
	d = MIN(pov.w, pov.h);
	butt->type = type;
	butt->available = 1;
	butt->offset.x = 0.02 * d;
	butt->offset.y = (0.02 * d) + (0.06 * d) * (i - 1);
	butt->offset.w = 0.05 * d;
	butt->offset.h = 0.05 * d;
	return (0);
}

int		init_but(t_rt *rt)
{
	if (load_btt("./buttons/d_a.png", SENT, &rt->butt[0], rt->pov))
		return (1);
	if (load_btt("./buttons/save.png", SAVE, &rt->butt[1], rt->pov))
		return (1);
	if (load_btt("./buttons/screen.png", SCREEN, &rt->butt[2], rt->pov))
		return (1);
	return (0);
}
