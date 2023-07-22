/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:28:09 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:20:59 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s1len;
	size_t	s2len;
	char	*p1;
	char	*p2;

	if (s1 == NULL && len == 0)
		return (NULL);
	p1 = (char *)s1;
	p2 = (char *)s2;
	if (*p2 == 0)
		return (p1);
	s2len = ft_strlen(p2);
	s1len = ft_strlen(p1);
	while (s1len != 0 && s2len <= len)
	{
		if (ft_strncmp(p1, p2, s2len) == 0)
			return (p1);
		p1 ++;
		len --;
	}
	return (0);
}
