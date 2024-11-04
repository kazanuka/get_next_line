#include "get_next_line.h"

#include <stdlib.h>

void son_haric_hepsini_sil(t_list **head)
{
    if (head == NULL || *head == NULL)
        return;

    t_list *current = *head;
    t_list *prev = NULL;

    while (current->next)
    {
        if (prev)
        {
            free(prev->buf);
            free(prev);
        }
        prev = current;
        current = (t_list *)current->next;
    }

    // Son elemandan bir önceki elemanı serbest bırak
    if (prev)
    {
        free(prev->buf);
        free(prev);
    }

    // Son elemanı yeni head yap
    *head = current;
    current->next = NULL;
}