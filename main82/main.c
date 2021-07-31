#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <psppower.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

PSP_MODULE_INFO("IdStorageChange", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

#define printf pspDebugScreenPrintf

void ErrorExit(int milisecs, char *fmt, ...)
{
	va_list list;
	char msg[256];	

	va_start(list, fmt);
	vsprintf(msg, fmt, list);
	va_end(list);

	printf(msg);

	sceKernelDelayThread(milisecs*1000);
	sceKernelExitGame();
}

#define printf pspDebugScreenPrintf

int LoadStartModule(char *module)
{
	SceUID mod = sceKernelLoadModule(module, 0, NULL);

	if (mod < 0)
		return mod;

	return sceKernelStartModule(mod, strlen(module)+1, module, NULL, NULL);
}

void Agreement()
{
	SceCtrlData pad;

	printf("You are about to change the idstorage of your PSP.\n");
	printf("Press X to start. By doing it, you accept the risk and ALL the responsability of what happens.\n");
	printf("If you don't agree press R button.\n");

	while (1)
	{
		sceCtrlReadBufferPositive(&pad, 1);

		if (pad.Buttons & PSP_CTRL_CROSS)
		{
			return;			
		}

		else if (pad.Buttons & PSP_CTRL_RTRIGGER)
		{
			sceKernelExitGame();
		}

		sceKernelDelayThread(10000);
	}
}

int main() 
{
	pspDebugScreenInit();

	if (scePowerGetBatteryLifePercent() < 75)
	{
		ErrorExit(6000, "Battery has to be at least at 75%%.\n");
	}
	
	int res = LoadStartModule("ta082_driver.prx");
	
	if (res < 0)
	{
		ErrorExit(6000, "Error loading/starting ta082_driver.prx.\n");
	}

	if (!pspTA082IsTA082())
	{
		ErrorExit(8000, "This psp doesn't seem to be a TA-082.\n");
	}

	if (pspTA082IsDowngraded())
	{
		ErrorExit(8000, "This program was already run once in this psp, or it was harddowngraded.\nNo need to run it again.\nJust use the generic downgrader directly.\n");
	}

	Agreement();

	res = pspTA082ChangeIdStorage();

	if (res < 0)
	{
		ErrorExit(6000, "Error %08X in pspTA082ChangeIdStorage. Probably read-only\n", res);
	}

	ErrorExit(6000, "Done. Exiting in 5 seconds.\nNow execute the generic downgrader.\n");


	return 0;
}



