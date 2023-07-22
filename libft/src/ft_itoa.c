/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:51:18 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/01 15:19:11 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countnbr(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa2(int n, char *str, int len, int i)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	i = len;
	while (n != 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i --;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		len = ft_countnbr(n);
	else
		len = ft_countnbr(n) - 1;
	str = malloc(sizeof(char) * len + 2);
	if (!str)
		return (0);
	str = ft_itoa2(n, str, len, i);
	str[len + 1] = 0;
	return (str);
}
