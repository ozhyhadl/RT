/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_double_to_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 00:35:01 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 00:36:03 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

char	*double_to_char2(double nbr, char *first)
{
	char	*second;
	char	*tmp;

	while (nbr != 0.0)
	{
		nbr = round(nbr * 10.0);
		second = ft_itoa((int)nbr);
		tmp = first;
		first = ft_strjoin(first, second);
		ft_strdel(&tmp);
		ft_strdel(&second);
		nbr -= (long long)nbr;
	}
	return (first);
}

char	*double_to_char(double nbr)
{
	char	*first;
	char	*second;
	char	*tmp;

	if (nbr < 0)
	{
		nbr = -nbr;
		second = ft_itoa((int)nbr);
		first = ft_strjoin("-", second);
		ft_strdel(&second);
	}
	else
		first = ft_itoa((int)nbr);
	if (nbr < 0)
		nbr = -nbr;
	nbr -= (long long)nbr;
	tmp = first;
	if (nbr != 0.0)
	{
		first = ft_strjoin(first, ".");
		ft_strdel(&tmp);
	}
	first = double_to_char2(nbr, first);
	return (first);
}
