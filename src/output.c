/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:18:16 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/19 15:18:16 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		error_message(char *mess)
{
	ft_putendl(mess);
	return (1);
}

int		print_usage(void)
{
	ft_putendl(GREEN"Hey boy, to run this program you should \
use :\n"CYAN"./RT\tor\t./RT scene/<scene>"COLOR_OFF);
	return (1);
}
