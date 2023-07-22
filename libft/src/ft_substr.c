/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:21:55 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:21:04 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	len2;

	if (s == 0)
		return (0);
	len2 = ft_strlen(s);
	if (len == 0 || start > len2)
		return (ft_strdup(""));
	if (len > len2)
		len = len2 - start;
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}
