/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 06:54:28 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:19:41 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove2(int n, char *d, const char *s)
{
	while (n > 0)
	{
		*d = *s;
		d ++;
		s ++;
		n --;
	}
	return (d);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (n == 0 || dest == src)
		return (dest);
	if (d > s)
	{
		while (i < n)
		{
			i ++;
			d[n - i] = s[n - i];
		}
	}
	else
	{
		ft_memmove2(n, d, s);
	}
	return (dest);
}
