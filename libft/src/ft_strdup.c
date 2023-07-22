/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:29:21 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:20:48 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*copie;
	char	*src1;

	src1 = (char *)src;
	copie = malloc(ft_strlen(src1) + 1 * sizeof(char));
	if (!copie)
		return (0);
	copie = ft_strcpy(copie, src1);
	return (copie);
}
