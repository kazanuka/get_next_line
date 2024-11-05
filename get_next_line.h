/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:59 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/05 15:21:34 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 4
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_list
{
	char *buf;
	void *next;

}				t_list;


int	length(t_list *list);
int is_newline(t_list *node);
void append(t_list **list, char *buf);
void	create_list(t_list **list, int fd);
void	polish_list(t_list **list);
char	*ft_getline(t_list *list);
char	*get_next_line(int fd);
void	create(t_list **list, int fd);
void	append(t_list **list, char *buf);
void	copy(t_list *list, char *string);
int		length(t_list *list);
int		is_newline(t_list *node);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
t_list	*find_last_node(t_list *list);



#endif