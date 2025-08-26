/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   220_minishell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:39:52 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/08/26 18:39:52 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds_pipes(t_shell *shell)
{
	close_all_fds(shell->tree);
	close_all_pipes(shell);
}
