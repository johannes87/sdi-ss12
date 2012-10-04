//
// File:  src/test/main.cc
//
// Description: Testclient
//

#include <l4io.h>

#include <sdi/sdi.h>
#include <sdi/types.h>
#include <sdi/constants.h>

#include <if/iflogging.h>
#include <if/ifnaming.h>
#include <if/ifconsoleserver.h>

#include <sdi/console_attributes.h>


L4_ThreadId_t consoleid = L4_nilthread;
CORBA_Environment env(idl4_default_environment);

char cmdbuf[256];


void print_banner()
{
	console_printf(consoleid, "SDI-Shell 0.1 beta\n\n");
}


void command_loop()
{
	while(1)
	{
		console_printf(consoleid, "shell$ ");
		console_readline(consoleid, cmdbuf, sizeof(cmdbuf)-1);
		console_printf(consoleid, "\nCommand: '%s'\n\n", cmdbuf);
	}
}


int main()
{
	char buf[256];

	CORBA_Environment env(idl4_default_environment);

	L4_ThreadId_t loggerid = L4_nilthread;

	while (L4_IsNilThread(loggerid))
		loggerid = nameserver_lookup("/server/logger");


	/* Print some stuff on the console */
	while (L4_IsNilThread(consoleid))
		consoleid = nameserver_lookup("/server/console");

	L4_ThreadId_t myself = L4_Myself();
	IF_CONSOLESERVER_setactivethread((CORBA_Object)consoleid, 1, &myself, &env);


	print_banner();

	/* And now.... action! */
	command_loop();

	/* Spin forever */
	while (42) ;

	return 0;
}
