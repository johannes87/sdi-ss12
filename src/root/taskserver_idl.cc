/*****************************************************************
 * Source file : taskserver.idl
 * Platform    : V4 IA32
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 20/09/2012 13:13
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#include <sdi/sdi.h>

#include "taskserver-server.h"
#include "taskserver.h"

#include "root.h"

char buf_msg[TASKSERVER_STRBUF_SIZE][512];

/* Interface taskserver */

IDL4_INLINE L4_ThreadId_t  taskserver_create_task_implementation(CORBA_Object  _caller, const path_t  path, const path_t  cmdline, idl4_server_environment * _env)

{
  return taskserver_create_task_real(_caller, path, cmdline, _env);
}

IDL4_PUBLISH_TASKSERVER_CREATE_TASK(taskserver_create_task_implementation);

IDL4_INLINE L4_ThreadId_t  taskserver_create_thread_implementation(CORBA_Object  _caller, const L4_Word_t  ip, const L4_Word_t  sp, idl4_server_environment * _env)

{
  return taskserver_create_thread_real(_caller, ip, sp, _env);
}

IDL4_PUBLISH_TASKSERVER_CREATE_THREAD(taskserver_create_thread_implementation);

IDL4_INLINE void  taskserver_kill_task_implementation(CORBA_Object  _caller, const L4_ThreadId_t * task_id, idl4_server_environment * _env)

{
  /* implementation of IF_TASKSERVER::kill_task */
  
  return;
}

IDL4_PUBLISH_TASKSERVER_KILL_TASK(taskserver_kill_task_implementation);

IDL4_INLINE void  taskserver_kill_thread_implementation(CORBA_Object  _caller, const L4_ThreadId_t * thread_id, idl4_server_environment * _env)

{
  /* implementation of IF_TASKSERVER::kill_thread */
  
  return;
}

IDL4_PUBLISH_TASKSERVER_KILL_THREAD(taskserver_kill_thread_implementation);

IDL4_INLINE void  taskserver_set_priority_implementation(CORBA_Object  _caller, const L4_ThreadId_t * thread_id, const L4_Word_t  prio, idl4_server_environment * _env)

{
  /* implementation of IF_TASKSERVER::set_priority */
  
  return;
}

IDL4_PUBLISH_TASKSERVER_SET_PRIORITY(taskserver_set_priority_implementation);

IDL4_INLINE void  taskserver_destroyed_implementation(CORBA_Object  _caller, const L4_ThreadId_t * thread_id, idl4_server_environment * _env)

{
  /* implementation of IF_TASKSERVER::destroyed */
  
  return;
}

IDL4_PUBLISH_TASKSERVER_DESTROYED(taskserver_destroyed_implementation);

IDL4_INLINE void  taskserver_attach_interrupt_implementation(CORBA_Object  _caller, const L4_Word_t  int_num, idl4_server_environment * _env)

{
	if(!L4_AssociateInterrupt(L4_GlobalId(int_num, 1), _caller))
		IF_LOGGING_LogMessage((CORBA_Object)loggerid, "[TASK] AssociateInterrupt failed", &env);
}

IDL4_PUBLISH_TASKSERVER_ATTACH_INTERRUPT(taskserver_attach_interrupt_implementation);

IDL4_INLINE L4_ThreadId_t  taskserver_Lookup_implementation(CORBA_Object  _caller, const path_t  path, path_t * remaining, idl4_server_environment * _env)

{
  L4_ThreadId_t  __retval = { local: { X: { 0, 0 } } };

  /* implementation of IF_NAMING::Lookup */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_LOOKUP(taskserver_Lookup_implementation);

IDL4_INLINE L4_Word_t  taskserver_get_file_id_implementation(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env)

{
  L4_Word_t  __retval = 0;

  /* implementation of IF_FILE::get_file_id */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_GET_FILE_ID(taskserver_get_file_id_implementation);

IDL4_INLINE L4_Word_t  taskserver_read_implementation(CORBA_Object  _caller, const L4_Word_t  file_id, const L4_Word_t  offset, const L4_Word_t  count, buf_t * buf, idl4_server_environment * _env)

{
  L4_Word_t  __retval = 0;

  /* implementation of IF_FILE::read */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_READ(taskserver_read_implementation);

IDL4_INLINE L4_Word_t  taskserver_write_implementation(CORBA_Object  _caller, const L4_Word_t  file_id, const L4_Word_t  offset, const L4_Word_t  count, const buf_t * buf, idl4_server_environment * _env)

{
  L4_Word_t  __retval = 0;

  /* implementation of IF_FILE::write */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_WRITE(taskserver_write_implementation);

IDL4_INLINE L4_Word_t  taskserver_get_file_size_implementation(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env)

{
  L4_Word_t  __retval = 0;

  /* implementation of IF_FILE::get_file_size */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_GET_FILE_SIZE(taskserver_get_file_size_implementation);

IDL4_INLINE L4_Word_t  taskserver_get_file_type_implementation(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env)

{
  L4_Word_t  __retval = 0;

  /* implementation of IF_FILE::get_file_type */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_GET_FILE_TYPE(taskserver_get_file_type_implementation);

IDL4_INLINE CORBA_boolean  taskserver_remove_implementation(CORBA_Object  _caller, const L4_Word_t  file_id, idl4_server_environment * _env)

{
  CORBA_boolean  __retval = 0;

  /* implementation of IF_FILE::remove */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_REMOVE(taskserver_remove_implementation);

IDL4_INLINE CORBA_boolean  taskserver_mkdir_implementation(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env)

{
  CORBA_boolean  __retval = 0;

  /* implementation of IF_FILE::mkdir */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_MKDIR(taskserver_mkdir_implementation);

IDL4_INLINE CORBA_boolean  taskserver_rmdir_implementation(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env)

{
  CORBA_boolean  __retval = 0;

  /* implementation of IF_FILE::rmdir */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_RMDIR(taskserver_rmdir_implementation);

IDL4_INLINE L4_Word_t  taskserver_get_dir_size_implementation(CORBA_Object  _caller, const path_t  path, idl4_server_environment * _env)

{
  L4_Word_t  __retval = 0;

  /* implementation of IF_FILE::get_dir_size */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_GET_DIR_SIZE(taskserver_get_dir_size_implementation);

IDL4_INLINE CORBA_boolean  taskserver_get_dir_entry_implementation(CORBA_Object  _caller, const path_t  path, const L4_Word_t  entry, buf_t * buf, idl4_server_environment * _env)

{
  CORBA_boolean  __retval = 0;

  /* implementation of IF_FILE::get_dir_entry */
  
  return __retval;
}

IDL4_PUBLISH_TASKSERVER_GET_DIR_ENTRY(taskserver_get_dir_entry_implementation);

void * taskserver_vtable_4[TASKSERVER_DEFAULT_VTABLE_SIZE] = TASKSERVER_DEFAULT_VTABLE_4;
void * taskserver_vtable_6[TASKSERVER_DEFAULT_VTABLE_SIZE] = TASKSERVER_DEFAULT_VTABLE_6;
void * taskserver_vtable_11[TASKSERVER_DEFAULT_VTABLE_SIZE] = TASKSERVER_DEFAULT_VTABLE_11;
void * taskserver_vtable_discard[TASKSERVER_DEFAULT_VTABLE_SIZE] = TASKSERVER_DEFAULT_VTABLE_DISCARD;
void ** taskserver_itable[16] = { taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_4, taskserver_vtable_discard, taskserver_vtable_6, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_11, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_discard, taskserver_vtable_discard };

void  taskserver_server(void)

{
  taskserver_init();    

  L4_ThreadId_t  partner;
  L4_MsgTag_t  msgtag;
  idl4_msgbuf_t  msgbuf;
  long  cnt;

  idl4_msgbuf_init(&msgbuf);
  for (cnt = 0;cnt < TASKSERVER_STRBUF_SIZE;cnt++)
    idl4_msgbuf_add_buffer(&msgbuf, buf_msg[cnt], 512);

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

          idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, taskserver_itable[idl4_get_interface_id(&msgtag) & TASKSERVER_IID_MASK][idl4_get_function_id(&msgtag) & TASKSERVER_FID_MASK]);
        }
    }
}

void  taskserver_discard(void)

{
}

