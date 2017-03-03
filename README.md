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


	>, <, ||, && --> pas de out
