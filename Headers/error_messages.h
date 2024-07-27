/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:05:47 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:18:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define ERR_QUOTE2 "bash: syntax error, unclosed double quote occurred\n"
# define ERR_QUOTE1 "bash: syntax error, unclosed single quote occurred\n"
# define ERROR_M_NEWLINE  "bash: syntax error near unexpected token `newline'\n"
# define ERROR_M_PIPE "bash: syntax error near unexpected token `|'\n"
# define ERROR_M_LESSER "bash: syntax error near unexpected token `<'\n"
# define ERROR_M_GREATER "bash: syntax error near unexpected token `>'\n"
# define ERROR_M_LESSERP "bash: syntax error near unexpected token `<<'\n"
# define ERROR_M_GREATERP "bash: syntax error near unexpected token `>>'\n"

#endif