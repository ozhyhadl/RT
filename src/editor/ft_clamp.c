/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:21:53 by yruda             #+#    #+#             */
/*   Updated: 2019/09/27 17:22:50 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

double	ft_clamp(double s, double min, double max)
{
	double t;

	t = s;
	if (s <= min)
		t = min;
	else if (s >= max)
		t = max;
	return (t);
}
