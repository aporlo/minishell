#include "minishell.h"

t_cmd_node  *newnode(t_list *temp)
{
    t_cmd_node  *new;

    new = malloc(sizeof(t_cmd_node));
    if (!new || !temp)
        return (NULL);
    new->cmd_arr = ll_to_strarr(temp);
    new->next = NULL;
    return (new);
}

void    node_addback(t_cmd_node **node, t_cmd_node *new)
{
    t_cmd_node  *tmp_nd;

    if (!new)
        return ;
    if (*node == NULL)
        *node = new;
    else
    {
        tmp_nd = *node;
        while(tmp_nd->next != NULL)
            tmp_nd = tmp_nd->next;
        tmp_nd->next = new;
    }
}

t_cmd_table    *parser(t_list *cmd_ll)
{
    t_cmd_table     *cmd_table;
    t_list          *left_ptr;
    t_list          *right_ptr;
    t_list          *temp;

    cmd_table = malloc(sizeof(t_cmd_table));
    if (!cmd_table)
        return (NULL);
    cmd_table->cmds = NULL;
    cmd_table->infile = NULL;
    cmd_table->outfile = NULL;
    left_ptr = cmd_ll;
    right_ptr = cmd_ll;
    while (right_ptr)
    {
        if (isredirection(right_ptr) || !ft_strncmp(right_ptr->token, "PIPE", 5))
        {
            redirection_parse(right_ptr, cmd_table);
            temp = sub_linklist(left_ptr, right_ptr);
            node_addback(&cmd_table->cmds, newnode(temp));
            ft_lstclear(&temp, &free_token);
            left_ptr = right_ptr->next;
            if (isredirection(right_ptr))
                left_ptr = left_ptr->next;
        }
        if (right_ptr->next == NULL)
            node_addback(&cmd_table->cmds, newnode(left_ptr));
        right_ptr = right_ptr->next;
    }
    return (cmd_table);
}
