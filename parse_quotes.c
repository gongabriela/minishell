/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:40:06 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/06/06 19:40:06 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
//- Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
//- Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).