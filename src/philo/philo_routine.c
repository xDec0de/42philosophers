/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:33:03 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/03 17:54:37 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	p_can_continue(t_philo *philo)
{
	t_philo_state	state;

	pthread_mutex_lock(philo->m_state);
	state = philo->state;
	pthread_mutex_unlock(philo->m_state);
	return (state != PAUSED && state != DEAD);
}

static bool	p_try_sleep(t_philo *philo, int ms)
{
	int	current_ms;

	if (!p_can_continue(philo))
		return (false);
	current_ms = get_current_ms(philo->info);
	if (((current_ms + ms) - philo->last_meal_ms) > philo->info->die_ms)
	{
		p_sleep(philo->info->die_ms - (current_ms - philo->last_meal_ms));
		pthread_mutex_lock(philo->m_state);
		philo->state = DEAD;
		pthread_mutex_unlock(philo->m_state);
		return (false);
	}
	p_sleep(ms);
	return (true);
}

static bool	p_take_forks(t_philo *philo, t_philo *left)
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
	return (true);
}

static bool p_eat(t_philo *philo)
{
	t_philo	*left;
	bool	alive;

	if (philo->id == 1)
		left = philo->info->philo_lst[philo->info->philo_n - 1];
	else
		left = philo->info->philo_lst[(philo->id - 2)];
	if (!p_take_forks(philo, left))
		return (false);
	p_printf(PHILO_EATING, get_current_ms(philo->info), philo->id);
	philo->last_meal_ms = get_current_ms(philo->info);
	alive = p_try_sleep(philo, philo->info->eat_ms);
	pthread_mutex_unlock(left->m_fork);
	pthread_mutex_unlock(philo->m_fork);
	philo->eat_amount++;
	return (alive);
}

void	*launch_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	while (true)
	{
		if (!p_can_continue(philo))
			break ;
		p_printf(PHILO_THINKING, get_current_ms(philo->info), philo->id);
		if (!p_eat(philo))
			break ;
		if (philo->eat_amount == philo->info->eat_num)
		{
			pthread_mutex_lock(philo->m_state);
			philo->state = INACTIVE;
			pthread_mutex_unlock(philo->m_state);
			break ;
		}
		if (!p_can_continue(philo))
			break ;
		p_printf(PHILO_SLEEPING, get_current_ms(philo->info), philo->id);
		if (!p_try_sleep(philo, philo->info->sleep_ms))
			break ;
	}
	return (philo_ptr);
}
