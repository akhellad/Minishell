/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:57:36 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:21:02 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_end(char const *s1, char const *set)
{
	size_t	lengh;
	size_t	i;

	lengh = ft_strlen(s1);
	i = 0;
	while (i < lengh)
	{
		if (ft_strchr(set, s1[lengh - i - 1]) == 0)
			break ;
		i ++;
	}
	return (lengh - i);
}

int	ft_start(char const *s1, char const *set)
{
	size_t	lengh;
	size_t	i;

	lengh = ft_strlen(s1);
	i = 0;
	while (i < lengh)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i ++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*fin;
	unsigned long	start;
	unsigned long	end;

	if (s1 == 0)
		return (0);
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	end = ft_end(s1, set);
	start = ft_start(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	fin = malloc(sizeof(char) * (end - start) + 1);
	if (!fin)
		return (0);
	ft_strlcpy(fin, s1 + start, end - start + 1);
	return (fin);
}
