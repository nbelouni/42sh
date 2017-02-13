# 42sh

test sous-shell& accolade

 .() := sous-shell
	. n'applieque pqs les changements au shell
	. child scope

 .{} := accolade
 	.applique les changements au shell
	.current scope (pas de fork);

 .&& .|| := et - ou
 	.() -> check la derniere sortie d'execution si ;
	.{} -> check la derniere sortie d'execution si ;

 .`` := basktickquote
	.cmd1 `cmd2` -> cmd1 -> arg(resul cmd2)
