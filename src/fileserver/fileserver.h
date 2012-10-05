#ifndef _FILESERVER_H_
#define _FILESERVER_H_

#include <sdi/types.h>
#include <l4/bootinfo.h>

extern L4_ThreadId_t loggerid;
extern L4_BootInfo_t* bootinfo;


/*****************************************************************
 * Source file : fileserver.idl
 * Platform    : V4 IA32
 * Mapping     : CORBA C
 *
 * Generated by IDL4 1.1.0 (roadrunner) on 23/08/2012 14:16
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/



/* Interface fileserver */

extern L4_ThreadId_t  fileserver_Lookup_impl(CORBA_Object  _caller, const path_t  path, path_t * remaining, idl4_server_environment * _env);

extern L4_Word_t  fileserver_get_file_id_impl(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env);

extern L4_Word_t  fileserver_read_impl(CORBA_Object  _caller, const L4_Word_t  file_id, const L4_Word_t  offset, const L4_Word_t  count, buf_t * buf, idl4_server_environment * _env);

extern L4_Word_t  fileserver_write_impl(CORBA_Object  _caller, const L4_Word_t  file_id, const L4_Word_t  offset, const L4_Word_t  count, const buf_t * buf, idl4_server_environment * _env);

extern L4_Word_t  fileserver_get_file_size_impl(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env);

extern L4_Word_t  fileserver_get_file_type_impl(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env);

extern CORBA_boolean  fileserver_remove_impl(CORBA_Object  _caller, const L4_Word_t  file_id, idl4_server_environment * _env);

extern CORBA_boolean  fileserver_mkdir_impl(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env);

extern CORBA_boolean  fileserver_rmdir_impl(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env);

extern L4_Word_t  fileserver_get_dir_size_impl(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env);

extern CORBA_boolean fileserver_get_dir_entry_impl(CORBA_Object  _caller, const path_t  path, const L4_Word_t  entry, buf_t * buf, idl4_server_environment * _env);


void  fileserver_server(void);

void  fileserver_discard(void);

#endif
