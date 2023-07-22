/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 07:05:20 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 03:07:07 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 1024

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_read(int fd, char *stash)
{
	char	*buffer;
	int		nbytes;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	nbytes = 1;
	while (!ft_strchr(stash, '\n') && nbytes != 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nbytes] = 0;
		stash = ft_free(stash, buffer);
	}
	free (buffer);
	return (stash);
}

char	*ft_final_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (stash[i] == 0)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i ++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i ++;
	}
	if (stash[i] == '\n')
		i ++;
	line[i] = '\0';
	return (line);
}

char	*ft_del(char *stash)
{
	int		n;
	int		k;
	char	*new_stash;

	n = 0;
	if (!stash[0])
	{
		free(stash);
		return (0);
	}
	while (stash[n] && stash[n] != '\n')
		n ++;
	if (!stash[n])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_calloc(ft_strlen(stash) - n + 1, sizeof(char));
	n ++;
	k = 0;
	while (stash[n])
		new_stash[k ++] = stash[n ++];
	new_stash[k] = '\0';
	free (stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*f_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	f_line = ft_final_line(stash);
	stash = ft_del(stash);
	return (f_line);
}
