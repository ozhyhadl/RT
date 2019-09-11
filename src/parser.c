/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:54:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/19 16:54:35 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			read_file(char *file_name, char **file_text)
{
	int		fd;
	char	buf[BUFFER_SIZE];
	int		ret;
	char	*tmp;

	fd = open(file_name, O_RDONLY);
	ret = 0;
	*file_text = 0;
	tmp = 0;
	while ((ret = read(fd, buf, BUFFER_SIZE -1)) > 0)
	{
		buf[ret] = 0;
		if (*file_text != 0)
		{
			tmp = ft_strjoin(*file_text, buf);
			free(*file_text);
		}
		else
			tmp = ft_strdup(buf);
		*file_text = tmp;
	}
	return (ret < 0 ? 1 : 0);
}

SDL_Surface	*load_tex(char *path, Uint32 format)
{
	SDL_Surface		*temp;
	SDL_Surface		*texture;

	temp = IMG_Load(path);
	if (temp == NULL)
	{
		SDL_FreeSurface(temp);
		error_message(RED"Texture load error\n"COLOR_OFF);
		exit(1);
	}
	texture = SDL_ConvertSurfaceFormat(temp, format, 0);
	if (texture == NULL)
	{
		SDL_FreeSurface(temp);
		error_message(RED"Texture load error\n"COLOR_OFF);
		exit(1);
	}
	SDL_FreeSurface(temp);
	return (texture);
}

cl_uint	*read_texture(char	*file_name, t_txt_params *params)
{
	SDL_Surface	*surr;
	cl_uint		*res;
	Uint8		*pixels;
	Uint8		*test;
	int			i;

	surr = load_tex(file_name, SDL_PIXELFORMAT_ARGB32);
	res = 0;
	params->w = surr->w;
	params->h = surr->h;
	res = (cl_uint*)ft_memalloc(params->w * params->h * sizeof(cl_uint));
	test = (Uint8*)res;
	if (res == 0)
		return (0);
	i = -1;
	pixels = (Uint8*)surr->pixels;

	while (++i < surr->w * surr->h)
		res[i] = (pixels[i * 4] << 24) + (pixels[i * 4 + 1] << 16) + (pixels[i * 4 + 2] << 8) + pixels[i * 4 + 3];
	SDL_FreeSurface(surr);
	return (res);
}
