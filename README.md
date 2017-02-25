# 42sh

test sous-shell& accolade

 .() := sous-shell
	. n'applieque pqs les changements au shell
	. child scope

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
