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

//ERRORS FOR SYNTAX
# define ERR_QUOTE2 "bash: syntax error, unclosed double quote occurred\n"
# define ERR_QUOTE1 "bash: syntax error, unclosed single quote occurred\n"
# define ERROR_M_NEWLINE  "bash: syntax error near unexpected token `newline'\n"
# define ERROR_M_PIPE "bash: syntax error near unexpected token `|'\n"
# define ERROR_M_LESSER "bash: syntax error near unexpected token `<'\n"
# define ERROR_M_GREATER "bash: syntax error near unexpected token `>'\n"
# define ERROR_M_LESSERP "bash: syntax error near unexpected token `<<'\n"
# define ERROR_M_GREATERP "bash: syntax error near unexpected token `>>'\n"

//ERRORS FOR MALLOCS
# define MF_OPERATOR "Error, malloc for operators failed\n"
# define MF_LEXER "Error, malloc for lexer failed\n"
# define MF_WORD "Error, malloc for creating the word failed\n"
# define MF_CMD_TABLE "Error, malloc for creating the command table failed\n"
# define MF_CMD_ARGS "Error, malloc for creating args failed\n"
# define MF_CMD_CMD "Error, malloc for creating cmd failed\n"
# define MF_PARSER "Error, malloc for creating parser failed\n"
# define MF_PIPES "Error, malloc for creating pipes failed\n"
# define MF_ONE_PIPE "Error, malloc for creating a pipe failed\n"
# define MF_INPUT_FD "Error, malloc for creating input_fd failed\n"
# define MF_OUPUT_FD "Error, malloc for creating output_fd failed\n"
# define MF_APPEND_OUT "Error, malloc for creating append_out_fd failed"
# define MF_ENV_LIST "Error, malloc failed for creating env list\n"
# define ERROR_STRDUP "Error, duplicating string failed\n"
# define MF_ENV_ARRAY "Error, malloc for creating env array failed\n"
# define MF_MAIN "Error, malloc for creating main struct failed\n"

//ERRORS FOR FAILURES
# define E_LIMIT_INSUF "Error: System process limit reached or insufficient resources to create new process\n"
# define E_INSUF_MEM "Error: Insufficient memory to create a new process\n"
# define E_CREATING_PROCESS "Error creating process with fork: %s\n"
# define E_INVALID_FD_PIPE "Error: Invalid file descriptors array provided to pipe()\n"
# define E_TOO_MANY_FD "Error: Too many file descriptors in use by the process\n"
# define E_TOO_MANY_FILES "Error: Too many files are currently open in the system\n"
# define E_PIPE_CREATION "Error creating pipe: %s\n"
# define E_PERMISSION_D "Error: Permission denied while opening directory '%s'\n"
# define E_NO_DIR "Error: Directory not found '%s'\n"
# define E_BIN_NO_DIR "Error: '%s' is not a directory\n"
# define E_OPEN_DIR "Error opening directory '%s': %s\n"
# define E_INV_D_STREAM "Error: Invalid directory stream (dir: %p)\n"
# define E_READ_DIR "Error reading directory (dir: %p): %s\n"
# define E_CLOSE_DIR "Error closing directory (dir: %p): %s\n"
# define E_INV_FD_CLOSE "Error: Invalid file descriptor (fd: %d)\n"
# define E_INT_SIG "Error: Close operation interrupted by signal (fd: %d)\n"
# define E_CLOSE_FD "Error closing file descriptor (fd: %d): %s\n"
# define E_INV_FD "Error: Invalid file descriptor (old_fd: %d, new_fd: %d)\n"
# define E_DUP_SIG "Error: Duplication interrupted by signal (old_fd: %d, new_fd: %d)\n"
# define E_TOO_MANY_FD_O "Error: Too many file descriptors open (old_fd: %d, new_fd: %d)\n"
# define E_DUP_FD "Error duplicating file descriptor (old_fd: %d, new_fd: %d): %s\n"
# define E_PERMISSION_D_OPEN "Error: Permission denied while opening file '%s'\n"
# define E_NO_FILE "Error: No such file or directory '%s'\n"
# define E_READ_ONLY "Error: Read-only file system '%s'\n"
# define E_OPEN_FILE "Error opening file '%s': %s\n"

#endif