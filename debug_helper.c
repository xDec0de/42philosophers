/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:21:03 by danimart          #+#    #+#             */
/*   Updated: 2023/10/01 17:46:10 by danimart         ###   ########.fr       */
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

t_philo_info	*print_info(t_philo_info *info)
{
	if (!DEBUG || info == NULL)
		return (info);
	printf(DEBUG_NOTE);
	printf(INFO_HEADER);
	printf(INFO_NUM, "Philosopher amount", info->amount);
	printf(INFO_NUM, "Time to die", info->die_time);
	printf(INFO_NUM, "Time to eat", info->eat_time);
	printf(INFO_NUM, "Time to sleep", info->sleep_time);
	printf(INFO_NUM, "Times to eat", info->eat_num);
	printf(INFO_FOOTER);
	return (info);
}
