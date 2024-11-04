/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:54 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/04 19:23:39 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 4


void copy(t_list *list, char *string) {
    char *temp;
    int i;

    while (list)
    {
        temp = list->buf;
        i = 0;
        while (*temp != '\n' && i < BUFFER_SIZE)
        {
            *string++ = *temp++;
            i++;
        }
        if (*temp == '\n')
        {
            *string++ = '\n';
            break ;
        }
        list = list->next;
    }
    *string = '\0';
}

char    *ft_getline(t_list *list) 
{
    int len; 
    char *line;

    len = length(list);
    line = malloc(len + 1);
    
    if (!line)
        return NULL;
    copy(list, line);
    return line;
}


int	length(t_list *list)
{
	char	*string;
	int		count;
	
	count = 0;
	
	if (list == NULL)
		return (0);
	
	while(list)
	{
		string =  list -> buf;
		while((*string)!= '\n')
		{
			count++;
			string++;
		}
		list = list -> next;
	}
	return (count);
}


void append(t_list **list, char *buf) {
    t_list *new = malloc(sizeof(t_list));
    t_list *last = *list;

    if (!new)
        return;
    new->buf = buf;
    new->next = NULL;

    if (!*list) 
        *list = new;
    else 
    {
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

int is_newline(t_list *node)
{
    int i = 0;
	char *string = node -> buf;
	while(i < BUFFER_SIZE)
	{
		if(*string == '\n')
		    return (1);
	    else
        {
			string++;
            i++;
        }
	}
	return (0);
}

void createnode(char *buf, int bytes, int fd,t_list **list)
{
    buf = malloc(BUFFER_SIZE);
    if (!buf)
        return;
    bytes = read(fd, buf, BUFFER_SIZE);
    if (bytes <= 0)
    {
        free(buf);
        return ;
    }
    buf[bytes] = '\0';
    append(list, buf);
}

void createlist(t_list **list, int fd) 
{
    char    *buf;
    int     bytes;

    createnode(buf,bytes,fd,list);
         
    while (!is_newline(*list))
    {   
        buf = malloc(BUFFER_SIZE);
        if (!buf)
            return;
        bytes = read(fd, buf, BUFFER_SIZE);
        if (bytes <= 0)
		{
            free(buf);
            return;
        }
        append(list, buf);
    }
}

void lstclear(t_list *list)
{
    t_list *current;
    t_list *prev;
    current = list;
    prev = NULL;
    
    while(current->next)
    {
        if (prev)
        {
            free(prev->buf);
            free(prev);
        }
        prev = current;
        current = current -> next;
    }
    if (prev)
    {
        free(prev->buf);
        free(prev);
    }
    
    list = current;
    current -> next = NULL;
    
    
    
    
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	
	createlist(&list, fd);
	
	if (list == NULL)
		return (NULL);
        
	next_line = ft_getline(list);
	
	lstclear(list);
	
	return (next_line);
}



#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("furkan.txt", O_CREAT | O_RDWR, 0777 );
	printf("%s",get_next_line(fd));
}