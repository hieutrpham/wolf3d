/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:35:33 by trupham           #+#    #+#             */
/*   Updated: 2025/12/07 15:44:16 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FAIL 1
# define SUCC 0

int	err_message(char *string, int code);
int	ft_strcmp(char *s1, char *s2);
int check_file(char *str);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int					has_nl(const char *str);

#endif
