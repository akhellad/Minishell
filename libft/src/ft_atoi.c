/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:46:16 by akhellad          #+#    #+#             */
/*   Updated: 2023/11/16 10:33:54 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi2(const char *nptr1, long int fin, long int neg)
{
	while (*nptr1 >= '0' && *nptr1 <= '9')
	{
		fin = fin * 10 + (*nptr1 - '0');
		nptr1 ++;
		if (fin > LLONG_MAX)
		{
			if (neg > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (fin * neg);
}

int	ft_atoi(const char *nptr)
{
	long int		fin;
	long int		neg;
	char			*nptr1;

	nptr1 = (char *)nptr;
	fin = 0;
	neg = 1;
	while (*nptr1 == ' ' || *nptr1 == '\f' || *nptr1 == '\n' || \
	*nptr1 == '\r' || *nptr1 == '\t' || *nptr1 == '\v')
		nptr1 ++;
	if (*nptr1 == '+')
		nptr1 ++;
	else if (*nptr1 == '-')
	{
		neg = -1;
		nptr1 ++;
	}
	return (ft_atoi2(nptr1, fin, neg));
}
