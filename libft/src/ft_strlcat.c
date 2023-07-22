/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:52:28 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:20:53 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	l_dest;
	size_t	l_src;

	if (dest == NULL && size == 0)
		return (0);
	l_dest = ft_strlen(dest);
	l_src = ft_strlen(src);
	i = l_dest;
	if (size <= l_dest || size == 0)
		return (size + l_src);
	while (src[i - l_dest] && i < size - 1)
	{
		dest[i] = src[i - l_dest];
		i ++;
	}
	dest[i] = '\0';
	return (l_dest + l_src);
}
