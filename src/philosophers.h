/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2025/08/01 21:37:02 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* - printf - */
# include <stdio.h>

/* - usleep - */
# include <unistd.h>

/* - INT_MAX macro - */
# include <limits.h>

/* - pthread (Multithreading) related functions - */
# include <pthread.h>

/* - malloc, free & NULL pointer */
# include <stdlib.h>

/* - gettimeofday - */
# include <sys/time.h>

/* - bool type - */
# include <stdbool.h>

/* - va macros - */
# include <stdarg.h>

# ifndef MAX_PHILOSOPHERS
// The maximum amount of philosophers. 200 by default
#  define MAX_PHILOSOPHERS 200
# endif

# define MAX_RECOMMENDED_PHILOSOPHERS 200

struct	s_philo_info;

// Enum used to represent the actual state of a philosopher.
typedef enum e_philo_state
{
	// The philosopher is currently well and alive (Active).
	ALIVE,
	// The philosopher is inactive (Ate enough times).
	INACTIVE,
	// The philosopher tragically died of starvation :(
	DEAD
}	t_philo_state;

// Enum used to represent the different phases a philosopher can be in
typedef enum e_philo_phase
{
	// Philosopher is currently THINKING, next phase is EATING.
	THINKING,
	// Philosopher is currently EATING, next phase is SLEEPING.
	EATING,
	// Philosopher is currently SLEEPING, next phase is THINKING.
	SLEEPING
}	t_philo_phase;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*m_state;
	t_philo_state		state;
	pthread_t			thread_id;
	int					eat_amount;
	int					last_meal_ms;
	struct s_philo_info	*info;
}			t_philo;

typedef struct s_philo_info
{
	// Param: The amount of philosophers on the simulation
	int				philo_n;
	// Param: The amount of ms philosophers have before dying of starvation
	int				die_ms;
	// Param: The amount of ms philosophers must eat
	int				eat_ms;
	// Param: The amount of ms philosophers must sleep
	int				sleep_ms;
	// Optional param: The amount of times every philosopher must eat
	int				eat_num;
	// The array of philosophers
	t_philo			*philo_lst[MAX_PHILOSOPHERS];
	// The printing mutex
	pthread_mutex_t	*m_print;
	// The date at which the simulation started
	size_t			start_date;
}				t_philo_info;

/*
 - Info
 */

t_philo_info	*get_info(void);

void			free_info(t_philo_info *info);

/*
 - Input parser
 */

t_philo_info	*parse_arguments(int argc, char **argv);

/*
 - Printer
 */

/**
 * @brief Fast printing function that respects the print mutex
 * from `t_philo_info->m_print`. It does not support format
 * specifiers or varargs.
 * 
 * If `str` is `NULL` or an empty string, the function exits
 * early without acquiring the mutex or making syscalls.
 * Otherwise, the entire string is written to `STDOUT_FILENO`
 * in a single `write` call to minimize syscall overhead.
 * 
 * @param str The string to print.
 */
void			p_print(const char *str);

/**
 * @brief Lightweight formatted printing function with support
 * for `%u` (`unsigned int` only). Uses the print mutex found in
 * `t_philo_info->m_print`.
 * 
 * The format string is parsed and printed in segments to
 * reduce the number of `write` syscalls. It uses only stack
 * memory, no heap allocations or recursion for maximum speed.
 * 
 * Only the `%u` specifier is supported. Any other character
 * following `%` is printed as-is.
 * 
 * @param str The format string. Passing `NULL` results in
 * undefined behavior.
 * @param ... The variable arguments for the format string.
 */
void			p_printf(const char *str, ...);

/*
 - Time
 */

int				get_current_ms(t_philo_info *info);

/**
 * @brief Three-phase sleep strategy to improve precision while keeping
 * CPU usage low.
 *
 * Phase 1:
 * Performs a long sleep using `usleep((ms - 10) * 1000)`, leaving a margin
 * of roughly 10 milliseconds to account for scheduling imprecision.
 *
 * Phase 2:
 * Performs shorter sleeps of 500 microseconds until approximately 3 milliseconds
 * remain. This phase balances precision with minimal CPU usage.
 *
 * Phase 3:
 * Performs a busy wait for the final ~3 milliseconds to ensure high precision,
 * accepting a brief increase in CPU usage.
 *
 * @param ms The number of milliseconds to sleep.
 */
void			p_sleep(size_t ms);

/*
 - Mutex utils
 */

bool			mutex_free(pthread_mutex_t *mutex);

pthread_mutex_t	*mutex_init(void);

/*
 - Philo functions
 */

t_philo			*init_philo(t_philo_info *info, int id);

/*
 - String utils
 */

unsigned int	p_strlen(const char *str);

/*
 - Input error messages
 */

// Input error: Invalid argument count - Too many arguments
# define ARGC_LONG "\e[0;31mError\e[1;30m: \e[1;31mToo many arguments\
\e[1;30m.\e[0m\n"

// Input error: Invalid argument count - Missing arguments title
# define ARGC_SMALL "\e[0;31mError\e[1;30m: \e[1;31mThe following\
 program arguments are missing\e[1;30m:\e[0m\n"

// Input error: Invalid argument count - Missing argument description
# define MISSING_ARG " \e[1;30m- \e[0;31m%s\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Amount of philosophers
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid number\
 of philosophers \e[1;30m[\e[1;33m1\e[1;30m-\e[1;33m%d\e[1;30m]\e[0m\n"

// Input warning: Too many philosophers - Using over 200 philosophers
# define AMOUNT_WARN "\e[0;33mWarning\e[1;30m: \e[1;33mUsing over\
 %i philosophers is not recommended\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Time to die
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to die\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Time to eat
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Time to sleep
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Times to eat
# define EAT_NUM_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid amount\
 of times to eat\e[1;30m.\e[0m\n"

/* External error messages */

// Internal error: Thread creation
# define THREAD_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not create\
 a new thread\e[1;30m.\e[0m\n"

// Internal error: Get time of day
# define GET_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not get current\
 time\e[1;30m.\e[0m\n"

// Internal error: Mutex creation
# define MUTEX_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not create\
 a new mutex\e[1;30m.\e[0m\n"

// Internal error: Malloc
# define MALLOC_ERR "\e[0;31mError\e[1;30m: \e[1;31mMalloc failed\e[1;30m.\
\e[0m\n"

/* Philosopher log messages */

// Log message: A philosopher took a fork (Left hand)
# define PHILO_TAKE_RFORK "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mRight\e[1;30m)\e[0m\n"

// Log message: A philosopher took a fork (Left hand)
# define PHILO_TAKE_LFORK "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mLeft\e[1;30m)\e[0m\n"

// Log message: A philosopher changed its state to EATING
# define PHILO_EATING "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;35meating\e[1;30m.\e[0m\n"

// Log message: A philosopher changed its state to SLEEPING
# define PHILO_SLEEPING "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;36msleeping\e[1;30m.\e[0m\n"

// Log message: A philosopher changed its state to THINKING
# define PHILO_THINKING "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;32mthinking\e[1;30m.\e[0m\n"

// Log message: A philosopher died :( - Simulation ends
# define PHILO_DIED "\e[1;30m[\e[0;31m%llu\e[1;30m] \e[1;31m%d \
died\e[1;30m.\e[0m\n"

// Log message: All philosophers survived - Simulation ends
# define ALL_SURVIVED "\e[1;30m[\e[0;32m%llu\e[1;30m] \e[1;32mAll philosophers\
 ate enough times, ending the simulation\e[1;30m.\e[0m\n"

#endif