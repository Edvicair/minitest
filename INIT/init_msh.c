/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:41:27 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 14:38:58 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_struct(t_msh *msh, char **env)
{
	msh->env = fill_env(msh, env);
	msh->tab = 0;
	msh->line = NULL;
	msh->token = NULL;
	msh->stin = 0;
	msh->stout = 0;
	msh->in = 0;
	msh->out = 1;
	msh->pip = 0;
}
