/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:51:49 by danimart          #+#    #+#             */
/*   Updated: 2023/10/16 01:12:13 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo_info	*print_info(t_philo_info *info)
{
	if (!DEBUG || info == NULL)
		return (info);
	printf(INFO_HEADER);
	printf(INFO_INT, "Philosopher amount", info->amount);
	printf(INFO_LONG, "Time to die", info->die_time);
	printf(INFO_INT, "Time to eat", info->eat_time);
	printf(INFO_INT, "Time to sleep", info->sleep_time);
	if (info->eat_num == 0)
		printf(INFO_STR, "Times to eat", "unlimited");
	else
		printf(INFO_INT, "Times to eat", info->eat_num);
	printf(INFO_FOOTER);
	return (info);
}

t_philo	*pause_philo(t_philo *philo, u_int64_t ms)
{
	useconds_t	to_match;

	to_match = get_current_ms(philo->prog_info) + ms;
	while (get_current_ms(philo->prog_info) < to_match)
	{
		mutex_lock(philo->m_ended);
		if (philo->ended == 1)
		{
			mutex_unlock(philo->m_ended, 0);
			return (NULL);
		}
		mutex_unlock(philo->m_ended, 0);
		usleep(100);
	}
	return (philo);
}

t_philo	*set_philo_state(t_philo *philo, int state, int print)
{
	char	*state_str;

	mutex_lock(philo->m_ended);
	if (philo->ended == 1)
	{
		mutex_unlock(philo->m_ended, 0);
		return (NULL);
	}
	if (state == DEAD)
		philo->ended = 1;
	mutex_unlock(philo->m_ended, 0);
	if (!print)
		return (philo);
	if (state == DEAD)
		state_str = PHILO_DIED;
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	else if (state == EATING)
		state_str = PHILO_EATING;
	mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id + 1);
	mutex_unlock(philo->prog_info->m_print, 0);
	return (philo);
}

void	free_philos(t_philo_info *info)
{
	int	id;

	id = 0;
	while (id < info->amount && info->philo_lst[id] != NULL)
	{
		pthread_join(info->philo_lst[id]->th_id, NULL);
		id++;
	}
	id = 0;
	while (id < info->amount && info->philo_lst[id] != NULL)
	{
		mutex_unlock(info->philo_lst[id]->m_fork, 1);
		mutex_unlock(info->philo_lst[id]->m_meal, 1);
		mutex_unlock(info->philo_lst[id]->m_ended, 1);
		free(info->philo_lst[id]);
		id++;
	}
}
