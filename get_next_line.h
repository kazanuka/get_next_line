#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE = 4
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_list
{
	char *buf;
	void *next;

}				t_list;

char	*get_next_line(int fd);



#endif