/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:42:05 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/03 20:45:15 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_set_state(t_philo *philo, t_philo_state state)
{
	pthread_mutex_lock(philo->m_state);
	philo->state = state;
	pthread_mutex_unlock(philo->m_state);
}
