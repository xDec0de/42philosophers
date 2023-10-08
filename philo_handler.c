/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/08 18:08:25 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	take_forks(t_philo *philo, t_philo *left)
{
	pthread_mutex_t	*m_print;

	m_print = philo->prog_info->m_print;
	pthread_mutex_lock(philo->m_fork);
	pthread_mutex_lock(m_print);
	printf(PHILO_TAKE_RFORK, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(m_print);
	pthread_mutex_lock(left->m_fork);
	pthread_mutex_lock(m_print);
	printf(PHILO_TAKE_LFORK, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(m_print);
}

void	*p_eat(t_philo *philo)
{
	t_philo	*left;

	if (set_philo_state(philo, THINKING) == NULL)
		return (NULL);
	if (philo->id == 0)
		left = philo->prog_info->philo_lst[philo->prog_info->amount - 1];
	else
		left = philo->prog_info->philo_lst[(philo->id - 1)];
	take_forks(philo, left);
	set_philo_state(philo, EATING);
	if (pause_philo(philo, philo->prog_info->eat_time) == NULL)
		return (NULL);
	pthread_mutex_unlock(philo->m_fork);
	pthread_mutex_unlock(left->m_fork);
	return (philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	void	*result;

	philo = (t_philo *) philo_ptr;
	result = philo_ptr;
	while (result != NULL)
	{
		result = p_eat(philo);
		if (result == NULL)
			return (NULL);
		pthread_mutex_lock(philo->m_meal);
		philo->meals += 1;
		philo->last_meal = get_current_ms(philo->prog_info);
		pthread_mutex_unlock(philo->m_meal);
		if (set_philo_state(philo, SLEEPING) == NULL)
			return (NULL);
		if (pause_philo(philo, philo->prog_info->sleep_time) == NULL)
			return (NULL);
		usleep(100);
	}
	return (philo_ptr);
}
