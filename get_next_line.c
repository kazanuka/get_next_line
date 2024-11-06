/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/06 12:32:31 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 4


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
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list));
	if (NULL == temp || NULL == new)
		return ;
	last = find_last_node(*list);
	i = 0;
	k = 0;
	while (last->buf[i] && last->buf[i] != '\n')
		i++;
	while (last->buf[i])
		temp[k++] = last->buf[++i];
	temp[k] = '\0';
	new->buf = temp;
	new->next = NULL;
	ft_lstfree(list, new, temp);
}


char	*get_next_line(int fd)
{
	static t_list	*list;
	list = NULL;
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
