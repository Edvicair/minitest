/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:07:26 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/29 00:42:01 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_shell_lvl(char *value)
{
	int		nb;

	nb = ft_atoi(value);
	nb += 1;
	return (ft_itoa(nb));
}

t_env	*ft_env_new(t_msh *msh, char *name, char *value, bool egal)
{
	t_env	*lst_env;

	lst_env = (t_env *)malloc(sizeof(t_env));
	if (!lst_env)
		return (NULL);
	lst_env->name = ft_strdup(name);
	if (!value)
		lst_env->value = NULL;
	else if (!ft_strncmp(lst_env->name, "SHLVL", 6))
		lst_env->value = ft_shell_lvl(value);
	else
		lst_env->value = ft_strdup(value);
	if (!egal)
		lst_env->egal = 0;
	else
		lst_env->egal = 1;
	lst_env->next = 0;
	return (lst_env);
}

t_env	*ft_env_last(t_env *env)
{
	if (env)
	{
		while (env->next)
			env = env->next;
	}
	return (env);
}

void	ft_env_add_back(t_env **env, t_env *new)
{
	t_env	*lst_env;

	if (env)
	{
		if (*env)
		{
			lst_env = ft_env_last(*env);
			lst_env->next = new;
		}
		else
			*env = new;
	}
}

t_env	*fill_env(t_msh *msh, char **env)
{
	int		i;
	char	**line;
	t_env	*new_env;

	i = 0;
	new_env = NULL;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		ft_env_add_back(&new_env, ft_env_new(msh, line[0], line[1], 0));
		ft_free_double(line);
		i++;
	}
	return (new_env);
}
