/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 22:53:00 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

bool	builtin_check(t_main *main)
{
	int	argc;

	argc = count_arg(main->cmd->args);
	if (ft_strcmp(main->cmd->cmd, "cd") == 0)
		return (ft_cd(main, argc), true);
	else if (ft_strcmp(main->cmd->cmd, "unset") == 0)
	{
		if (!unset_error(main->cmd->args, main))
			ft_unset(main, main->cmd->args);
		return (true);
	}
	else if (ft_strcmp(main->cmd->cmd, "pwd") == 0)
		return (ft_pwd(main), true);
	else if (ft_strcmp(main->cmd->cmd, "exit") == 0 && main->cmd->next == NULL)
		return (ft_exit(main->cmd, main), true);
	return (false);
}

void	echo_helper(t_cmd *own_cmd, t_main *main)
{
	char	*trimmed_str;

	trimmed_str = NULL;
	if (own_cmd->pid == 0)
	{
		if (own_cmd->args[1] && ft_strncmp(own_cmd->args[1], "$?", 2) == 0)
		{
			trimmed_str = ft_strtrim(own_cmd->args[1], "$?");
			if (!trimmed_str)
				error_function(21, main);
			ft_putnbr_fd(main->exit_code, 1);
			ft_putstrs_fd(trimmed_str, "\n", NULL, 1);
			free(trimmed_str);
		}
		else
			ft_echo(own_cmd);
		main->exit_code = 0;
	}
}

void	env_helper(t_cmd *own_cmd, t_main *main)
{
	if (own_cmd->pid == 0)
	{
		ft_env(main);
		main->exit_code = 0;
	}
}

int	echo_ex_env_check(t_main *main, t_cmd *own_cmd)
{
	if (ft_strcmp(own_cmd->cmd, "exit") == 0)
	{
		if (own_cmd->pid == 0)
			ft_exit(own_cmd, main);
		return (1);
	}
	else if (ft_strcmp(own_cmd->cmd, "echo") == 0)
		return (echo_helper(own_cmd, main), 1);
	else if (ft_strcmp(own_cmd->cmd, "env") == 0)
		return (env_helper(own_cmd, main), 1);
	else if (ft_strcmp(own_cmd->cmd, "export") == 0)
	{
		if (own_cmd->pid == 0 && !export_error(own_cmd->args, main))
		{
			ft_export(main, own_cmd->args);
			main->exit_code = 0;
		}
		return (1);
	}
	return (0);
}

void	parser(t_main *main)
{
	t_cmd	*own_cmd;
	__pid_t	pid;

	own_cmd = NULL;
	parser_helper(main);
	if (builtin_check(main) == true)
		return ;
	if (main->parser->n_pipes)
		own_cmd = init_pipes(main);
	else if (main->parser->n_pipes == 0)
	{
		pid = fork1(main);
		main->cmd->pid = pid;
		own_cmd = main->cmd;
		calling_redirects(main, own_cmd);
	}
	if (!echo_ex_env_check(main, own_cmd) && own_cmd->pid == 0)
		executor(main, own_cmd);
	if (own_cmd->pid == 0)
	{
		ok_free_function(main);
		exit(main->exit_code);
	}
	wait_for_children(main);
	setup_parent_signal_handlers();
}
