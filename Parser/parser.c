/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/02 13:23:21 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

bool	builtin_check(t_main *main)
{
	int	argc;

	argc = count_arg(main->cmd->args);
	if (ft_strcmp(main->cmd->cmd, "cd") == 0 && !main->parser->n_pipes)
		return (ft_cd(main, argc), true);
	else if (ft_strcmp(main->cmd->cmd, "exit") == 0 && (main->cmd->next == NULL
			&& !((main->cmd->args[2]) && ft_isnumeric_str(main->cmd->args[1]))))
		return (ft_exit(main->cmd, main), true);
	else if (ft_strcmp(main->cmd->cmd, "unset") == 0 && main->cmd->next == NULL)
	{
		unset_helper(main->cmd, main);
		return (true);
	}
	else if (ft_strcmp(main->cmd->cmd, "export") == 0 && !main->cmd->next)
	{
		export_helper(main->cmd, main);
		return (true);
	}
	return (false);
}

void	echo_helper(t_cmd *own_cmd, t_main *main)
{
	if (own_cmd->pid == 0)
	{
		ft_echo(own_cmd);
		main->exit_code = 0;
	}
}

int	cd_unset_check(t_main *main, t_cmd *own_cmd)
{
	if (ft_strcmp(own_cmd->cmd, "unset") == 0 && main->cmd->next)
		return (1);
	else if (ft_strcmp(own_cmd->cmd, "cd") == 0 && main->cmd->next)
		return (1);
	return (0);
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
		if ((own_cmd->pid == 0 && main->cmd->next))
			export_helper(own_cmd, main);
		return (1);
	}
	else if (ft_strcmp(own_cmd->cmd, "pwd") == 0)
	{
		if (own_cmd->pid == 0)
			ft_pwd(main);
		return (1);
	}
	else if (cd_unset_check(main, own_cmd) == 1)
		return (1);
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
	if (!echo_ex_env_check(main, own_cmd)
		&& ft_strcmp(own_cmd->cmd, "cd"))
		executor(main, own_cmd);
	if (own_cmd->pid == 0)
	{
		ok_free_function(main);
		exit(main->exit_code);
	}
	wait_for_children(main);
}
