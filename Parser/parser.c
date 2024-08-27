/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/27 16:13:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	calling_redirects(t_main *main, t_cmd *own_cmd)
{
	if (own_cmd->pid == 0)
	{
		if (own_cmd->n_in)
			init_infile(main, own_cmd);
		if (own_cmd->n_out)
			init_outfile(main, own_cmd);
		if (own_cmd->n_append)
			init_append_out(main, own_cmd);
		if (own_cmd->n_heredoc)
		{
			main->heredoc_flag = 1;
			init_heredoc(main, own_cmd);
		}
	}
}

void	wait_for_children(t_main *main)
{
	int	i;
	int	status;
	int	count;
	int	exit_status;

	i = 0;
	if (main->exec->n_childs)
		count = main->exec->n_childs;
	else
		count = 1;
	while (i < count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				main->exit_code = exit_status;
		}
		else if (WIFSIGNALED(status))
			main->exit_code = 128 + WTERMSIG(status);
		i++;
	}
}

bool	builtin_check(t_main *main)
{
	int	argc;

	argc = count_arg(main->cmd->args);
	if (ft_strncmp(main->cmd->cmd, "cd", 2) == 0)
		return (ft_cd(main, argc), true);
	else if (ft_strncmp(main->cmd->cmd, "exit", 4) == 0)
		return (ft_exit(main), true);
	else if (ft_strncmp(main->cmd->cmd, "export", 6) == 0)
	{
		if (!export_error(main->cmd->args, main))
			ft_export(main, main->cmd->args);
		return (true);
	}
	else if (ft_strncmp(main->cmd->cmd, "unset", 5) == 0)
	{
		if (!unset_error(main->cmd->args, main))
			ft_unset(main, main->cmd->args);
		return (true);
	}
	else if (ft_strncmp(main->cmd->cmd, "pwd", 3) == 0)
		return (ft_pwd(main), true);
	else if (ft_strncmp(main->cmd->cmd, "env", 3) == 0)
		return (ft_env(main), true);
	return (false);
}

int	echo_check(t_main *main, t_cmd *own_cmd)
{
	char	*trimmed_str;

	trimmed_str = NULL;
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
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
		}
		main->exit_code = 0;
		return (1);
	}
	return (0);
}

void	parser(t_main *main)
{
	t_cmd	*own_cmd;
	__pid_t	pid;

	own_cmd = NULL;
	creating_cmd_table(main);
	alloc_parser(main);
	find_hd_indicator(main, main->cmd);
	alloc_exec(main);
	alloc_builtin(main);
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
	if (!echo_check(main, own_cmd) && own_cmd->pid == 0)
		executor(main, own_cmd);
	if (own_cmd->pid == 0)
	{
		ok_free_function(main);
		exit(0);
	}
	wait_for_children(main);
}
