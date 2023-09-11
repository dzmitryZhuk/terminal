#include "app_def.h"

#define APP_TASK_MIN_PRIO	30
#define _APP_TASK_SIZE		(1024+1024)			// Thread stack size
#define _APP_TASK_PRIO		(APP_TASK_MIN_PRIO + 3)	// Thread priority
static unsigned int pTaskStk[_APP_TASK_SIZE];					// Thread stack

static void showqr()
{
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;
	char * pbmp;
	pbmp = gui_load_bmp_ex(IMG_QR, &logowidth , &logoheight, &logocolor);
	if (pbmp != 0){
		gui_begin_batch_paint();
		gui_set_win_rc();
		gui_clear_dc();
        logoleft = (gui_get_width()-logowidth)/2;
		logotop = (gui_get_height()-logoheight)/2;
		gui_out_bits_ex(logoleft, logotop, pbmp , logowidth , logoheight , 0 , logocolor);
		Util_Free(pbmp);
		gui_end_batch_paint();
        while(1)
		    Sys_Delay(1000);
	} 
}

static void showlogo()
{
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;
	char * pbmp;
	pbmp = gui_load_bmp_ex(IMG_LOGO, &logowidth , &logoheight, &logocolor);
	if (pbmp != 0){
		gui_begin_batch_paint();
		gui_set_win_rc();
		gui_clear_dc();
        logoleft = (gui_get_width()-logowidth)/2;
		logotop = (gui_get_height()-logoheight)/2;
		gui_out_bits_ex(logoleft, logotop, pbmp , logowidth , logoheight , 0 , logocolor);
		Util_Free(pbmp);
		gui_end_batch_paint();
		Sys_Delay(1000);
	} 
}

// this functions used only for MF67
void MF67_init()
{
#ifdef SOCKET_SUPPORT
    Sys_init_mini(SOCKET_SUPPORT);
#else
    Sys_init_mini(0);
#endif
#ifdef LOG
    Sys_console_switch(1);
#endif
    Sys_qr_set_buff();
}

void app_main_task(void * pParam)
{
    MF67_init();
    Sys_setAppVision(APP_VER);
    set_malloc_log(0);
    showlogo();
    showqr();
}

void app_main()
{
    // driver initialization / ucosii initialization
    Sys_driverlib_init();
    // ucosii run
    Sys_TaskCreate(app_main_task,_APP_TASK_PRIO,(char *)pTaskStk, _APP_TASK_SIZE); // this function ONLY working for MF67, MF66S, MF67A10
    while(1)
        Sys_Delay(1000);
}

void main()
{
    //Sys_Init(argc, argv, APP_NAME);
    if(Sys_get_is_1903())
        mf_start_apps(app_main);
    else
        app_main(0);
}