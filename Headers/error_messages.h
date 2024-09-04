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
# define MF_N_ENV_ARRAY "Error, malloc for creating new_env_array failed\n"
# define MF_HEREDOC "Error, malloc for creating heredoc_fd failed\n"
# define MF_BUILTIN "Error, malloc for creating builtin struct failed\n"
# define MF_EXEC "Error, malloc for creating exec struct failed\n"
# define MF_STRJOIN "Error, joining the two strings failed\n"
# define MF_STRTRIM "Error, malloc for trimming the word failed\n"
# define MF_SUBSTR "Error, malloc for creating substring failed\n"
# define MF_STRING "Error_malloc for creating string failed\n"
# define MF_NEW_STR "Error, malloc for creating new string failed\n"
# define MF_EXPNAD_NODE "Error, malloc for creating expand node failed\n"
# define MF_DELIMITER "Error, malloc for creating delimiters failed\n"
# define MF_CD_ARGV "Error, malloc for creating arguments in cd failed\n"
# define MF_T_CD "Error, malloc for creating cd struct failed\n"
# define MF_REALLOC "Error, reallocing memory failed\n"

//ERRORS FOR FAILURES
# define E_LIMIT_INSUF "Error: System process limit reached\n"
# define E_INSUF_MEM "Error: Insufficient memory to create a new process\n"
# define E_CREATING_PROCESS "Error creating process with fork"
# define E_INVALID_FD_PIPE "Error: Invalid file descriptor array for pipe()\n"
# define E_TOO_MANY_FD "Error: Too many file descriptors in use\n"
# define E_TOO_MANY_FILES "Error: Too many open files in the system\n"
# define E_PIPE_CREATION "Error creating pipe"
# define E_PERMISSION_D "Error: Can't open directory - Permission denied\n"
# define E_NO_DIR "Error: Directory not found '%s'\n"
# define E_BIN_NO_DIR "Error: it is not a directory\n"
# define E_OPEN_DIR "Error opening directory \n"
# define E_INV_D_STREAM "Error: Invalid directory stream "
# define E_READ_DIR "Error reading directory"
# define E_CLOSE_DIR "Error closing directory"
# define E_INV_FD_CLOSE "Error: Invalid file descriptor \n"
# define E_INT_SIG "Error: Close operation interrupted by signal\n"
# define E_CLOSE_FD "Error closing file descriptor "
# define E_INV_FD "Error: Invalid file descriptor" //
# define E_DUP_SIG "Error: Duplication interrupted"
# define E_TOO_MANY_FD_O "Error: Too many open fds"
# define E_DUP_FD "Error duplicating fd"
# define E_PERMISSION_D_OPEN "Error: Permission denied opening "
# define E_READ_ONLY "Error: Read-only file system"
# define E_OPEN_FILE "Error opening file : "
# define NO_CMD ": command not found\n"
# define IS_DIR ": is a directory\n"
# define NO_DIR ": No such file or directory\n"
# define NO_PERMISSION ": Permission denied\n"

//BUILTINS_ERRORS
# define E_NUM_ARG_P1 "exit\nbash: exit: "
# define E_NUM_ARG_P2 ": numeric argument required\n"
# define TOO_MANY_ARGS "exit\nbash: exit: too many arguments\n"
# define EXIT "exit\n"
# define ENV_NO_ACCES "bash: env: environment is not accessible\n"
# define EMPTY_ENV_VAR "bash: env: found empty environment variable\n"
# define NOT_VAILD_ID_1 "bash: export: `"
# define NOT_VALID_ID_2 "': not a valid identifier\n"

#endif