/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/09 17:31:39 by fkuyumcu         ###   ########.fr       */
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



int readbuf(int fd, char **content, char *buffer)
{
	ssize_t bytes;
	char *temp;

	bytes = read(fd, buffer, BUFFER_SIZE);
	
	if (bytes < 0)
	{
		content = NULL;
		free(content);
		return (-1);
	}
	if(bytes == 0)
		return (0);
	buffer[bytes] = '\0';
	temp = ft_strjoin(*content,buffer);
	free(*content);
	*content = temp;
	return (1);
}

void readline(char **content, char **next_line)
{
	int len;
	char *start;
		
	start = findnewline(*content);
	len = ((ft_strlen(*content) - ft_strlen(start)) * sizeof(char));
	*next_line = malloc(len);	
}


char	*get_next_line(int fd)
{
	static char		*content;
	char			*next_line;
	char 			*buffer;
	int 		status;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	status = 1;
	while(ft_strchr(content,'\n') == 0 && status > 0)
		status = readbuf(fd,buffer,BUFFER_SIZE); 
	free(buffer);
	if(!content || status == -1)
		return (NULL);
	readline(&content, &next_line);//contentteki stringi uygun şekilde next line'a ata.
	lineclear(&content);//contentte newline dahil olmak üzere önceki stringleri siler böylece sonraki satıra hazır olur
	return (next_line);
}
