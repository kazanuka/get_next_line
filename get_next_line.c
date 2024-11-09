/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/09 15:41:21 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_strjoin(char *string, char *buffer)
{
	size_t	c;
	size_t	i;
	char	*res;

	if (!string)
	{
		string = malloc(1);
		string[0] = '\0';
	}
	c = 0;
	i = 0;
	res = malloc(ft_strlen(string) + ft_strlen(buffer) + 1);
	if (res == NULL)
		return (NULL);
	while (string[c])
	{
		res[c] = string[c];
		c++;
	}
	while (buffer[i])
		res[c++] = buffer[i++];
	res[ft_strlen(string) + ft_strlen(buffer)] = '\0';
	free(string);
	return (res);
}


char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}



char *readline(int fd,char *string)
{
	char	*buffer;
	int		i;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = 1;
	while (ft_strchr(string, '\n') == 0 && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(string);
			return (NULL);
		}
		buffer[i] = '\0';
		string = ft_strjoin(string, buffer);
	}
	free(buffer);
	return (string);
}



char	*get_next_line(int fd)
{
	static char		*content;
	char			*next_line;
	char 			*buffer;
	ssize_t 		bytes;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		printf("Error\n");
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while(ft_strchr(content,'\n') == 0 && bytes != 0)
		bytes = read(fd,buffer,BUFFER_SIZE); 
	free(buffer);
	readline(fd, content);
	if(content == NULL)
	{
		return (NULL);
	}
	 
	return (next_line);
}
