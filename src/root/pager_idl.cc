/*****************************************************************
 * Source file : pager.idl
 * Platform    : V4 IA32
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 17/08/2012 20:58
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#include <sdi/sdi.h>
#include <sdi/constants.h>

#include "pager-server.h"

#include "root.h"

/* Interface pager */

IDL4_INLINE void  pager_pagefault_implementation(CORBA_Object  _caller, const L4_Word_t  address, const L4_Word_t  ip, const L4_Word_t  privileges, idl4_fpage_t * page, idl4_server_environment * _env)

{
	pager_pagefault_implementation_real(_caller, address, ip, privileges, page, _env);
  
  return;
}

IDL4_PUBLISH_PAGER_PAGEFAULT(pager_pagefault_implementation);

IDL4_INLINE void  pager_alloc_implementation(CORBA_Object  _caller, const idl4_fpage_t  page, const L4_Word_t  size, idl4_server_environment * _env)

{
  /* implementation of IF_PAGER::alloc */
  
  return;
}

IDL4_PUBLISH_PAGER_ALLOC(pager_alloc_implementation);

IDL4_INLINE void  pager_free_implementation(CORBA_Object  _caller, const idl4_fpage_t  page, idl4_server_environment * _env)

{
  /* implementation of IF_PAGER::free */
  
  return;
}

IDL4_PUBLISH_PAGER_FREE(pager_free_implementation);

void * pager_vtable_10[PAGER_DEFAULT_VTABLE_SIZE] = PAGER_DEFAULT_VTABLE_10;
void * pager_vtable_discard[PAGER_DEFAULT_VTABLE_SIZE] = PAGER_DEFAULT_VTABLE_DISCARD;
void ** pager_itable[16] = { pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_10, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard, pager_vtable_discard };
void * pager_ktable[PAGER_DEFAULT_KTABLE_SIZE] = PAGER_DEFAULT_KTABLE;

char buf[2][1024];

void  pager_server(void)

{
  L4_ThreadId_t  partner;
  L4_MsgTag_t  msgtag;
  idl4_msgbuf_t  msgbuf;
  long  cnt;

  idl4_msgbuf_init(&msgbuf);
  for (cnt = 0;cnt < PAGER_STRBUF_SIZE;cnt++)
    idl4_msgbuf_add_buffer(&msgbuf, &buf[cnt], 1024);

  while (1)
    {
      partner = L4_nilthread;
      msgtag.raw = 0;
      cnt = 0;

      while (1)
        {
          idl4_msgbuf_sync(&msgbuf);

          idl4_reply_and_wait(&partner, &msgtag, &msgbuf, &cnt);

          if (idl4_is_error(&msgtag))
            break;

          if (IDL4_EXPECT_FALSE(idl4_is_kernel_message(msgtag)))
            idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, pager_ktable[idl4_get_kernel_message_id(msgtag) & PAGER_KID_MASK]);
            else idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, pager_itable[idl4_get_interface_id(&msgtag) & PAGER_IID_MASK][idl4_get_function_id(&msgtag) & PAGER_FID_MASK]);
        }
    }
}

void  pager_discard(void)

{
}

