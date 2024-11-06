#include "get_next_line.h"
#include <stdio.h>
int main()
{
    int fd = open("furkan.txt",O_RDWR, 0777);
    printf("%s",get_next_line(fd));



}