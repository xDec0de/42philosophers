/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 17:16:48 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include "philosopher.h"

// Struct used to store program information such as parameters and philosophers
typedef struct s_philo_info {
	int		amount;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_num;
	t_philo	philo_lst[MAX_PHILOSOPHERS];
}				t_philo_info;

/* Error messages */

// Invalid argument count.
# define ARGC_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid input\
\e[1;30m.\e[0m\n"
// Invalid amount of philosophers.
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid number\
 of philosophers \e[1;30m(\e[33;31mMax is %d\e[1;30m)\e[0m\n"
// Warn philosophers over 200 if a higher amount is allowed.
# define AMOUNT_WARN "\e[0;33mWarning\e[1;30m: \e[33;33mUsing over\
 200 philosophers is not recommended\e[1;30m.\e[0m\n"
// Invalid time to die.
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid time\
 to die\e[1;30m.\e[0m\n"
// Invalid time to eat.
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"
// Invalid time to sleep.
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"
// Invalid amount of times to eat.
# define EAT_NUM_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid amount\
 of times to eat\e[1;30m.\e[0m\n"
// Error creating a thread.
# define THREAD_ERR "\e[0;31mError\e[1;30m: \e[33;31mCould not create\
 a new thread\e[1;30m.\e[0m\n"

/* Philosopher log messages */

// Invalid time to die.
# define PHILO_TAKE_RFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mRight\e[1;30m)\e[0m\n"
// Invalid time to die.
# define PHILO_TAKE_LFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mLeft\e[1;30m)\e[0m\n"
// Invalid time to die.
# define PHILO_EATING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;35meating\e[1;30m.\e[0m\n"
// Invalid time to die.
# define PHILO_SLEEPING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;36msleeping\e[1;30m.\e[0m\n"
// Invalid time to die.
# define PHILO_THINKING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;32mthinking\e[1;30m.\e[0m\n"
// Invalid time to die.
# define PHILO_DIED "\e[1;30m[\e[0;31m%d\e[1;30m] \e[1;31m%d \
died\e[1;30m.\e[0m\n"

#endif