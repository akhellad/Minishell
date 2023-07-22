/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:13:25 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:19:38 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*p1;
	const char	*p2;

	p1 = s1;
	p2 = s2;
	if (n == 0)
		return (0);
	while (n != 0)
	{
		if (*p1 != *p2)
			return ((unsigned char)(*p1) - (unsigned char)(*p2));
		else
		{
			p1 ++;
			p2 ++;
		}
		n --;
	}
	return (0);
}
