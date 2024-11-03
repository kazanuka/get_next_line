/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/03 19:55:11 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 4


void copy(t_list *list, char *string)//listedeki her bir düğümün içeriğini \0 ları silerek okuyup 
{									//stringe kopyalamalıyım	
	char *temp;
	temp = 
	while ((list -> buf) != '\n')
	
}


char	*getline(t_list *list)
{
	int		len;
	char	*line;
	
	len = length(list);
	line = malloc(length + 1);//listedeki \n görene kadarki bütün stringleri line'a kopyala 
	if (line == NULL)
		return (NULL);
	copy(list, line);
}

int	length(t_list *list)
{
	char	*string;
	int		count;
	
	count = 0;
	
	if (list == NULL)
		return (NULL);
	
	while(list)
	{
		string =  list -> buf;
		while((*string)!= NULL)
		{
			if(*string == '\n')
			{
				count++;
				return (count);
			}
			count++;
		}
		list = list -> next;
	}
	return (count);
	
}


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

int is_newline(t_list *node)
{
	char *string = *node -> buf;
	while(string != '\0')
	{
		if(*string == '\n')
			return 1;
		else
			string++;
	}
	return 0;
	
}


void create(t_list **list, int fd)
{
	char	*buf;
	int		bytes;


	while(!is_newline(*list))
	{
		buf = malloc(sizeof (char) * (BUFFER_SIZE) + 1);
		if (buf == NULL)
			return ;
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == 0)
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