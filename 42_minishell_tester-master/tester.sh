#!/usr/bin/env -S --default-signal bash

# Change if you store the tester in another PATH
export MINISHELL_PATH=./
export EXECUTABLE=minishell
RUNDIR=$HOME/42_minishell_tester
DATE=$(date +%Y-%m-%d_%H.%M.%S)
TMP_OUTDIR=$RUNDIR/tmp_$DATE
OUTDIR=$MINISHELL_PATH/mstest_output_$DATE

# Test how minishell behaves to adjust the output filters to it
adjust_to_minishell() {
	# Get the prompt of the minishell in case it needs to be filtered out
	MINISHELL_PROMPT=$(echo -n "" | $MINISHELL_PATH/$EXECUTABLE 2>/dev/null | tail -n 1)
	# Escape special characters
	MINISHELL_PROMPT=$(echo -n "$MINISHELL_PROMPT" | sed 's:[][\/.^$*]:\\&:g')

	# Check if a command gives as the first line of output exactly the prompt with the input
	# If it does, the minishell uses readline
	if echo -n "this_is_the_input" | $MINISHELL_PATH/$EXECUTABLE 2>/dev/null | head -n 1 | grep -q "^${MINISHELL_PROMPT}this_is_the_input$" ; then
		READLINE="true"
	fi

	# Get the name of the minishell by running a command that produces an error
	# The name will then be filtered out from error messages
	MINISHELL_ERR_NAME=$(echo -n "|" | $MINISHELL_PATH/$EXECUTABLE 2>&1 >/dev/null | awk -F: '{if ($0 ~ /:/) print $1; else print ""}')
	MINISHELL_ERR_NAME=$(echo -n "$MINISHELL_ERR_NAME" | sed 's:[][\/.^$*]:\\&:g')

	# Get the exit message of the minishell in case it needs to be filtered out
	# The exit message should always get printed to stderr, bash does it too (see `exit 2>/dev/null`)
	MINISHELL_EXIT_MSG=$(echo -n "" | $MINISHELL_PATH/$EXECUTABLE 2>&1 >/dev/null | tail -n 1)
	MINISHELL_EXIT_MSG=$(echo -n "$MINISHELL_EXIT_MSG" | sed 's:[][\/.^$*]:\\&:g')
}

check_exit_stderr() {
	if echo -n "exit" | $MINISHELL_PATH/$EXECUTABLE 2>/dev/null | grep -q "exit" ; then
		echo -e "\033[1;31mERROR: Your minishell prints 'exit' to STDOUT instead of STDERR."
		echo -e "All the STDOUT tests will fail because bash prints 'exit' to STDERR.\033[m"
		echo -e "Find more information here:"
		echo -e "\033[4;94mhttps://github.com/LeaYeh/42_minishell_tester?tab=readme-ov-file#all-my-stdout-tests-fail\033[m"
		echo
		if ! prompt_with_enter "Are you sure you want to continue?" ; then
			exit 1
		fi
	fi
}

BASH="bash --posix"

export PATH="/bin:/usr/bin:/usr/sbin:$PATH"
VALGRIND_FLAGS=(
	--errors-for-leak-kinds=all
	--leak-check=full
	--show-error-list=yes
	--show-leak-kinds=all
	--suppressions="$RUNDIR/utils/minishell.supp"
	--trace-children=yes
	--trace-children-skip="$(echo /bin/* /usr/bin/* /usr/sbin/* $(which norminette) | tr ' ' ',')"
	--track-fds=all
	--track-origins=yes
	--log-file="$TMP_OUTDIR/tmp_valgrind_out"
	)
VALGRIND="valgrind ${VALGRIND_FLAGS[*]}"

NL=$'\n'
TAB=$'\t'

TEST_COUNT=0
TESTS_PASSED=0
TESTS_OK=0
TESTS_KO=0

SCRIPT_ARGS=("$@")

main() {
	trap sigint_trap SIGINT
	trap cleanup EXIT

	process_options "$@"

	if [[ "$NO_UPDATE" != "true" ]] ; then
		update_tester
	fi

	if [[ ! -f $MINISHELL_PATH/$EXECUTABLE ]] ; then
		echo -e "\033[1;33m# **************************************************************************** #"
		echo "#                            MINISHELL NOT COMPILED                            #"
		echo "#                                 COMPILING ...                                #"
		echo -e "# **************************************************************************** #\033[m"
		if ! make -s -C $MINISHELL_PATH || [[ ! -f $MINISHELL_PATH/$EXECUTABLE ]] ; then
			echo -e "\033[1;31mCOMPILING FAILED\033[m" && exit 1
		fi
	elif ! make --question -s -C $MINISHELL_PATH &>/dev/null ; then
		echo -e "\033[1;33m# **************************************************************************** #"
		echo "#                           MINISHELL NOT UP TO DATE                           #"
		echo "#                                 COMPILING ...                                #"
		echo -e "# **************************************************************************** #\033[m"
		if ! make -s -C $MINISHELL_PATH ; then
			echo -e "\033[1;31mCOMPILING FAILED\033[m" && exit 1
		fi
	fi

	if [[ $# -eq 0 ]] ; then
		print_usage
		exit 0
	fi

	check_exit_stderr
	adjust_to_minishell

	mkdir -p "$TMP_OUTDIR"
	process_tests "$@"

	if [[ $TEST_COUNT -gt 0 ]] ; then
		print_stats
	fi

	if [[ "$GITHUB_ACTIONS" == "true" ]] ; then
		echo "$GH_BRANCH=$TESTS_KO" >> "$GITHUB_ENV"
	fi

	if [[ $CRASHES -ne 0 ]] ; then
		exit 2
	elif [[ $LEAKS -ne 0 ]] ; then
		exit 1
	else
		exit 0
	fi
}

print_usage() {
	echo -e "  \033[1;33m# **************************************************************************** #"
	echo -e "  #                          USAGE: mstest [options]                             #"
	echo -e "  # Options:                                                                     #"
	echo -e "  #   m                      Run mandatory tests                                 #"
	echo -e "  #   vm                     Run mandatory tests with memory leak checks         #"
	echo -e "  #   b                      Run bonus tests                                     #"
	echo -e "  #   vb                     Run bonus tests with memory leak checks             #"
	echo -e "  #   ne                     Run empty environment tests                         #"
	echo -e "  #   vne                    Run empty environment tests with memory leak checks #"
	echo -e "  #   c                      Run crash tests                                     #"
	echo -e "  #   vc                     Run crash tests with memory leak checks             #"
	echo -e "  #   a                      Run all tests                                       #"
	echo -e "  #   va                     Run all tests with memory leak checks               #"
	echo -e "  #   -l|--leaks             Enable memory leak checks for any test              #"
	echo -e "  #      --no-stdfds         Don't report fd leaks of stdin, stdout, and stderr  #"
	echo -e "  #   -n|--no-env            Run any test with an empty environment              #"
	echo -e "  #   -f|--file <file>       Run tests specified in a file                       #"
	echo -e "  #   -d|--dir <directory>   Run tests specified in a directory                  #"
	echo -e "  #      --non-posix         Compare with normal bash instead of POSIX mode bash #"
	echo -e "  #      --no-update         Don't check for updates                             #"
	echo -e "  #   -h|--help              Show this help message and exit                     #"
	echo -e "  # **************************************************************************** #\033[m"
}

process_options() {
	while [[ $# -gt 0 ]] ; do
		case $1 in
			-l|--leaks)
				TEST_LEAKS="true"
				shift
				;;
			--no-stdfds)
				VALGRIND="${VALGRIND/--track-fds=all/--track-fds=yes}"
				shift
				;;
			-n|--no-env)
				NO_ENV="true"
				shift
				;;
			-f|--file)
				if [[ ! -f $2 ]] ; then
					echo "FILE NOT FOUND: \"$2\""
					exit 1
				fi
				shift 2
				;;
			-d|--dir)
				if [[ ! -d $2 ]] ; then
					echo "DIRECTORY NOT FOUND: \"$2\""
					exit 1
				fi
				shift 2
				;;
			-h|--help)
				print_usage
				exit 0
				;;
			--non-posix)
				BASH="bash"
				shift
				;;
			--no-update)
				NO_UPDATE="true"
				shift
				;;
			m|vm|b|vb|ne|vne|c|vc|a|va)
				shift
				;;
			*)
				echo "INVALID OPTION: $1"
				print_usage
				exit 1
				;;
		esac
	done
}

process_tests() {
	if [[ $TEST_LEAKS == "true" ]] ; then
		print_title "MEMORY_LEAKS" "💧"
	fi
	if [[ $NO_ENV == "true" ]] ; then
		print_title "NO_ENVIRONMENT" "🌐"
	fi
	while [[ $# -gt 0 ]] ; do
		case $1 in
			m)
				dir="mand"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="$NO_ENV"
				)
				print_title "MANDATORY" "🚀"
				run_tests "$dir" "test_flags"
				shift
				;;
			vm)
				dir="mand"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="true"
					[no_env]="$NO_ENV"
				)
				print_title "MANDATORY_LEAKS" "🚀"
				run_tests "$dir" "test_flags"
				shift
				;;
			b)
				dir="bonus"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="$NO_ENV"
				)
				print_title "BONUS" "🎉"
				run_tests "$dir" "test_flags"
				shift
				;;
			vb)
				dir="bonus"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="true"
					[no_env]="$NO_ENV"
				)
				print_title "BONUS_LEAKS" "🎉"
				run_tests "$dir" "test_flags"
				shift
				;;
			ne)
				dir="no_env"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="true"
				)
				print_title "NO_ENV" "🌐"
				run_tests "$dir" "test_flags"
				shift
				;;
			vne)
				dir="no_env"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="true"
					[no_env]="true"
				)
				print_title "NO_ENV_LEAKS" "🌐"
				run_tests "$dir" "test_flags"
				shift
				;;
			c)
				dir="crash"
				declare -A test_flags=(
					[stdout]="false"
					[stderr]="false"
					[exit_code]="false"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="$NO_ENV"
				)
				print_title "CRASH" "💥"
				run_tests "$dir" "test_flags"
				shift
				;;
			vc)
				dir="crash"
				declare -A test_flags=(
					[stdout]="false"
					[stderr]="false"
					[exit_code]="false"
					[crash]="true"
					[leaks]="true"
					[no_env]="$NO_ENV"
				)
				print_title "CRASH_LEAKS" "💥"
				run_tests "$dir" "test_flags"
				shift
				;;
			a)
				dir="all"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="$NO_ENV"
				)
				print_title "ALL" "🌟"
				run_tests "$dir" "test_flags"
				shift
				;;
			va)
				dir="all"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="true"
					[no_env]="$NO_ENV"
				)
				print_title "ALL_LEAKS" "🌟"
				run_tests "$dir" "test_flags"
				shift
				;;
			-f|--file)
				file="$2"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="$NO_ENV"
				)
				print_title "FILE: $file" "📄"
				run_tests_from_file "$file" "test_flags"
				shift 2
				;;
			-d|--dir)
				dir="$2"
				declare -A test_flags=(
					[stdout]="true"
					[stderr]="true"
					[exit_code]="true"
					[crash]="true"
					[leaks]="$TEST_LEAKS"
					[no_env]="$NO_ENV"
				)
				print_title "DIRECTORY: $dir" "📁"
				run_tests_from_dir "$dir" "test_flags"
				shift 2
				;;
			*)
				shift
				;;
		esac
	done
}

print_title() {
	local title="$1"
	local s="$2"
	local total_length=80
	local title_length=${#title}
	local padding_length_left=$(( (total_length - title_length - 4) / 2 ))
	local padding_length_right=$((padding_length_left + (total_length - title_length - 4) % 2))
	local padding_left=$(printf '%*s' "$padding_length_left" "")
	local padding_right=$(printf '%*s' "$padding_length_right" "")

	echo "  $s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s"
	echo -e "  $s${padding_left}\033[1;34m$title\033[m${padding_right}$s"
	echo "  $s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s$s"
}

run_tests() {
	local dir=$1
	local test_flags_ref_name=$2
	local -n test_flags_ref=$test_flags_ref_name
	declare -A test_flags_no_env=(
		[stdout]="${test_flags_ref[stdout]}"
		[stderr]="${test_flags_ref[stderr]}"
		[exit_code]="${test_flags_ref[exit_code]}"
		[crash]="${test_flags_ref[crash]}"
		[leaks]="${test_flags_ref[leaks]}"
		[no_env]="true"
	)
	declare -A test_flags_crash=(
		[stdout]="false"
		[stderr]="false"
		[exit_code]="false"
		[crash]="true"
		[leaks]="${test_flags_ref[leaks]}"
		[no_env]="${test_flags_ref[no_env]}"
	)
	local files

	if [[ $dir == "all" ]] ; then
		files="${RUNDIR}/cmds/**/*.sh"
	else
		files="${RUNDIR}/cmds/${dir}/*"
	fi
	for file in $files ; do
		if [[ $(basename "$(dirname "$file")") == "no_env" ]] ; then
			run_test "$file" "test_flags_no_env"
		elif [[ $(basename "$(dirname "$file")") == "crash" ]] ; then
			run_test "$file" "test_flags_crash"
		else
			run_test "$file" "$test_flags_ref_name"
		fi
	done
}

run_tests_from_file() {
	local file=$1
	local test_flags_ref_name=$2

	run_test "$file" "$test_flags_ref_name"
}

run_tests_from_dir() {
	local dir=$1
	local test_flags_ref_name=$2
	local files="${dir}/*"

	for file in $files ; do
		run_test "$file" "$test_flags_ref_name"
	done
}

run_test() {
	local file=$1
	local -n test_flags_ref=$2
	local test_stdout=${test_flags_ref[stdout]}
	local test_stderr=${test_flags_ref[stderr]}
	local test_exit_code=${test_flags_ref[exit_code]}
	local test_crash=${test_flags_ref[crash]}
	local test_leaks=${test_flags_ref[leaks]}
	local no_env=${test_flags_ref[no_env]}

	if [[ $no_env == "true" ]] ; then
		env="env -i"
	fi
	if  [[ $test_leaks == "true" ]] ; then
		valgrind="$VALGRIND"
	fi
	if [[ $test_stdout == "true" && -z $TESTS_KO_OUT ]] ; then
		TESTS_KO_OUT=0
	fi
	if [[ $test_stderr == "true" && -z $TESTS_KO_ERR ]] ; then
		TESTS_KO_ERR=0
	fi
	if [[ $test_exit_code == "true" && -z $TESTS_KO_EXIT ]] ; then
		TESTS_KO_EXIT=0
	fi
	if [[ $test_crash == "true" && -z $CRASHES ]] ; then
		CRASHES=0
	fi
	if [[ $test_leaks == "true" && -z $LEAKS ]] ; then
		LEAKS=0
	fi

	IFS=''
	i=1
	end_of_file=0
	line_count=0
	dir_name=$(basename "$(dirname "$file")")
	file_name=$(basename --suffix=.sh "$file")
	while [[ $end_of_file == 0 ]] ; do
		# Read the test input
		read -r line
		end_of_file=$?
		((line_count++))
		if [[ $line == "#"* ]] || [[ $line == "" ]] ; then
			if [[ $line == "#"[[:blank:]]*[[:blank:]]"#" ]] ; then
				echo -e "\033[1;33m		$line\033[m" | tr '\t' '    '
			fi
			continue
		else
			printf "\033[1;35m%-4s\033[m" "  $i:	"
			tmp_line_count=$line_count
			failed=0
			while [[ $end_of_file == 0 ]] && [[ $line != "#"* ]] && [[ $line != "" ]] ; do
				input+="$line$NL"
				read -r line
				end_of_file=$?
				((line_count++))
			done

			# Run the test
			if [[ $test_leaks == "true" ]] ; then
				echo -n "$input" | eval "$env $valgrind $MINISHELL_PATH/$EXECUTABLE" &>/dev/null
			fi
			if [[ $test_stdout == "true" || $test_stderr == "true" || $test_exit_code == "true" || $test_crash == "true" ]] ; then
				echo -n "$input" | eval "$env $MINISHELL_PATH/$EXECUTABLE" 2>"$TMP_OUTDIR/tmp_err_minishell" >"$TMP_OUTDIR/tmp_out_minishell"
				exit_minishell=$?
				echo -n "enable -n .$NL$input" | eval "$env $BASH" 2>"$TMP_OUTDIR/tmp_err_bash" >"$TMP_OUTDIR/tmp_out_bash"
				exit_bash=$?
			fi

			# Check stdout
			if [[ $test_stdout == "true" ]] ; then
				echo -ne "\033[1;34mSTD_OUT:\033[m "
				if [[ -n "$MINISHELL_PROMPT" ]] ; then
					if [[ $READLINE == "true" ]] ; then
						# Filter out the prompt line of readline from stdout
						sed -i "/^$MINISHELL_PROMPT/d" "$TMP_OUTDIR/tmp_out_minishell"
					else
						# Filter out the prompt from stdout
						sed -i "s/^$MINISHELL_PROMPT//" "$TMP_OUTDIR/tmp_out_minishell"
					fi
				fi
				if ! diff -q "$TMP_OUTDIR/tmp_out_minishell" "$TMP_OUTDIR/tmp_out_bash" >/dev/null ; then
					echo -ne "❌  " | tr '\n' ' '
					((TESTS_KO_OUT++))
					((failed++))
					mkdir -p "$OUTDIR/$dir_name/$file_name" 2>/dev/null
					mv "$TMP_OUTDIR/tmp_out_minishell" "$OUTDIR/$dir_name/$file_name/${i}_stdout_minishell" 2>/dev/null
					mv "$TMP_OUTDIR/tmp_out_bash" "$OUTDIR/$dir_name/$file_name/${i}_stdout_bash" 2>/dev/null
				else
					echo -ne "✅  "
					((TESTS_OK++))
				fi
			fi

			# Check stderr
			if [[ $test_stderr == "true" ]] ; then
				echo -ne "\033[1;33mSTD_ERR:\033[m "
				if [[ -n "$MINISHELL_EXIT_MSG" ]] ; then
					# Filter out the exit message from stderr
					sed -i "/^$MINISHELL_EXIT_MSG$/d" "$TMP_OUTDIR/tmp_err_minishell"
				fi
				if grep -q '^bash: line [0-9]*:' "$TMP_OUTDIR/tmp_err_bash" ; then
					# Normalize bash stderr by removing the program name and line number prefix
					sed -i 's/^bash: line [0-9]*:/:/' "$TMP_OUTDIR/tmp_err_bash"
					# Normalize minishell stderr by removing its program name prefix
					sed -i "s/^\\($MINISHELL_ERR_NAME: line [0-9]*:\\|$MINISHELL_ERR_NAME:\\)/:/" "$TMP_OUTDIR/tmp_err_minishell"
					# Remove the next line after a specific syntax error message in bash stderr
					sed -i '/^: syntax error near unexpected token/{n; d}' "$TMP_OUTDIR/tmp_err_bash"
				fi
				if ! diff -q "$TMP_OUTDIR/tmp_err_minishell" "$TMP_OUTDIR/tmp_err_bash" >/dev/null ; then
					echo -ne "❌  " | tr '\n' ' '
					((TESTS_KO_ERR++))
					((failed++))
					mkdir -p "$OUTDIR/$dir_name/$file_name" 2>/dev/null
					mv "$TMP_OUTDIR/tmp_err_minishell" "$OUTDIR/$dir_name/$file_name/${i}_stderr_minishell" 2>/dev/null
					mv "$TMP_OUTDIR/tmp_err_bash" "$OUTDIR/$dir_name/$file_name/${i}_stderr_bash" 2>/dev/null
				else
					echo -ne "✅  "
					((TESTS_OK++))
				fi
			fi

			# Check exit code
			if [[ $test_exit_code == "true" ]] ; then
				echo -ne "\033[1;36mEXIT_CODE:\033[m "
				if [[ $exit_minishell != $exit_bash ]] ; then
					echo -ne "❌\033[1;31m [ minishell($exit_minishell) bash($exit_bash) ]\033[m  " | tr '\n' ' '
					((TESTS_KO_EXIT++))
					((failed++))
				else
					echo -ne "✅  "
					((TESTS_OK++))
				fi
			fi

			# Check for crashes
			if [[ $test_crash == "true" ]] ; then
				echo -ne "\033[1;36mCRASH:\033[m "
				case $exit_minishell in
					132) crash_type="SIGILL" ;;
					134) crash_type="SIGABRT" ;;
					136) crash_type="SIGFPE" ;;
					135) crash_type="SIGBUS" ;;
					137) crash_type="SIGKILL" ;;
					139) crash_type="SIGSEGV" ;;
					159) crash_type="SIGSYS" ;;
					*) crash_type="" ;;
				esac
				if [[ -n $crash_type ]] ; then
					echo -ne "❌\033[1;31m [ $crash_type ]\033[m  " | tr '\n' ' '
					((CRASHES++))
					((failed++))
				else
					echo -ne "✅  "
				fi
			fi

			# Check for leaks
			if [[ $test_leaks == "true" ]] ; then
				echo -ne "\033[1;36mLEAKS:\033[m "
				# Get all error summaries
				error_summaries=$(cat "$TMP_OUTDIR/tmp_valgrind_out" | grep -a "ERROR SUMMARY:" | awk '{print $4}')
				IFS=$'\n' read -rd '' -a error_summaries_array <<< "$error_summaries"
				# Check if any error summary is not 0
				leak_found=0
				for error_summary in "${error_summaries_array[@]}" ; do
					if [[ -n "$error_summary" ]] && [[ "$error_summary" -ne 0 ]] ; then
						leak_found=1
						break
					fi
				done
				# Check if there are any open file descriptors not inherited from parent
				open_file_descriptors=$(
					awk '
						# If the line starts with a PID and "Open file descriptor"
						/^==[0-9]+== Open file descriptor/ {
							# Store the PID and the line
							pid=$1
							line=$0

							# Keep reading lines until a line that starts with the same PID gets found
							while (getline && $1 != pid);

							# Check if the line does not contain "<inherited from parent>"
							if ($0 !~ /<inherited from parent>/) {
								print line
							}
						}
					' "$TMP_OUTDIR/tmp_valgrind_out"
				)
				if [[ -n "$open_file_descriptors" ]] ; then
					leak_found=1
				fi
				if [[ "$leak_found" -ne 0 ]] ; then
					echo -ne "❌ "
					((LEAKS++))
					((failed++))
					mkdir -p "$OUTDIR/$dir_name/$file_name" 2>/dev/null
					mv "$TMP_OUTDIR/tmp_valgrind_out" "$OUTDIR/$dir_name/$file_name/${i}_valgrind_out" 2>/dev/null
				else
					echo -ne "✅ "
				fi
			fi

			# Print the file name and line count of the test
			input=""
			((i++))
			((TEST_COUNT++))
			echo -e "\033[0;90m$file:$tmp_line_count\033[m  "
			if [[ $failed -eq 0 ]] ; then
				((TESTS_PASSED++))
			else
				((TESTS_KO += failed))
			fi
		fi
	done < "$file"
	rm -f "$TMP_OUTDIR/tmp_valgrind_out"
	find "$OUTDIR" -type d -empty -delete 2>/dev/null
}

print_stats() {
	local line

	echo "🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁"
	echo -e "🏁                                    \033[1;31mRESULT\033[m                                    🏁"
	echo "🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁🏁"
	line="\033[1;35mTOTAL TEST COUNT: $TEST_COUNT\033[m"
	line+="  \033[1;32mTESTS PASSED: $TESTS_PASSED\033[m"
	if [[ -n $LEAKS ]] ; then
		if [[ $LEAKS == 0 ]] ; then
			line+="  \033[1;32mLEAKING: $LEAKS\033[m"
		else
			line+="  \033[1;31mLEAKING: $LEAKS\033[m"
		fi
	fi
	print_centered "$line"

	line=""
	if [[ -n $TESTS_KO_OUT ]] ; then
		line="\033[1;34mSTD_OUT:\033[m "
		if [[ $TESTS_KO_OUT == 0 ]] ; then
			line+="\033[1;32m✓\033[m"
		else
			line+="\033[1;31m$TESTS_KO_OUT\033[m"
		fi
	fi
	if [[ -n $TESTS_KO_ERR ]] ; then
		line+="  \033[1;33mSTD_ERR:\033[m "
		if [[ $TESTS_KO_ERR == 0 ]] ; then
			line+="\033[1;32m✓\033[m"
		else
			line+="\033[1;31m$TESTS_KO_ERR\033[m"
		fi
	fi
	if [[ -n $TESTS_KO_EXIT ]] ; then
		line+="  \033[1;36mEXIT_CODE:\033[m "
		if [[ $TESTS_KO_EXIT == 0 ]] ; then
			line+="\033[1;32m✓\033[m"
		else
			line+="\033[1;31m$TESTS_KO_EXIT\033[m"
		fi
	fi
	if [[ -n $CRASHES ]] ; then
		if [[ $CRASHES == 0 ]] ; then
			line+="  \033[1;32mCRASHING: $CRASHES\033[m"
		else
			line+="  \033[1;31mCRASHING: $CRASHES\033[m"
		fi
	fi
	print_centered "$line"

	print_centered "\033[1;33mTOTAL FAILED AND PASSED CASES:\033[m"
	echo -e "\033[1;31m                                      ❌ $TESTS_KO \033[m"
	echo -e "\033[1;32m                                      ✅ $TESTS_OK \033[m"
}

update_tester() {
	cd "$RUNDIR" || return 1
	if git rev-parse --is-inside-work-tree >/dev/null 2>&1 ; then
		echo "Checking for updates..."
		git pull 2>/dev/null | head -n 1 | grep "Already up to date." || { echo "Tester updated." && cd - >/dev/null && exec "$0" --no-update "${SCRIPT_ARGS[@]}" ; exit ; }
	fi
	cd - >/dev/null
}

# Prompt the user for confirmation
# Default is 'no', for 'yes' needs y/Y/yes/Yes + Enter key
prompt_with_enter() {
    echo -e "$1 [\e[1my\e[0m/\e[1mN\e[0m]"
    read -rp "> "
    if [[ "$REPLY" =~ ^[Yy]([Ee][Ss])?$ ]]; then
        return 0
    fi
    return 1
}

strip_ansi() {
    echo -ne "${1}" | sed -r "s/(\033|\x1B|\x1b|\e)\[(([0-9]{1,3};)*[0-9]{1,3})?[mGK]//g"
}

print_centered() {
    local text=$1
    local total_length=82
	local pure_text="$(strip_ansi "$text")"
    local text_length=${#pure_text}
    local padding=$(( (total_length - text_length + 1) / 2 ))

    printf "%*s%b\n" $padding "" "$text"
}

cleanup() {
	rm -rf "$TMP_OUTDIR" 2>/dev/null
}

sigint_trap() {
	cleanup
	exit 130
}

# Start the tester
main "$@"
