/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:10:32 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/18 17:08:21 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t count_tab(t_env *env)
{
	t_env *cpy;
	size_t count;

	cpy = env;
	count = 0;
	while (cpy && cpy->next)
	{
		count++;
		cpy = cpy->next;
	}
	return (count);
}

char	**tab_env(t_msh *msh, t_env *env)
{
	char **str;
	t_env *cpy;
	size_t i;

	cpy = env;
	i = count_tab(env);
	str = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (cpy->next)
	{
		if (cpy->name && cpy->value)
		{
			str[i] = ft_strjoin(msh, cpy->name, "=");
			str[i] = ft_strjoin(msh, str[i], cpy->value);
		}
		i++;
		cpy = cpy->next;
	}
	if (cpy->name && cpy->value)
	{
		str[i] = ft_strjoin(msh, cpy->name, "=");
		str[i] = ft_strjoin(msh, str[i], cpy->value);
		i++;
		str[i] = NULL;
	}
	return (str);
}

void ft_dup(t_msh *msh, t_token *token)
{
		if (msh->in)
		{
			dup2(msh->in, STDIN_FILENO);
			close(msh->in);
		}
		else if (msh->pip || token->redir->type == H_DOC)
		{
			dup2(msh->fd[0], STDIN_FILENO);
			close(msh->fd[0]);
		}
		if (msh->out != 1)
		{
			dup2(msh->out, STDOUT_FILENO);
			close(msh->out);
		}
		else if (msh->pip)
		{
			dup2(msh->fd[1], STDOUT_FILENO);
			close(msh->fd[1]);
		}
}

void	one_child(t_msh *msh, t_token *token)
{
	char **env;

	env = tab_env(msh, msh->env);
	token->child = fork();
	if (token->child == -1)
	{
		perror("Can't fork");
		exit(0);
	}
	if (token->child == 0)
	{
		ft_dup(msh, token);
		exec(msh, token->cmd, env);
	}
	else
	{
		close(msh->fd[0]);
		close(msh->fd[1]);
	}
}
