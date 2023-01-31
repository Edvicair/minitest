/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:59:02 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/31 15:03:13 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_cd_fail(char *s)
{
    g_value_exit = 1;
    printf("\033[0;31mcd: no such file or directory : %s\n", s);
}