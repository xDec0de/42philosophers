/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:33:03 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/04 18:52:23 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	p_can_continue(t_philo *philo)
{
	bool	cont;

	pthread_mutex_lock(philo->m_last_meal_ms);
	cont = philo->last_meal_ms >= 0;
	pthread_mutex_unlock(philo->m_last_meal_ms);
	return (cont);
}

static bool	p_take_forks(t_philo *philo, t_philo *left)
{
	t_philo	*first;
	t_philo	*second;

	first = philo;
	second = left;
	if (philo->id % 2 == 0)
	{
		first = left;
		second = philo;
	}
	pthread_mutex_lock(first->m_fork);
	if (!p_can_continue(philo))
		return (pthread_mutex_unlock(first->m_fork), false);
	p_printf(PHILO_TAKE_FORK, PRINT_GET_MS, philo->id);
	pthread_mutex_lock(second->m_fork);
	if (!p_can_continue(philo))
	{
		pthread_mutex_unlock(first->m_fork);
		return (pthread_mutex_unlock(second->m_fork), false);
	}
	p_printf(PHILO_TAKE_FORK, PRINT_GET_MS, philo->id);
	return (true);
}

static bool	p_eat(t_philo *philo)
{
	t_philo	*left;

	if (philo->id == 1)
		left = philo->info->philo_lst[philo->info->philo_n - 1];
	else
		left = philo->info->philo_lst[(philo->id - 2)];
	if (!p_take_forks(philo, left))
		return (false);
	if (!p_can_continue(philo))
	{
		pthread_mutex_unlock(left->m_fork);
		pthread_mutex_unlock(philo->m_fork);
		return (false);
	}
	p_printf(PHILO_EATING, PRINT_GET_MS, philo->id);
	pthread_mutex_lock(philo->m_last_meal_ms);
	philo->last_meal_ms = get_current_ms(philo->info);
	pthread_mutex_unlock(philo->m_last_meal_ms);
	p_sleep(philo->info->eat_ms);
	pthread_mutex_unlock(left->m_fork);
	pthread_mutex_unlock(philo->m_fork);
	philo->eat_amount++;
	return (true);
}

static void	sync_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->info->m_hold);
	pthread_mutex_unlock(philo->info->m_hold);
	if (philo->id % 2 == 0)
		usleep(1000);
}

void	*launch_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	sync_philo(philo);
	while (true)
	{
		if (!p_can_continue(philo))
			break ;
		p_printf(PHILO_THINKING, PRINT_GET_MS, philo->id);
		if (!p_eat(philo))
			break ;
		if (philo->eat_amount == philo->info->eat_num)
		{
			pthread_mutex_lock(philo->m_last_meal_ms);
			philo->last_meal_ms = LAST_MEAL_MS_DONE;
			pthread_mutex_unlock(philo->m_last_meal_ms);
			break ;
		}
		if (!p_can_continue(philo))
			break ;
		p_printf(PHILO_SLEEPING, PRINT_GET_MS, philo->id);
		p_sleep(philo->info->sleep_ms);
	}
	return (philo_ptr);
}
