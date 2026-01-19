/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:04:12 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/25 18:28:45 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int		has_nl(const char *str);
bool 	ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif
