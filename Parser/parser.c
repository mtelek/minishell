/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/30 23:01:41 by mtelek           ###   ########.fr       */
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

void wait_for_children(t_main *main, int last_pid)
{
    int status;
    int exit_status;

    while (waitpid(-1, &status, 0) > 0)
    {
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
                main->exit_code = exit_status;
        }
        else if (WIFSIGNALED(status))
            main->exit_code = 128 + WTERMSIG(status);
    }
    if (waitpid(last_pid, &status, 0) > 0)
    {
        if (WIFEXITED(status))
            main->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            main->exit_code = 128 + WTERMSIG(status);
    }
}


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
		return(ft_exit(main->cmd, main), true);
	return (false);
}

int	echo_ex_env_check(t_main *main, t_cmd *own_cmd)
{
	char	*trimmed_str;

	trimmed_str = NULL;
	if (ft_strcmp(own_cmd->cmd, "exit") == 0)
	{
		if (own_cmd->pid == 0)
			ft_exit(own_cmd, main);
		return(1);
	}
	else if (ft_strcmp(own_cmd->cmd, "echo") == 0)
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
			main->exit_code = 0;
		}
		return (1);
	}
	else if (ft_strcmp(own_cmd->cmd, "env") == 0)
	{
		if (own_cmd->pid == 0)
		{
			ft_env(main);
			main->exit_code = 0;
		}
		return (1);
	}
	else if (ft_strcmp(own_cmd->cmd, "export") == 0)
	{
		if (!export_error(own_cmd->args, main) && own_cmd->pid == 0)
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
	{
		return ;
	}
	if (main->parser->n_pipes)
		own_cmd = init_pipes(main);
	else if (main->parser->n_pipes == 0)
	{
		pid = fork1(main);
		main->last_pid = pid;
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
	wait_for_children(main, main->last_pid);
}
