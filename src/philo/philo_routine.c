/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:33:03 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 22:42:10 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	p_take_forks(t_philo *philo, t_philo *left)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(left->m_fork);
		p_printf(PHILO_TAKE_LFORK, get_current_ms(philo->info), philo->id);
		pthread_mutex_lock(philo->m_fork);
		p_printf(PHILO_TAKE_RFORK, get_current_ms(philo->info), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->m_fork);
		p_printf(PHILO_TAKE_RFORK, get_current_ms(philo->info), philo->id);
		pthread_mutex_lock(left->m_fork);
		p_printf(PHILO_TAKE_LFORK, get_current_ms(philo->info), philo->id);
	}
}

static void	p_eat(t_philo *philo)
{
	t_philo	*left;

	if (philo->id == 1)
		left = philo->info->philo_lst[philo->info->philo_n - 1];
	else
		left = philo->info->philo_lst[(philo->id - 2)];
	p_take_forks(philo, left);
	p_printf(PHILO_EATING, get_current_ms(philo->info), philo->id);
	p_sleep(philo->info->eat_ms);
	pthread_mutex_unlock(left->m_fork);
	pthread_mutex_unlock(philo->m_fork);
}

void	*launch_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	while (true)
	{
		p_printf(PHILO_THINKING, get_current_ms(philo->info), philo->id);
		p_eat(philo);
		p_printf(PHILO_SLEEPING, get_current_ms(philo->info), philo->id);
		p_sleep(philo->info->sleep_ms);
	}
	pthread_mutex_lock(philo->m_state);
	philo->state = INACTIVE;
	pthread_mutex_unlock(philo->m_state);
	return (philo_ptr);
}
