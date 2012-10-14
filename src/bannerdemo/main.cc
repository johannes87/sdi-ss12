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
#include <if/iftaskserver.h>

#include <sdi/console_attributes.h>


L4_ThreadId_t loggerid = L4_nilthread;
L4_ThreadId_t consoleid = L4_nilthread;
L4_ThreadId_t taskserverid = L4_nilthread;
CORBA_Environment env(idl4_default_environment);


void print_charat(int x, int y, char character, char attrib)
{
    IF_CONSOLESERVER_putcharat((CORBA_Object)consoleid, x, y, character, attrib, &env); 
}


void print_stringat(int x, int y, char* text, char attrib)
{
    IF_CONSOLESERVER_putstringat((CORBA_Object)consoleid, x, y, text, attrib, &env); 
}


void blank_line(int y)
{
    print_stringat(0, y, (char*)"                                                                                ", SDI_CONSOLE_ATTRIBUTE_FGBLACK | SDI_CONSOLE_ATTRIBUTE_BGBLACK);
}


void clear_screen()
{
    for(int y = 0; y < 25; y++)
        blank_line(y);
}


void thread_loop() {
    while(42) {
        sleep(5000);

        if( loggerid != L4_nilthread) {
            log_printf(loggerid, "Thread is running...");
        }
    }
}


void animation_loop()
{
    int x = 85;
    const char* banner = "Karlsruhe Institute of Technology";
    char buf[30];

    sleep(300);

    clear_screen();

    // Get console number
    L4_Word_t console = IF_CONSOLESERVER_getconsolenum((CORBA_Object)consoleid, &env);

    /** Print logo */
    print_stringat(23, 3, (char*)" ____  ____ ___       ___  ____  ", SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE | SDI_CONSOLE_ATTRIBUTE_BGBLUE);
    print_stringat(23, 4, (char*)"/ ___||  _ \\_ _|     / _ \\/ ___| ", SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE | SDI_CONSOLE_ATTRIBUTE_BGBLUE);
    print_stringat(23, 5, (char*)"\\___ \\| | | | |_____| | | \\___ \\ ", SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE | SDI_CONSOLE_ATTRIBUTE_BGBLUE);
    print_stringat(23, 6, (char*)" ___) | |_| | |_____| |_| |___) |", SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE | SDI_CONSOLE_ATTRIBUTE_BGBLUE);
    print_stringat(23, 7, (char*)"|____/|____/___|     \\___/|____/ ", SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE | SDI_CONSOLE_ATTRIBUTE_BGBLUE);


    // Print system info
    char conbuf[15];
    snprintf(conbuf, sizeof(conbuf), "Console %i", (int)(console+1));
    print_stringat(33, 10, conbuf,  SDI_CONSOLE_ATTRIBUTE_FGLIGHTWHITE);


    while(1)
    {
        /* Scrolling step */
        x--;
        if(x < -strlen(banner))
            x = 85;

        /* Blank line */
        blank_line(23);

        /* Print banner */
        for(int i = 0; i < strlen(banner); i++)
            if(x + i > 0)
                print_charat(x + i, 23, banner[i], SDI_CONSOLE_ATTRIBUTE_FGLIGHTRED);

        sleep(150);
    }
}


int main()
{
    CORBA_Environment env(idl4_default_environment);

    // Resolve logger
    while (L4_IsNilThread(loggerid))
        loggerid = nameserver_lookup((path_t)"/server/logger");

    // Resolve console
    while (L4_IsNilThread(consoleid))
        consoleid = nameserver_lookup((path_t)"/server/console");

    // Resolve taskserver
    while (L4_IsNilThread(taskserverid))
        taskserverid = nameserver_lookup("/task");

    // Resolve myself
    L4_ThreadId_t myself = L4_Myself();

    /* And now.... action! */
    animation_loop();

    /* Spin forever */
    while (42) ;

    return 0;
}

