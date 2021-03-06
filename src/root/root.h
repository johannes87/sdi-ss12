//
// File:  src/root/root.h
//
// Description: Header for root task
//

#include <l4/kdebug.h>

#include <l4io.h>

#include <macros.h>
#include <sdi/types.h>


/* ======== Thread IDs =========== */

extern L4_ThreadId_t sigma0id;   // sigma0, just in case
extern L4_ThreadId_t pagerid;    // our internal pager
extern L4_ThreadId_t minipagerid;   // minipager


extern void logger_server (void);
extern void minipager_server (void);
extern void taskserver_server (void);

extern void  pager_pagefault_implementation_real(CORBA_Object  _caller, const L4_Word_t  address, const L4_Word_t  ip, const L4_Word_t  privileges, idl4_fpage_t * page, idl4_server_environment * _env);
