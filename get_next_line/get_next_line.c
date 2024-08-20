/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:32:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 02:44:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*createline(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s[0])
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n' && s[i])
		line[i++] = '\n';
	return (line);
}

char	*get_remainder(char *s)
{
	char		*temp;
	size_t		len;

	len = 0;
	while (s[len] != '\n' && s[len])
		len++;
	if (!s[len])
	{
		free(s);
		return (NULL);
	}
	temp = ft_substr(s, len + 1, (ft_strlen(s) - len));
	if (!temp)
	{
		free(s);
		return (NULL);
	}
	if (ft_strchr(s, '\n'))
		s[len + 1] = '\0';
	else
		s[len] = '\0';
	free(s);
	return (temp);
}

char	*read_into_buffer(int fd, char *s, char *buff)
{
	long long int		ret;
	char				*temp;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			free(s);
			return (NULL);
		}
		buff[ret] = '\0';
		temp = ft_strjoin2(s, buff);
		free(s);
		s = temp;
		if (ft_strchr(s, '\n'))
			break ;
	}
	free(buff);
	return (s);
}

char	*get_next_line(int fd)
{
	static char		*s;
	char			*line;
	char			*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!s)
	{
		s = ft_calloc(1, 1);
		if (!s)
			return (NULL);
	}
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(s), NULL);
	s = read_into_buffer(fd, s, buff);
	if (!s)
		return (free(s), NULL);
	line = createline(s);
	s = get_remainder(s);
	return (line);
}
