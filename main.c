/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:34 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/25 17:23:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ok_free_function(t_operator *operators, t_lexer *lexer)
{
    t_operator *temp_op;
    t_lexer *temp_lex;

    while (lexer != NULL)
    {
        temp_lex = lexer;
		free(temp_lex->str);
        lexer = lexer->next;
        free(temp_lex);
    }
    while (operators != NULL)
    {
        temp_op = operators;
		free(temp_op->name);
		free(temp_op->operator);
        operators = operators->next;
        free(temp_op);
    }
}

void	error_function(int error_type, t_operator *operators, t_lexer *lexer)
{
	if (error_type == 1)
	{
		while (operators != NULL)
		{
			t_operator *temp_op = operators;
			free(temp_op->operator);
            free(temp_op->name);
            free(temp_op);
			operators = operators->next;
		}
		printf("Error, malloc for operators failed\n");
		exit(1);
	}
	if (error_type == 2)
	{
		while (operators != NULL)
		{
			t_operator *temp_op = operators;
			free(temp_op->operator);
            free(temp_op->name);
            free(temp_op);
			operators = operators->next;
		}
		printf("Error, malloc for lexer failed\n");
		exit(1);
	}
	if (error_type == 3)
	{
		while (operators != NULL)
		{
			t_operator *temp_op = operators;
			free(temp_op->operator);
            free(temp_op->name);
            free(temp_op);
			operators = operators->next;
		}
		while (lexer != NULL)
		{
			t_lexer *temp_lex = lexer;
			free(temp_lex->str);
            free(temp_lex);
			lexer = lexer->next;
		}
		printf("Error, malloc for creting the word failed\n");
		exit(1);
	}
}

int	get_type(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (!ft_strncmp(str, "|", 1))
			return (1);
		else if (!ft_strncmp(str, "<", 1))
			return (2);
		else if (!ft_strncmp(str, ">", 1))
			return (3);
	}
	else if (ft_strlen(str) == 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (4);
		else if (!ft_strncmp(str, ">>", 2))
			return (5);
		else if (!ft_strncmp(str, "||", 2))
			return (7);
	}
	else
		return (6);
	return (6);
}

int	qoutes_checker(char *input, char check, int i)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == check)
			return (i);
		i++;
	}
	return (0);
}

int is_operator(char c1,char c2, t_operator *operators)
{
	char *op;

	if (!c2)
		c2 = 0;
	if ((c1 == 124 && c2 == 124) || (c1 == 60 && c2 == 60) || (c1 == 62 && c2 == 62))
	{
		op = malloc(3);
		if (!op)
			error_function(2, operators, NULL);
		op[0]= c1;
		op[1] = c2;
		op[2] = '\0';
	}
	else
	{
		op = malloc(2);
		if (!op)
			error_function(2, operators, NULL);
		op[0] = c1;
		op[1] = '\0';
	}
	while (operators != NULL)
	{
		if (!ft_strncmp(op, operators->operator, 2))
		{
			free(op);
			return (1);
		}
		operators = operators->next;
	}
	free(op);
	return (0);
}

int	number_of_words(char *input, t_operator *operators)
{
	int	i;
	int	temp_i;
	int	n_words;

	i = 0;
	temp_i = 0;
	n_words = 0;
	while (input[i] != '\0' && ft_isspace(input[i]))
		i++;
	while (input[i] != '\0')
	{
		if (input[i] != '\0' && !is_operator(input[i], input[i+1], operators))
			n_words++;
		while (input[i] != '\0' && !ft_isspace(input[i]) && !is_operator(input[i], input[i+1], operators))
		{
			if (input[i] == 34)
			{
				temp_i = qoutes_checker(input, 34, i);
				if (temp_i != 0)
					i = temp_i;
			}
			if (input[i] == 39)
			{
				temp_i = qoutes_checker(input, 39, i);
				if (temp_i != 0)
					i = temp_i;
			}
			i++;
		}
		while (input[i] != '\0' && ft_isspace(input[i]) && !is_operator(input[i], input[i+1], operators))
			i++;
		if (input[i] != '\0')
		{
			while (is_operator(input[i], input[i+1], operators) && input[i] != '\0')
			{
				n_words++;
				if (ft_strncmp(&input[i+1], "<", 1) || ft_strncmp(&input[i+1], ">", 1) || ft_strncmp(&input[i+1], "|", 1))
					i++;
				i++;
			}
		}
	}
	printf("N_word:%d\n", n_words);
	return (n_words);
}

char	*getting_word(char *input, t_operator *operators, t_lexer *lexer)
{
	static int	i;
	int			temp_i;
	int			k;
	int			start;
	int			end;
	char		*word;

	k = 0;
	temp_i = 0;
	while (input[i] != '\0' && ft_isspace(input[i]))
		i++;
	if (is_operator(input[i], input[i + 1], operators))
	{
		start = i;
		if (input[i+1])
		{
			if (input[i + 1] == '<' || input[i + 1] == '>' || input[i+1] == '|')
				i++;
		}
		end = ++i;
	}
	else
	{
		start = i;
		while (input[i] != '\0' && !ft_isspace(input[i]) && !is_operator(input[i], input[i+1], operators))
		{
			if (input[i] == 34)
				temp_i = qoutes_checker(input, 34, i);
			if (input[i] == 39)
				temp_i = qoutes_checker(input, 39, i);
			if (temp_i != 0)
			{
				i = temp_i + 1;
				temp_i = 0;
			}
			else
				i++;
		}
		end = i;
		if (start == end)
			return (NULL);
	}
	word = malloc((end - start) + 1);
	if (!word)
		error_function(3, operators, lexer);
	while (start < end)
		word[k++] = input[start++];
	word[k] = '\0';
	if (input[i] == '\0')
		i = 0;
	return (word);
}

void	get_tokens(char *input, t_operator *operators, t_lexer **lexer)
{
	int		n_words;
	int		i;
	t_lexer	*current;
	t_lexer	*prev_node;

	prev_node = NULL;
	i = 0;
	n_words = number_of_words(input, operators);
	while (i < n_words)
	{
		current = malloc(sizeof(t_lexer));
		if (!lexer)
			error_function(2, operators, *lexer);
		current->str = getting_word(input, operators, current);
		current->type = get_type(current->str);
		current->next = NULL;
		current->prev = prev_node;
		if (prev_node)
			prev_node->next = current;
		else
			*lexer = current;
		prev_node = current;
		i++;
	}
}

bool checking_lex(char *str)
{
	int i;
	int temp_i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i+1] == '>') || (str[i] == '>' && str[i+1] == '<'))
			return (false);
		if ((str[i] == '|' && str[i+1] == '>') || (str[i] == '|' && str[i+1] == '<'))
			return (false);
		if ((str[i] == '<' && str[i+1] == '|') || (str[i] == '>' && str[i+1] == '|'))
			return (false);
		if (str[i] == 34)
		{
			temp_i = qoutes_checker(str, 34, i);
			if (temp_i != 0)
				i = temp_i;
			if (temp_i == 0)
				return (false);
		}
		else if (str[i] == 39)
		{
			temp_i = qoutes_checker(str, 39, i);
			if (temp_i != 0)
				i = temp_i;
			if (temp_i == 0)
				return (false);
		}
		i++;
	}
	return (true);	
}

bool syntax_check(t_operator *operators, t_lexer *lexer)
{
	t_operator *temp_op;
	t_lexer		*temp_lex;

	temp_op = operators;
	temp_lex = lexer;
	if (temp_lex->type == 1)
		return (false);
	if (lexer != NULL && lexer->next == NULL)
	{
		if (lexer->type < 6)
			return (false);
	}
	while (lexer->next != NULL)
	{
		if (lexer->type < 6 && lexer->next->type < 6)
			return (false);
		lexer = lexer->next;
	}
	while (temp_op != NULL)
	{
		if (lexer->type < 6 && lexer->type == temp_op->type)
			return(false);
		temp_op = temp_op->next;
	}
	while (temp_lex != NULL)
	{
		if (temp_lex->type == 7)
			return (false);
		if (checking_lex(temp_lex->str) == false)
			return (false);
		temp_lex = temp_lex->next;
	}
	return (true);
}

void	init_operators(t_operator **head)
{
	char		*signs[] = {"|", "<", ">", "<<", ">>", "||"};
	char		*names[] = {"PIPE", "LESS", "GREATER", "LESSP", "GREATERP", "OR"};
	int			type[] = {1, 2, 3, 4, 5, 7};
	t_operator	*prev_node;
	t_operator	*current;
	int			i;

	prev_node = NULL;
	i = 0;
	while (i < 6)
	{
		current = malloc(sizeof(t_operator));
		if (!current)
			error_function(1, *head, NULL);
		current->operator= ft_strdup(signs[i]);
		current->name = ft_strdup(names[i]);
		current->type = type[i];
		current->next = NULL;
		current->prev = prev_node;
		if (prev_node)
			prev_node->next = current;
		else
			*head = current;
		prev_node = current;
		i++;
	}
}

int	minishell(char *input)
{
	t_operator	*operators;
	t_lexer		*lexer;

	operators = NULL;
	lexer = NULL;
	init_operators(&operators);
	get_tokens(input, operators, &lexer);
	if (syntax_check(operators, lexer) == false)
	{	
		ok_free_function(operators, lexer);	
		exit(1); //here syntax_check failed error function missing
	}
	while(lexer != NULL)
	{
		printf("words:%s\n", lexer->str);
		lexer = lexer->next;
	}
	ok_free_function(operators, lexer);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*input;

	(void)argc;
	(void)argv;
	argc_checker(argc, argv);
	while (1)
	{
		input = readline("minishell> ");
		if (input)
		{
			minishell(input);
			free(input);
		}
	}
	return (0);
}
