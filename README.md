# 42sh




| PARTIE | STATUE | BUG report |
| ------ | ------ | ---------- |
| ED Line | DONE |     | 
| PLexer | DONE |  |
| globbing | en cours | |
| exec | en cours  | |
| builtins | en cours | |









test sous-shell& accolade

 .() := sous-shell
	. n'applique pas les changements au shell
	. child scope (env)

 .{} := accolade
 	.applique les changements au shell
	.current scope (pas de fork);
	{cmd;} -> erreur parse ne check ni avant ni apres
	{cmd} -> envoie la commande avec accolade
	{esp -> tok ouvrant
	;} -> tok fermant
	si {esp sans ;} no tokken

 .&& .|| := et - ou
 	.() -> check la derniere sortie d'execution si ;
	.{} -> check la derniere sortie d'execution si ;

 .`` := basktickquote
	.cmd1 `cmd2` -> cmd1 -> arg(resul cmd2)

	. lexer_parser.h

 .in & out
	.in + << + eof --> stdout: Bad file descriptor;

	>  >> -> in, no out;
	<  << -> (no in ?), no out, (in a voir)
	&& || | -> no in no out
	>& <& -> in, out

bash-3.2$ ls 2147483648>la
bash: file descriptor out of range: Bad file descriptor
bash-3.2$ ls 2147483647>la
bash: 2147483647: Bad file descriptor


	cmd'cmd'cdm |cmd<>
	cmd'cmd' cmd
	'cmd'cmd cmd
	'cmd'cmd|
	'cmd' cmd

	$(cmd)|cmd -> no


	>, <, ||, && --> pas de out
  // opts -> chaine d'options dans define
  // args -> arguments au builtins (options incluses)
  // au retour, opt[0] contient soit le code d'erreur, soit la position dans args
  // de la fin des options.
  //int *ft_opt_parse(char *opts, char **args, size_t overwrite)
  #define UNSET_OPT "iu" -> opt{pos/code erreur, 1/0, 1/0}
   exemple opt[1] -> 1

	TOKEN A FAIRE
	<> -> == < a voir
	<& && >& sont differents a changer a checker

--->>> Penser a aller chercher la liste d'arguments dans t_list *argv
		a la place de char **cmd

typedef struct		s_tree
{
	int				token;
	char			**cmd;
	t_list			*argv;
	t_token			*token_or;
	struct s_tree	*father;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;
