#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 4

// Uzunluğu hesaplayan fonksiyon
int length(t_list *list) {
    int count = 0;
    char *string;
    
    while (list) {
        string = list->buf;
        while (*string != '\0') {
            if (*string == '\n')
                return count + 1;
            count++;
            string++;
        }
        list = list->next;
    }
    return count;
}

// Stringi kopyalayan fonksiyon
void copy(t_list *list, char *string) {
    char *temp;
    int i = 0;

    while (list) {
        temp = list->buf;
        while (*temp != '\0' && *temp != '\n') {
            if (i == BUFFER_SIZE) {
                list = list->next;
                if (!list)
                    break;
                temp = list->buf;
                i = 0;
            }
            *string++ = *temp++;
        }
        if (*temp == '\n') {
            *string++ = '\n';
            break;
        }
        list = list->next;
    }
    *string = '\0';
}

// Satırı oluşturan fonksiyon
char *ft_getline(t_list *list) {
    int len = length(list);
    char *line = malloc(len + 1);

    if (!line)
        return NULL;
    copy(list, line);
    return line;
}

// Yeni bir düğüm ekleyen fonksiyon
void append(t_list **list, char *buf) {
    t_list *new = malloc(sizeof(t_list));
    t_list *last = *list;

    if (!new)
        return;
    new->buf = buf;
    new->next = NULL;

    if (!*list) {
        *list = new;
    } else {
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

// Satır içindeki yeni satır karakterini kontrol eden fonksiyon
int is_newline(t_list *node) {
    char *string = node->buf;
    while (*string != '\0') {
        if (*string == '\n')
            return 1;
        string++;
    }
    return 0;
}

// Listeyi dolduran fonksiyon
void create(t_list **list, int fd) {
    char *buf;
    int bytes;

    if (!*list) { // Eğer liste boşsa başlangıç düğümünü oluştur
        buf = malloc(BUFFER_SIZE + 1);
        if (!buf)
            return;
        bytes = read(fd, buf, BUFFER_SIZE);
        if (bytes <= 0) {
            free(buf);
            return;
        }
        buf[bytes] = '\0';
        append(list, buf);
    }

    while (!is_newline(*list)) {
        buf = malloc(BUFFER_SIZE + 1);
        if (!buf)
            return;
        bytes = read(fd, buf, BUFFER_SIZE);
        if (bytes <= 0) {
            free(buf);
            return;
        }
        buf[bytes] = '\0';
        append(list, buf);
    }
}

// Ana işlev
char *get_next_line(int fd) {
    static t_list *list = NULL;
    char *next_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return NULL;

    create(&list, fd);
    if (!list)
        return NULL;

    next_line = ft_getline(list);

    // Bellek temizleme işlemleri buraya eklenebilir (TODO)
    return next_line;
}

// Test ana fonksiyon
int main(void) {
    int fd = open("furkan.txt", O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
        perror("File open error");
        return 1;
    }
    char *line = get_next_line(fd);
    if (line) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}