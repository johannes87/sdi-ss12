/*****************************************************************
 * Source file : memoryserver.idl
 * Platform    : V4 IA32
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 20/09/2012 15:16
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#include "memoryserver.h"
#include <l4io.h>

//#include <sdi/sdi.h>
#include <sdi/constants.h>

#include <if/iflogging.h>


L4_ThreadId_t loggerid;
L4_ThreadId_t sigma0id;
L4_ThreadId_t fileserverid;
CORBA_Environment env (idl4_default_environment);
char logbuf[80];

int main(void)
{
    while (L4_IsNilThread(loggerid)){
        loggerid = nameserver_lookup("/server/logger");
    }

    log_printf(loggerid, "[MEMORY] Registering");

    nameserver_register("/server/memory");

    log_printf(loggerid, "[MEMORY] Registered...");

    //initialize data
    Taskheader_index = 0;
    sigma0id = L4_GlobalId(48, 1); // TODO: hard coded for now

    log_printf(loggerid, "[MEMORY] sigma0id = %x", sigma0id);

    while (L4_IsNilThread(fileserverid)){
        fileserverid = nameserver_lookup("/file");
    }

    memoryserver_server();	
}
