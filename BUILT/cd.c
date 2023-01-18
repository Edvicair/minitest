/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:47:57 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/13 17:08:13 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_pwd(t_msh *msh, char *pwd, char *path)
{
	t_env	*cpy;

	cpy = msh->env;
	while (cpy->next)
	{
		if (!ft_strcmp(cpy->name, pwd))
		{
			cpy->value = NULL;
			free(cpy->value);
			cpy->value = ft_strdup(msh, path);
			break ;
		}
		cpy = cpy->next;
	}
	cpy = msh->env;
}

void	ft_cd_home(t_msh *msh)
{
	int		ret;
	char	*home_path;
	char	*pwd;

	pwd = malloc(sizeof(char) * 200);
	if (!pwd)
		printf("error pwd/n");
	pwd = getcwd(pwd, 200);
	ft_export_pwd(msh, "OLDPWD", pwd);
	pwd = NULL;
	free(pwd);
	home_path = getenv("HOME");
	ret = chdir(home_path);
	if (ret == -1)
		printf("cd: no such file or directory : %s\n", home_path);
	else
		ft_export_pwd(msh, "PWD", home_path);
}

void	ft_cd_old(t_msh *msh)
{
	int		ret;
	char	*old_pwd;
	char	*pwd;

	pwd = malloc(sizeof(char) * 200);
	if (!pwd)
		printf("error pwd/n");
	old_pwd = ft_getenv(msh, "OLDPWD");
	pwd = getcwd(pwd, 200);
	ft_export_pwd(msh, "OLDPWD", pwd);
	pwd = NULL;
	free(pwd);
	ret = chdir(old_pwd);
	if (ret == -1)
		printf("cd: no such file or directory : %s\n", old_pwd);
	else
	{
		ft_export_pwd(msh, "PWD", old_pwd);
		printf("%s\n", old_pwd);
	}
}

void	ft_cd_path(t_msh *msh, char **cmd)
{
	int		ret;
	char	*old_pwd;
	char	*pwd;
	char	*new_pwd;

	pwd = malloc(sizeof(char) * 200);
	new_pwd = malloc(sizeof(char) * 200);
	if (!pwd)
		printf("error pwd/n");
	pwd = getcwd(pwd, 200);
	ft_export_pwd(msh, "OLDPWD", pwd);
	pwd = NULL;
	free(pwd);
	ret = chdir(cmd[1]);
	if (ret == -1)
		printf("cd: no such file or directory : %s\n", cmd[1]);
	else
		ft_export_pwd(msh, "PWD", getcwd(new_pwd, 200));
	new_pwd = NULL;
	free(new_pwd);
}

void	ft_cd(t_msh *msh, char **cmd)
{
	if (cmd[1] == NULL)
		ft_cd_home(msh);
	else if (cmd[1] && !ft_strncmp("--", cmd[1], 3))
		ft_cd_home(msh);
	else if (cmd[1] && !ft_strncmp("-", cmd[1], 2))
		ft_cd_old(msh);
	else if (cmd[1] != NULL)
		ft_cd_path(msh, cmd);
}
