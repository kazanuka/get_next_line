/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/05 17:16:00 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 4


void	copy(t_list *list, char *str)
{
	int	i;
	int	k;

	if (NULL == list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->buf[i])
		{
			if (list->buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

char    *ft_getline(t_list *list) 
{
    int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = length(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy(list, next_str);
	return (next_str);
}


int	length(t_list *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->buf[i])
		{
			if (list->buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}	
	return (len);
}


void append(t_list **list, char *buf) {
    t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->buf = buf;
	new_node->next = NULL;
}

int is_newline(t_list *list)
{
    int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->buf[i] && i < BUFFER_SIZE)
		{
			if (list->buf[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

void	create_list(t_list **list, int fd)
{
	int		bytes;	
	char	*buf;

	while (!is_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;
		bytes = read(fd, buf, BUFFER_SIZE);
		if (!bytes)
		{
			free(buf);
			return ;
		}
		buf[bytes] = '\0';
		append(list, buf);
	}
}


t_list	*find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}



void	ft_lstfree(t_list **list, t_list *new, char *buf)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (new->buf[0])
		*list = new;
	else
	{
		free(buf);
		free(new);
	}
}


void	lstmove(t_list **list)
{
	t_list	*last;
	t_list	*new;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list));
	if (NULL == buf || NULL == new)
		return ;
	last = find_last_node(*list);
	i = 0;
	k = 0;
	while (last->buf[i] && last->buf[i] != '\n')
		i++;
	while (last->buf[i])
		buf[k++] = last->buf[++i];
	buf[k] = '\0';
	new->buf = buf;
	new->next = NULL;
	ft_lstfree(list, new, buf);
}


char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = ft_getline(list);
	lstmove(&list);
	return (next_line);
}



#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("furkan.txt", O_CREAT | O_RDWR, 0777 );
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
}