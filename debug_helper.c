/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:21:03 by danimart          #+#    #+#             */
/*   Updated: 2023/09/30 19:43:59 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"
#include "headers/text_colors.h"

char	*get_state_name(int state)
{
	if (state == DEAD)
		return (RED"dead");
	else if (state == INACTIVE)
		return (YELLOW"inactive");
	else if (state == EATING)
		return (B_GREEN"eating");
	else if (state == F_EATING)
		return (B_GREEN"eating"B_GRAY" ("WHITE"Finished"B_GRAY")");
	else if (state == SLEEPING)
		return (MAGENTA"sleeping");
	else if (state == F_SLEEPING)
		return (MAGENTA"sleeping"B_GRAY" ("WHITE"Finished"B_GRAY")");
	else if (state == THINKING)
		return (B_BLUE"thinking");
	return (B_RED"broken");
}

t_philo_info	*test_philosophers(t_philo_info *info)
{
	int		id;
	t_philo	*philo;

	if (!DEBUG)
		return (info);
	id = 0;
	while (id < info->amount)
	{
		philo = info->philo_lst[id];
		printf(DEBUG_PREFIX PHILO_STATE, id, get_state_name(philo->state));
		id++;
	}
	return (info);
}
