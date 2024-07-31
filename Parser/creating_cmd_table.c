/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:18:16 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/31 23:32:20 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void    args_maker(t_lexer *lexer, t_cmd *cmd, int n_cmds)
{
    int i;
    int k;
    static t_lexer *temp_lex;
    static t_cmd    *temp_cmd;

    i = 0;
    k = 0;
    if (temp_cmd == NULL)
        temp_cmd = cmd;
    if (temp_lex == NULL)
        temp_lex = lexer;
    // if (n_cmds == 1)
    // {
    //     while (lexer != NULL)
    //     {
    //         if (lexer->type != 6)
    //             lexer = lexer->next->next;
    //         if (cmd->args[i])
    //             cmd->args[i] = lexer->str;
    //         i++;
    //         lexer = lexer->next;
    //     }
    //     return;
    // }
    // else
    // {
    while (temp_lex != NULL && temp_lex->type != 1)
        {
            if (temp_lex->type != 6 && temp_lex->next->next)
                temp_lex = temp_lex->next->next;
            if (temp_lex->type != 6 && !temp_lex->next->next)
                break;
            temp_cmd->args[i] = temp_lex->str;
            i++;
            temp_lex = temp_lex->next;
        }
        if (temp_lex != NULL)
            temp_lex = temp_lex->next;
        cmd = temp_cmd;
        temp_cmd = temp_cmd->next;
        if (k == n_cmds)
            cmd = temp_cmd;
        k++;
    // }
}

int     count_cmds(t_lexer *lexer)
{
    int n_cmds;

    n_cmds = 0;
    if (lexer)
        n_cmds++;
    if (lexer->type != 6 && lexer->next && !lexer->next->next)
        n_cmds--;
    while (lexer != NULL)
    {
        if (lexer->type == 1)
            n_cmds++;
        lexer = lexer->next;
    }
    return (n_cmds);
}

int number_of_args(t_lexer *lexer) 
{
    int count = 0;
    static t_lexer *temp;

    if (temp == NULL)
        temp = lexer;
    while (temp != NULL && temp->type != 1) 
    {
        count++;
        if (temp->type != 6)
            count = count -2 ;
        temp = temp->next;
    }
    if (temp != NULL && temp->type == 1)
        temp = temp->next;
    return (count);
}

void creating_cmd_table(t_lexer *lexer, t_cmd **cmd)
{
    t_cmd *temp;
    t_cmd *prev_node = NULL;
    int n_cmds;
    int i;
    int j;
    int n_args;

    i = 0;
    j = 0;
    n_cmds = count_cmds(lexer);
    if (!n_cmds)
        return ;
    while (i < n_cmds)
    {
        temp = malloc(sizeof(t_cmd));
        if (!temp)
            exit(1); //exit function missing
        n_args = number_of_args(lexer);
        temp->args = malloc(sizeof(char *) * n_cmds);
        if (!temp->args)
            exit(1); // exit function missing
        for (j = 0; j < n_args; j++)
        {
            temp->args[j] = malloc(sizeof(char) * n_args);
            if (!temp->args[j])
                exit(1); //exit function missing
        }
        temp->args[j] = NULL;
        args_maker(lexer, temp, n_cmds);
        temp->cmd = temp->args[0];
        // temp->op_next = find_op_next(); (if needed)
        // temp->op_bef = find_op_bef(); (if needed)
        temp->next = NULL;
        temp->prev = prev_node;
        if (prev_node)
            prev_node->next = temp;
        else
            *cmd = temp;
        prev_node = temp;
        i++;
    }
}
