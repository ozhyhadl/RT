/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_but.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:02:49 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/24 00:16:41 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include <time.h>

void	ft_screenshot(t_rt *rt)
{
	SDL_Surface	*surr = SDL_CreateRGBSurface(0, rt->pov.w, rt->pov.h, 32, 0, 0, 0, 0);
	time_t		mytime;
	char		*str_stime;
	int			len;
	
	mytime = time(NULL);
	str_stime = ctime(&mytime);
	len = ft_strlen(str_stime);
	str_stime[len - 1] = '\0';
	str_stime = ft_strjoin(str_stime, ".png");
	ft_memcpy(surr->pixels, rt->sdl.win_sur->pixels, rt->sdl.win_sur->w * rt->sdl.win_sur->h * 4);
	IMG_SavePNG(surr, str_stime);
	SDL_FreeSurface(surr);
	free(str_stime);
}

void	ft_butn_sent(t_rt *rt)
{
	int i;

	i = 0;
	while (i != COUNT_BUTT)
	{
		if (rt->butt[i].type != SENT)
			rt->butt[i].available = (rt->butt[i].available == 1) ? 0 : 1;;
		i++;
	}
}

int		pres_buttn(t_rt *rt, int x, int y)
{
	int i;
	SDL_Rect off;


	i = 0;
	while (i != COUNT_BUTT)
	{
		off = rt->butt[i].offset;
		if (rt->butt[i].available)
			if ((x > off.x && x < off.w + off.x) && (y > off.y && y < off.h + off.y))
			{
					ft_butn_sent(rt);
				if (rt->butt[i].type == SAVE)
					ft_xml_save("SaveSceneRT.xml", &rt->scene, rt->pov);
				else if (rt->butt[i].type == SCREEN)
					ft_screenshot(rt);
			}
		i++;
	}
	
	return (1);
}