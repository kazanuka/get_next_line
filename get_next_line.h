/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:24:59 by fkuyumcu          #+#    #+#             */
/*   Updated: 2024/11/06 16:49:11 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char	*buf;
	void	*next;

}				t_list;

void	copy(t_list *list, char *str);
char	*ft_getline(t_list *list);
int		length(t_list *list);
void	append(t_list **list, char *buf);
int		is_newline(t_list *list);
void	create_list(t_list **list, int fd);
t_list	*find_last_node(t_list *list);
void	ft_lstfree(t_list **list, t_list *new, char *buf);
void	lstmove(t_list **list);
char	*get_next_line(int fd);

#endif