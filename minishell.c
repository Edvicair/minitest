/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:39:31 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/18 17:28:42 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built(t_msh *msh, char **cmd)
{
	if (cmd[0] && (!ft_strncmp(cmd[0], "cd", 3) || !ft_strncmp(cmd[0], "exit", 5)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "echo", 5) || !ft_strncmp(cmd[0], "pwd", 4)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "env", 4) || !ft_strncmp(cmd[0], "getenv", 7)))
		return (1);
	else if (cmd[0] && (!ft_strncmp(cmd[0], "export", 7) || !ft_strncmp(cmd[0], "unset", 6)))
		return (1);
	return (0);
}

void	exec_built(t_msh *msh, char **cmd)
{
	if (msh->pip == 0)
	{
		if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "cd", 3))
			ft_cd(msh, cmd);
		else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "unset", 6))
			ft_unset(msh, cmd);
			 if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "exit", 5))
			ft_exit(msh);
	}
	if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "pwd", 4))
		ft_pwd(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "env", 4))
		ft_env(msh);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "echo", 5))
		ft_echo(msh, cmd);
	else if (msh->token->cmd[0] && !ft_strncmp(msh->token->cmd[0], "export", 7))
		ft_export(msh, cmd);
}

void	ft_cmd(t_msh *msh)
{
	t_token *cpy;
	t_redir *redir_cpy;

	cpy = msh->token;
	while (msh->pip >= 0)
	{
		ft_check_redirection(msh);
	 	if (is_built(msh, cpy->cmd))
	 		exec_built(msh, cpy->cmd);
		else
		{
			one_child(msh, cpy);
			if (cpy->child)
				waitpid(cpy->child, NULL, 0);
		}
		if (msh->pip)
		{
			if (msh->out != 1)
			{
				msh->fd[1] = msh->out;
				close(msh->out);
			}
			else
			{
				msh->fd[1] = msh->fd[0];
				close(msh->fd[0]);
			}
			cpy = cpy->next;
		}
		msh->pip--;
	}
	ft_free_token(msh);
}

int	main(int ac, char **av, char **env)
{
	t_msh	msh;
	t_env	*cpy;

	ft_init_struct(&msh, env);
	while (1)
	{
		msh.line = space_chips(readline("minizboub-> "));
		if (msh.line)
		{
			add_history(msh.line);
			if (parser(&msh))
			{
				if (msh.token)
					ft_cmd(&msh);
			}
			free(msh.line);
		}
		else
			break;
	}
	printf("exit\n");
	free(msh.line);
	return (0);
}