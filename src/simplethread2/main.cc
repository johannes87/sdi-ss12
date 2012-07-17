//
// File:  src/test/main.cc
//
// Description: Testclient
//

#include <l4/thread.h>
#include <l4/space.h>
#include <l4/message.h>
#include <l4/ipc.h>
#include <l4/sigma0.h>
#include <l4/bootinfo.h>
#include <l4/kdebug.h>

#include <l4io.h>
#include <macros.h>

#include <stdlib.h>

#include <sdi/types.h>
#include <sdi/sdi.h>

#include <idl4glue.h>

#include <sdi/constants.h>

#include <if/iflogging.h>
#include <if/ifnaming.h>
#include <if/ifconsoleserver.h>

#include <nameserver.h>

#include <sdi/console_attributes.h>
#include <sdi/io.h>


static const int KBD_DATA_REG = 0x60;
static const int KBD_STATUS_REG = 0x64;



L4_ThreadId_t consoleid = L4_nilthread;
CORBA_Environment env(idl4_default_environment);


int main()
{
	L4_Msg_t msg;
	L4_MsgTag_t tag;

	char buf[257];

	int scancode;
	int scanstatus;

	printf("a");

	CORBA_Environment env(idl4_default_environment);

	L4_ThreadId_t loggerid = L4_nilthread;

	while (L4_IsNilThread(loggerid))
		loggerid = nameserver_lookup("/server/logger");

	IF_LOGGING_LogMessage((CORBA_Object)loggerid, "[SIMPLETHREAD2] Active", &env);


	/* Spin forever */
	while (42) ;

	return 0;
}
