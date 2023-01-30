/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:44:16 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/30 16:13:50 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env_expand_hdoc(t_msh *msh, char *str)
{
	int		i;
	t_env	*cpy;

	i = 0;
	cpy = msh->env;
	while (cpy)
	{
		if (!ft_strncmp(str, cpy->name, ft_strlen(cpy->name))
			&& !ft_strncmp(str, cpy->name, ft_strlen(str)))
			return (cpy->value);
		else if (str[0] == '?')
			return (ft_itoa(g_value_exit));
		if (cpy->next)
			cpy = cpy->next;
		else
			break ;
	}
	return (NULL);
}

char	*fill_expand_hdoc(t_msh *msh, char *line, int i, int j, char *word)
{
	char	*str;
	char	*exp;
	int		x;

	x = -1;
	str = NULL;
	exp = check_env_expand_hdoc(msh, word);
	str = (char *)malloc(sizeof(char) + (ft_strlen(line)
				+ ft_strlen(exp) + 1 - ft_strlen(word)));
	if (!(str))
		return (NULL);
	if (word[0] != '?')
		free(word);
	while (++x < i)
		str[x] = line[x];
	x = 0;
	while (exp[x])
		str[i++] = exp[x++];
	while (line[j])
		str[i++] = line[j++];
	str[i] = '\0';
	if (exp[0] == '1')
		free(exp);
	free(line);
	return (str);
}

char	*fill_no_expand_hdoc(char *line, char *word, int i, int j)
{
	int		x;
	char	*str;

	x = 0;
	str = (char *)malloc(sizeof(char) + (ft_strlen(line)
				+ 2 - ft_strlen(word)));
	if (!str)
		return (NULL);
	ft_bzero(str, (ft_strlen(line) - ft_strlen(word) + 2));
	free(word);
	while (x < i)
	{
		str[x] = line[x];
		x++;
	}
	while (line[j])
	{
		str[x] = line[j];
		x++;
		j++;
	}
	str[x] = '\0';
	free(line);
	line = NULL;
	return (str);
}

void	add_expand_hdoc_bis(t_msh *msh, char *line, int i)
{
	char	*word;
	int		j;

	j = i + 1;
	while (line[j] && ft_isalnum(line[j]))
		j++;
	word = ft_substr(line, (i + 1), (j - i - 1));
	if (check_env_expand(msh, word))
		line = fill_expand_hdoc(msh, line, i, j, word);
	else
		line = fill_no_expand_hdoc(line, word, i, j);
}

char	*add_expand_hdoc(t_msh *msh, char *line)
{
	int		i;
	int		quote;

	i = -1;
	quote = 0;
	line = valeur_retour_bis(msh, line);
	while (line[++i])
		if (line[i] == '$' && ft_isalnum(line[i + 1]))
			add_expand_hdoc_bis(msh, line, i);
	return (line);
}
