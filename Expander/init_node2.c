/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:04:52 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/28 17:17:45 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

// tester> echo haha"$VAR1"$'VAR2'
// EXPAND
// EXPAND_STR: echo
// EXPAND
// EXPAND_STR: haha
// EXPAND_STR: "$VAR1"
// EXPAND_STR: $
// EXPAND_STR: 'VAR2'
// val$VAR2

void handle_quote(t_expand_node **head, t_lexer *lexer, t_main *main, int *i, int *start, bool *in_quotes, char *quote_char) 
{
    if (*in_quotes && lexer->str[*i] == *quote_char) 
    {
        *in_quotes = false;
        char *substr = strndup(lexer->str + *start, *i - *start + 1);
        add_node(head, substr, main);
        *start = *i + 1;
    } 
    else if (!*in_quotes) 
    {
        if (*i > *start) 
        {
            char *substr = strndup(lexer->str + *start, *i - *start);
            add_node(head, substr, main);
        }
        *in_quotes = true;
        *quote_char = lexer->str[*i];
        *start = *i;
    }
}

void handle_special_char(t_expand_node **head, t_lexer *lexer, t_main *main, int *i, int *start)
{
    if (*i > *start) 
    {
        char *substr = strndup(lexer->str + *start, *i - *start);
        add_node(head, substr, main);
    }
    *start = *i;
}

void handle_space(t_expand_node **head, t_lexer *lexer, t_main *main, int *i, int *start)
{
    if (*i > *start) 
    {
        char *substr = strndup(lexer->str + *start, *i - *start);
        add_node(head, substr, main);
    }
    *start = *i + 1;
}

void add_remaining_substring(t_expand_node **head, t_lexer *lexer, t_main *main, int i, int start)
{
    if (i > start) 
    {
        char *substr = strndup(lexer->str + start, i - start);
        add_node(head, substr, main);
    }
}

void split_up_by_quotes(t_expand_node **head, t_lexer *lexer, t_main *main)
{
    int i = 0;
    int start = 0;
    bool in_quotes = false;
    char quote_char = '\0';

    i = -1;
    start = 0;
    in_quotes = false;
    quote_char = '\0';
    while (lexer->str[++i]) 
    {
        if (lexer->str[i] == '"' || lexer->str[i] == '\'') 
        {
            handle_quote(head, lexer, main, &i, &start, &in_quotes, &quote_char);
        } 
        else if (lexer->str[i] == '$' && !in_quotes) 
        {
            handle_special_char(head, lexer, main, &i, &start);
        } 
        else if (lexer->str[i] == ' ' && !in_quotes) 
        {
            handle_space(head, lexer, main, &i, &start);
        }
    }
    add_remaining_substring(head, lexer, main, i, start);
}