#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include <stdarg.h>
#define BUFFER_SIZE 1024
#define BACKET_SIZE 64

/**
 *struct entry_s - struct that hold key and value
 * of hash table
 *
 *@key: the key used to retrieve values
 *@value: the respective data for the key
 */
typedef struct entry_s
{
	char *key;
	char *value;
} entry_t;

/**
 * enum status_actions_e - actions that will be applied to
 * status state management
 *
 * @UPDATE_STATUS: action to update status code
 * @GET_STATUS: action to retrieve status code
 */
typedef enum status_actions_e
{
	UPDATE_STATUS,
	GET_STATUS
} status_actions_t;

/**
 * struct list_s - node of linkedlist
 *
 * @data: linkedlist content
 * @next: next node
 */
typedef struct list_s
{
	void *data;
	struct list_s *next;
} list_t;

/**
 * enum command_type_e - types of command
 *
 * @BUILTINS: MEANS THAT COMMAND IS BUILTIN
 * @EXTERNAL: MEANS IT's AN EXTERNAL COMMAND
 * @NOT_FOUND: MEANS THAT COMMANS IS NOT FOUND
 */
typedef enum command_type_e
{
	BUILTINS,
	EXTERNAL,
	NOT_FOUND
} command_type_t;
/**
 * struct command_s - struct that holds informations
 * about command
 *
 * @name: name of the command
 * @arguments: command arguments
 * @type: type of the command
 */
typedef struct command_s
{
	char *name;
	char **arguments;
	command_type_t type;
} command_t;
/**
 * struct builtin_s - builtin struct
 * that will contain name of builtins
 * and it respective function to be
 * executed
 *
 * @name: builtin name
 * @function: builtin function
 *
 */
typedef struct builtin_s
{
	char name[30];
	int (*function)(command_t *command);
} builtin_t;

/**
 * enum builtin_actions_e - builtin actions
 *
 * @GET_BUILTIN: action to get builtin function
 * @SET_BUILTIN: action to add new_buitin function
 */
typedef enum builtin_actions_e
{
	GET_BUILTIN,
	SET_BUILTIN
} builtin_actions_t;
/**
 * struct map_s - defines a structure for a hash table
 *
 * @backets: an array of linkedlist where
 * our entry data will be stored
 */
typedef struct map_s
{
	list_t *backets[BACKET_SIZE];
} map_t;

/**
 * enum enviroment_action_e - actions that will be applied to
 * global enviroment
 *
 * @INIT_ENV: TO INITIALIZE ENVIROMENT VARIABLE
 * @SET_ENTRY: TO ADD NEW ENTRY TO ENVIROMENT VARIABLE
 * @GET_VALUE: TO RETRIEVE VALUE FROM ENVIROMENT VARIABLE
 * @GET_KEYS: TO GET ALL KEY THAT STORED INSIDE ENV VARIABLE
 * @CONVERT_INTO_2D: RETURNS 2D ARRAY CONTAINING ALL ENVIRONEMENT
 * VARIBALES (env)
 * @CLEAR_ENV: TO FREE AND CLEAR EVERYTHING INSIDE OF OUR
 * @DELETE_ENTRY: USED TO DELETE ENTRY FROM ENVIROMENT VARIABLE
 * ENV
 */
typedef enum enviroment_action_e
{
	INIT_ENV,
	SET_ENTRY,
	GET_VALUE,
	GET_KEYS,
	DELETE_ENTRY,
	CONVERT_INTO_2D,
	CLEAR_ENV
} enviroment_action_t;

/**
 * enum globals_action_e - actions to be applied to
 * some global states or variables
 *
 * @GET_LINE: action that allows to
 * get line
 * @GET_LINE_NUMBER: action that allows to get
 * current line number
 * @GET_SHELL_NAME: action that allows us to
 * get shell name
 * @SET_LINE: action that allow us to the line
 * @SET_SHELL_NAME: action allow us to set
 * shell name
 * @INCREMENT_LINE_NUMBER: action to increment
 * line number by one
 * @SET_2D: action that set 2d array
 * @GET_2D: action that get 2d array
 */
typedef enum globals_action_e
{
	GET_LINE,
	GET_LINE_NUMBER,
	GET_SHELL_NAME,
	SET_LINE,
	SET_SHELL_NAME,
	INCREMENT_LINE_NUMBER,
	SET_2D,
	GET_2D
} globals_action_t;

typedef int (*builtins_t)(command_t *);

char *_copy(char *dest, const char *src, size_t size);
void *_realloc(void *old_buffer, size_t old_size, size_t new_size);
ssize_t myGetline(char **line);
char *trimspace(const char *line);
int _parsing_error_handler(char *line);
size_t _strlen(const char *s);
void _free_split(char ***backets);
char **_split(const char *line, const char *diameter);
list_t *addTolist(list_t **lst, void *data);
void *pop_from_list(list_t **list);
size_t _listlen(const list_t *list);
void free_list(list_t *list, void (*free_content)(void *data));
int _strcmp(const char *str1, const char *str2);
char *_strdup(const char *str);
int hachcode(const char *key);
map_t *initMp(void);
int valueSet(map_t *map, const char *key, const char *value);
char *_get_value(const map_t *map, const char *key);
void _clear_entry(void *data);
void clearMp(map_t *map);
list_t *keyGetGen(const map_t *map);
int deleteEntry(map_t *map, const char *key);
command_t *_inigf(char **tokens);
void freeCmd(void *data);
command_t *handlcmd(const char *line);
int semichr(const char *line);
list_t *_pipe_handler(const char *line);
int _handle_pipe_execution(list_t *pipes, int previous_stdin);
int statusmt(status_actions_t action, int new_status);
void _handle_sigint(int sig);
void *envimat(enviroment_action_t action,
							 const char *key, const char *value);
int statusmt(status_actions_t action, int new_status);
char **convert2darry(void);
void feedEnv(char **new_env);
char *pathFromCmd(char *command);
char *stlinstttt(const char *line, int start, int end);
char *_strcat(const char *str1, const char *str2);
char *_itoa(int number);
char *varEnvm(char *env_key);
char **_trim_2darray(char **arr);
int _env(command_t *command);
int _isdigit(const char *s);
int _str2dlen(char **arr2d);
int _atoi(const char *str);
int __exit(command_t *command);
builtins_t bMt(builtin_actions_t action, char *name,
							   int (*function)(command_t *command));
void _excute(command_t *command);
int _setenv(command_t *command);
int _unsetenv(command_t *command);
int _fprint(int fd, const char *format, ...);
void *globalStatus(globals_action_t action, char **s);
int _cd(command_t *command);
void _handle_sigint(int sig);
void pmt(void);
int positionGet(const char *line);
char *exclct(const char *line);
#endif
