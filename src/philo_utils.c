/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:51:49 by danimart          #+#    #+#             */
/*   Updated: 2025/07/01 20:48:42 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_current_ms(t_philo_info *info)
{
	return (get_current_time(info) - info->start_date);
}

int	get_current_time(t_philo_info *info)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (*(int *) free_info(GET_TIME_ERR, info, NULL));
	return (((time.tv_sec * (int) 1000) + (time.tv_usec / 1000)));
}

t_philo	*pause_philo(t_philo *philo, int ms)
{
	int	to_match;

	to_match = get_current_ms(philo->prog_info) + ms;
	while (get_current_ms(philo->prog_info) < to_match)
	{
		mutex_lock(philo->m_ended);
		if (philo->ended)
		{
			mutex_unlock(philo->m_ended, false);
			return (NULL);
		}
		mutex_unlock(philo->m_ended, false);
	}
	return (philo);
}

t_philo	*set_philo_state(t_philo *philo, int state, bool print)
{
	char	*state_str;
	bool	ended;

	mutex_lock(philo->m_ended);
	ended = philo->ended;
	mutex_unlock(philo->m_ended, false);
	if (ended)
		return (NULL);
	if (!print)
		return (philo);
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	else if (state == EATING)
		state_str = PHILO_EATING;
	mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	mutex_unlock(philo->prog_info->m_print, false);
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
		mutex_unlock(info->philo_lst[id]->m_fork, true);
		mutex_unlock(info->philo_lst[id]->m_meal, true);
		mutex_unlock(info->philo_lst[id]->m_ended, true);
		mutex_unlock(info->philo_lst[id]->m_ready, true);
		free(info->philo_lst[id]);
		id++;
	}
}
