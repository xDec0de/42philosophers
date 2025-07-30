/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:41:01 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/30 19:47:55 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_info(t_philo_info *info)
{
	pthread_mutex_unlock(info->m_print);
	pthread_mutex_destroy(info->m_print);
}
