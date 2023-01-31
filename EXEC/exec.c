/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:46:25 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/31 15:19:44 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_child(t_msh *msh, t_env *cpy, char **env, char *paths)
{
		ft_free_double(env);
		ft_free_env(cpy);
		ft_free_token(msh, msh->token);
		free(paths);
		free(msh->line);
		free(msh->tab);
}

static char	*test_path(t_msh *msh, char **cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*path_b;

	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		path_b = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path_b, X_OK) == 0)
			return (path_b);
		free(path_b);
		i++;
	}
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	return (NULL);
}

char	*exec_bis(t_msh *msh, t_env *cpy, char **cmd)
{
	char	**path;
	char	*paths;

	while (cpy)
	{
		if (!ft_strncmp(cpy->name, "PATH", 5))
		{
			path = ft_split(cpy->value, ':');
			break ;
		}
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	paths = test_path(msh, cmd, path);
	ft_free_double(path);
	return (paths);
}

void	exec(t_msh *msh, char **cmd, char **env)
{	
	char	*paths;
	t_env	*cpy;

	cpy = msh->env;
	paths = exec_bis(msh, cpy, cmd);
	if (paths == NULL)
	{
		printf("\033[0;31mCan't find command\n");
		ft_free_child(msh, cpy, env, paths);
		exit(127);
	}
	else if (execve(paths, cmd, env) == -1)
	{
		printf("\033[0;31mCan't execve\n");
		ft_free_child(msh, cpy, env, paths);
		exit(127);
	}
}
