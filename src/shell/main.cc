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



void animation_loop()
{
	int x = 1;
	char buf[30];

	/** Print logo */
	while(1)
	{
		snprintf(buf, sizeof(buf), "Line %i\n", x);
		x++;

		IF_CONSOLESERVER_putstring((CORBA_Object)consoleid, buf, SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE, &env);
		sleep(1000);
	}
}


int main()
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

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


	/* And now.... action! */
	animation_loop();

	/* Spin forever */
	while (42) ;

	return 0;
}
