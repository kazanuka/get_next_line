/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/03 16:24:55 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 4

void	append(t_list **list, char *buf)
{
	t_list	*new;

	while ((*list)->next)//goto last node
		*list = (*list)->next;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	if (*list == NULL)
		*list = new;
	else
		(*list)->next = new;
	new->buf = buf;
	new->next = NULL;
}


void create(t_list **list, int fd)
{
	char	*buf;
	int		bytes;

	//Bu kısımdan sonra buffer_size içinde newline bulunmamasına göre hareket edecek
	//!newline sürece

	while(!newline(*list))
	{
	buf = malloc(sizeof (char) * (BUFFER_SIZE) + 1);
	if (buf == NULL)
		return ;
	bytes = read(fd, buf, BUFFER_SIZE);
	if(bytes == 0)
	{
		free(buf);
		return ;
	}
	buf[bytes] = '\0';

	t_list *new = malloc(sizeof(t_list));
	if(!new)
		return ;
	append(list,buf);

	}

	

}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	
	create(&list, fd);
	
	if (list == NULL)
		return (NULL);
	//TODO Yeni satırı al
	//TODO Listeyi temizle
	return (next_line);
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("furkan.txt", O_CREAT | O_RDWR, 0777 );
	printf("%s",get_next_line);
}