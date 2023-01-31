/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:48:15 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 19:09:25 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	ft_choose_type(int R)
{
	t_type	t;

	if (R == 1)
		t = RE_G;
	else if (R == 2)
		t = H_DOC;
	else if (R == -1)
		t = RE_D;
	else if (R == -2)
		t = RE_DD;
	else
		t = NO_REDIR;
	return (t);
}

size_t	count_tab(t_env *env)
{
	t_env	*cpy;
	size_t	count;

	cpy = env;
	count = 0;
	while (cpy)
	{
		count++;
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	return (count);
}

char	*valeur_retour(t_msh *msh, char *line)
{
	int		i;
	char	*ss;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = split_what(line, i, line[i]);
		if (line[i] == '$' && line[i + 1] == '?')
		{
			ss = "?\0";
			line = fill_expand(msh, i, (i + 2), ss);
			return (line);
		}
		i++;
	}
	return (line);
}
