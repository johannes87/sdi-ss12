/*****************************************************************
* Source file : ../../if/ifnameserver.idl
* Platform    : V4 Generic
* Mapping     : CORBA C
*
* Generated by IDL4 1.1.0 (roadrunner) on 10/07/2012 19:02
* Report bugs to haeberlen@ira.uka.de
*****************************************************************/

#include <idl4glue.h>
#include "nameserver-server.h"
#include <l4/types.h>
#include <l4io.h>
#include <sdi/sdi.h>
#include <sdi/constants.h>
#include <stdlib.h>

#include <if/iflogging.h>

/* Interface IF_NAMESERVER */

typedef struct {
	char path[SDI_NAMESERVER_MAX_ENTRY_LEN + 1];
	L4_ThreadId_t registrant;
} name_entry_t;

name_entry_t names[SDI_NAMESERVER_MAX_ENTRIES];

L4_ThreadId_t loggerid;
CORBA_Environment env(idl4_default_environment);


/**
   Find the next free name database entry

   @return index on success, -1 if database full
 */
int find_free_entry()
{
	for (int i = 0; i < SDI_NAMESERVER_MAX_ENTRIES; i++)
		if (names[i].registrant == L4_nilthread)
			return i;

	return -1;
}

IDL4_INLINE void  IF_NAMESERVER_register_implementation(CORBA_Object _caller, const path_t path, idl4_server_environment * _env)

{
	int i = find_free_entry();

	if (i >= 0) {
		strncpy(names[i].path, path, SDI_NAMESERVER_MAX_ENTRY_LEN);
		names[i].registrant = _caller;
	}else
		printf("[NAMESERVER] Error: Could not register thread %lx for path \"%s\", database full\n", _caller.raw, path);

	return;
}

IDL4_PUBLISH_IF_NAMESERVER_REGISTER(IF_NAMESERVER_register_implementation);

IDL4_INLINE void  IF_NAMESERVER_deregister_implementation(CORBA_Object _caller, idl4_server_environment * _env)

{
	/* Remove all entries for the caller thread */
	for (int i = 0; i < SDI_NAMESERVER_MAX_ENTRIES; i++)
		if (names[i].registrant == _caller) {
			names[i].registrant = L4_nilthread;
			names[i].path[0] = '\0';
		}

	return;
}

IDL4_PUBLISH_IF_NAMESERVER_DEREGISTER(IF_NAMESERVER_deregister_implementation);

IDL4_INLINE L4_ThreadId_t  IF_NAMESERVER_Lookup_implementation(CORBA_Object _caller, const path_t path, path_t * remaining, idl4_server_environment * _env)

{
	/* Is someone looking for me? */
	if(strlen(path) == 0 || (strlen(path) == 1 && path[0] == '/'))
	{
		*remaining = '\0';
		return L4_Myself();
	}

	/* Find the first database entry matching the query */
	for (int i = 0; i < SDI_NAMESERVER_MAX_ENTRIES; i++)
		if (strncmp(path, names[i].path, strlen(names[i].path)) == 0) {
			strcpy(*remaining, &path[strlen(names[i].path)]);
			return names[i].registrant;
		}

	strcpy(*remaining, path);

	return L4_nilthread;

}

IDL4_PUBLISH_IF_NAMESERVER_LOOKUP(IF_NAMESERVER_Lookup_implementation);

void * IF_NAMESERVER_vtable_4[IF_NAMESERVER_DEFAULT_VTABLE_SIZE] = IF_NAMESERVER_DEFAULT_VTABLE_4;
void * IF_NAMESERVER_vtable_5[IF_NAMESERVER_DEFAULT_VTABLE_SIZE] = IF_NAMESERVER_DEFAULT_VTABLE_5;
void * IF_NAMESERVER_vtable_discard[IF_NAMESERVER_DEFAULT_VTABLE_SIZE] = IF_NAMESERVER_DEFAULT_VTABLE_DISCARD;
void ** IF_NAMESERVER_itable[8] = { IF_NAMESERVER_vtable_discard, IF_NAMESERVER_vtable_discard, IF_NAMESERVER_vtable_discard, IF_NAMESERVER_vtable_discard, IF_NAMESERVER_vtable_4, IF_NAMESERVER_vtable_5, IF_NAMESERVER_vtable_discard, IF_NAMESERVER_vtable_discard };

void  IF_NAMESERVER_server()

{
	L4_ThreadId_t partner;
	L4_MsgTag_t msgtag;
	idl4_msgbuf_t msgbuf;
	long cnt;

	idl4_msgbuf_init(&msgbuf);
	for (cnt = 0; cnt < IF_NAMESERVER_STRBUF_SIZE; cnt++)
		idl4_msgbuf_add_buffer(&msgbuf, malloc(16000), 16000);

	while (1) {
		partner = L4_nilthread;
		msgtag.raw = 0;
		cnt = 0;

		while (1) {
			idl4_msgbuf_sync(&msgbuf);

			idl4_reply_and_wait(&partner, &msgtag, &msgbuf, &cnt);

			if (idl4_is_error(&msgtag))
				break;

			idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, IF_NAMESERVER_itable[idl4_get_interface_id(&msgtag) & IF_NAMESERVER_IID_MASK][idl4_get_function_id(&msgtag) & IF_NAMESERVER_FID_MASK]);
		}
	}
}

void  IF_NAMESERVER_discard()

{
}

void clear_name_database()
{
	for (int i = 0; i < SDI_NAMESERVER_MAX_ENTRIES; i++) {
		names[i].path[0] = '\0';
		names[i].registrant = L4_nilthread;
	}
}


int main(void)
{
	clear_name_database();

	IF_NAMESERVER_server();
}

