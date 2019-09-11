/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_add_param_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:30:23 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/01 15:26:13 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		ft_add_rgb(const char *str, t_scene *scene, int i)
{
	cl_double3	dot;

	if (ft_get_3param(3, str, &dot, NULL))
		if ((dot.s[0] >= 0 && dot.s[0] <= 255) && (dot.s[1] >= 0 && \
			dot.s[1] <= 255) && (dot.s[2] >= 0 && dot.s[2] <= 255))
			scene->obj[i].color = (cl_double3)dot;
		else
			return (error_message(RED"XML: 0 <= RGB <= 255"COLOR_OFF));
	else
		return (1);
	return (0);
}

double	str_to_double(char *line)
{
	int		int_part;
	int		float_part;
	int		dot_pos;
	int		line_len;
	double	res;

	dot_pos = 0;
	line_len = ft_strlen(line);
	while (line[dot_pos] != '.' && line[dot_pos] != 0)
		dot_pos++;
	dot_pos++;
	int_part = ft_atoi(line);
	float_part = (dot_pos != line_len) ? ft_atoi(line + dot_pos) : 0;
	res = int_part + (double)float_part / (pow(10, count_num(float_part)));
	if (res > 0 && res < 1 && line[0] == '-')
		res *= -1;
	return (res);
}

int		ft_del_split(char ***split, cl_double3 *dot, cl_double *one_dot)
{
	int i;

	if (dot != NULL && *split != NULL)
		*dot = (cl_double3){{str_to_double((*split)[0]), \
		str_to_double((*split)[1]), str_to_double((*split)[2])}};
	else if (one_dot != NULL && *split != NULL)
		*one_dot = (cl_double)str_to_double((*split)[0]);
	if (*split != NULL)
	{
		i = 0;
		while ((*split)[i] != NULL)
		{
			free((*split)[i]);
			i++;
		}
		free(*split);
		*split = NULL;
	}
	return (1);
}

char	**ft_is_good_param(const char *str, int count)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(str, ' ');
	while (split[i] != NULL)
		i++;
	if (split != NULL && i != count)
	{
		ft_putstr(RED"XML: Error count argument "COLOR_OFF);
		ft_putendl(str);
		ft_del_split(&split, NULL, NULL);
		return (NULL);
	}
	return (split);
}

int		ft_get_3param(int i, const char *str, cl_double3 *dot, \
						cl_double *one_dot)
{
	char		**split;
	int			n;

	n = 0;
	if (str == NULL)
	{
		ft_putendl(RED"XML: Empty tag "COLOR_OFF);
		return (0);
	}
	while (str[n] != '\0')
	{
		if (str[n] == '\n' || str[n] == '\t')
		{
			ft_putendl(RED"XML : Only space between paramrams"COLOR_OFF);
			return (0);
		}
		n++;
	}
	if ((split = ft_is_good_param(str, i)) != NULL)
		return (ft_del_split(&split, dot, one_dot));
	return (0);
}
