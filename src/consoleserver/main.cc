/*****************************************************************
 * Source file : consoleserver.idl
 * Platform    : V4 IA32
 * Mapping     : CORBA C
 * 
 * Generated by IDL4 1.1.0 (roadrunner) on 15/07/2012 18:21
 * Report bugs to haeberlen@ira.uka.de
 *****************************************************************/

#include <sdi/sdi.h>
#include <sdi/constants.h>
#include "consoleserver-server.h"

#include <l4io.h>

#include <if/iflogging.h>
#include <if/ifkeyboarddriver.h>

typedef struct {
        char x;
        char y;
} cursor_t;

struct glyph_t {
        char character;
        char attribute;
} __packed;

/** Backbuffer */
glyph_t backbuffer[SDI_CONSOLESERVER_NUM_CONSOLES][80 * 25];

/** Cursors */
cursor_t cursors[SDI_CONSOLESERVER_NUM_CONSOLES] = {0, 0};

/** Thread mapping */
L4_ThreadId_t active_threads[SDI_CONSOLESERVER_NUM_CONSOLES];

/** Video memory */
static glyph_t *vidmem = (glyph_t *)0xb8000;

/** Currently active console */
int active_console = 0;

L4_ThreadId_t keyboarddriverid = L4_nilthread;


L4_ThreadId_t loggerid = L4_nilthread;
CORBA_Environment env(idl4_default_environment);


/**
 Find the console for a given thread
*/
int find_console_for_thread(L4_ThreadId_t threadid)
{
	for(int i = 0; i < SDI_CONSOLESERVER_NUM_CONSOLES; i++)
		if(active_threads[i] == threadid)
			return i;

	return -1;
}

void blit_backbuffer(int num)
{
        memcpy(vidmem, backbuffer[num], 80 * 25 * sizeof(glyph_t));
}

void putcharat(int consolenum, int x, int y, char character, char attribute)
{
	if(x < 80 && y < 25)
	{
		int index = y * 80 + x;

	        backbuffer[consolenum][index].character = character;
        	backbuffer[consolenum][index].attribute = attribute;

		if(consolenum == active_console)
		{
	        	(vidmem + index)->character = character;
	        	(vidmem + index)->attribute = attribute;
		}
	}
}


void putchar(int consolenum, char character, char attribute)
{
	if(consolenum < 0 || consolenum >= SDI_CONSOLESERVER_NUM_CONSOLES)
		return;

	putcharat(consolenum, cursors[consolenum].x, cursors[consolenum].y, character, attribute);

	cursors[consolenum].x++;

	/** Line wrap */
	if(cursors[consolenum].x >= 80)
	{
		cursors[consolenum].x = 0;
		cursors[consolenum].y++;

		/** Scroll */
		if(cursors[consolenum].y >= 25)
		{
			cursors[consolenum].y = 24;

			for(int i = 0; i < (80 * 24); i++)
			{
				        backbuffer[consolenum][i] = backbuffer[consolenum][i + 80];
			}

			if(consolenum == active_console)
				blit_backbuffer(active_console);
		}
	}
}

IDL4_INLINE void  consoleserver_putchar_implementation(CORBA_Object  _caller, const CORBA_char  character, const CORBA_char  attribute, idl4_server_environment * _env)

{
    /** Find matching console */
    int console = find_console_for_thread(_caller);

    if(console != -1)
	putchar(console, character, attribute);

    return;
}

IDL4_PUBLISH_CONSOLESERVER_PUTCHAR(consoleserver_putchar_implementation);

IDL4_INLINE void  consoleserver_putcharat_implementation(CORBA_Object  _caller, const CORBA_long  x, const CORBA_long  y, const CORBA_char  character, const CORBA_char  attribute, idl4_server_environment * _env)

{
    /** Find matching console */
    int console = find_console_for_thread(_caller);

    if(console != -1)
	putcharat(console, x,y, character, attribute);

    return;
  /* implementation of IF_CONSOLESERVER::putcharat */

  return;
}

IDL4_PUBLISH_CONSOLESERVER_PUTCHARAT(consoleserver_putcharat_implementation);

IDL4_INLINE void  consoleserver_putstring_implementation(CORBA_Object  _caller, const consolestring_t  text, const CORBA_char  attribute, idl4_server_environment * _env)

{
    /** Find matching console */
	int console = find_console_for_thread(_caller);

	if(console != -1)
	{
		for(int i = 0; i < strlen(text); i++)
			putchar(console, text[i], attribute);
	}
}

IDL4_PUBLISH_CONSOLESERVER_PUTSTRING(consoleserver_putstring_implementation);

IDL4_INLINE void  consoleserver_putstringat_implementation(CORBA_Object  _caller, const CORBA_long  x, const CORBA_long  y, const consolestring_t  text, const CORBA_char  attribute, idl4_server_environment * _env)

{
    /** Find matching console */
	int console = find_console_for_thread(_caller);

	if(console != -1)
	{
		for(int i = 0; i < strlen(text); i++)
			putcharat(console, x + i, y, text[i], attribute);
	}

	return;
}

IDL4_PUBLISH_CONSOLESERVER_PUTSTRINGAT(consoleserver_putstringat_implementation);

IDL4_INLINE void  consoleserver_setactivethread_implementation(CORBA_Object  _caller, const CORBA_long  console, const L4_ThreadId_t * thread, idl4_server_environment * _env)

{
	if(console <0 || console >= SDI_CONSOLESERVER_NUM_CONSOLES)
		return;

	active_threads[console] = *thread;

  return;
}

IDL4_PUBLISH_CONSOLESERVER_SETACTIVETHREAD(consoleserver_setactivethread_implementation);

IDL4_INLINE CORBA_long  consoleserver_getconsolenum_implementation(CORBA_Object  _caller, idl4_server_environment * _env)

{
  CORBA_long  __retval = 0;

  /* implementation of IF_CONSOLESERVER::getconsolenum */

  return __retval;
}

IDL4_PUBLISH_CONSOLESERVER_GETCONSOLENUM(consoleserver_getconsolenum_implementation);

IDL4_INLINE CORBA_char  consoleserver_getchar_implementation(CORBA_Object  _caller, idl4_server_environment * _env)

{
  CORBA_char  __retval = 0;

  /* implementation of IF_CONSOLESERVER::getchar */

  return __retval;
}

IDL4_PUBLISH_CONSOLESERVER_GETCHAR(consoleserver_getchar_implementation);

void * consoleserver_vtable[CONSOLESERVER_DEFAULT_VTABLE_SIZE] = CONSOLESERVER_DEFAULT_VTABLE;

void  consoleserver_server(void)

{
  L4_ThreadId_t  partner;
  L4_MsgTag_t  msgtag;
  idl4_msgbuf_t  msgbuf;
  long  cnt;

  idl4_msgbuf_init(&msgbuf);
  for (cnt = 0;cnt < CONSOLESERVER_STRBUF_SIZE;cnt++)
    idl4_msgbuf_add_buffer(&msgbuf, malloc(16000), 16000);

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

          idl4_process_request(&partner, &msgtag, &msgbuf, &cnt, consoleserver_vtable[idl4_get_function_id(&msgtag) & CONSOLESERVER_FID_MASK]);
        }
    }
}

void  consoleserver_discard(void)

{
}




/**
 Blank all consoles
*/
void init_consoles()
{
        for(int i = 0; i < SDI_CONSOLESERVER_NUM_CONSOLES;i++)
        {
                // Blank the screen and set attribute to bright white
                for(int j = 0; j < 2000; j++)
                {
                        backbuffer[i][j].character = ' ';
                        backbuffer[i][j].attribute = 0xf;
                }

                // Reset the cursor
                cursors[i].x = 0;
                cursors[i].y = 0;

		/** Reset thread mappings */
		active_threads[i] = L4_nilthread;
        }
}


void set_active_console(int num)
{
        if(num < SDI_CONSOLESERVER_NUM_CONSOLES)
        {
                active_console = num;

                blit_backbuffer(num);
        }
}


int main(void)
{
	while (L4_IsNilThread(loggerid))
        	loggerid = nameserver_lookup("/server/logger");

	/* Register myself with the nameserver */
	nameserver_register("/server/console");
	IF_LOGGING_LogMessage((CORBA_Object)loggerid, "[CONSOLESERVER] Registered", &env);

	/* Get keyboard driver */
//	while(L4_IsNilThread(keyboarddriverid))
//		keyboarddriverid = nameserver_lookup("/driver/keyboard");

//	IF_LOGGING_LogMessage((CORBA_Object)loggerid, "[CONSOLESERVER] Got keyboard", &env);

        init_consoles();
        set_active_console(0);

	consoleserver_server();
}

