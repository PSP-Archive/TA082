#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspidstorage.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


PSP_MODULE_INFO("pspTA082_Driver", 0x1006, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

u8 leaf[512];

int pspTA082ChangeIdStorage()
{
	int k1 = pspSdkSetK1(0);	
	
	if (sceIdStorageIsReadOnly())
		return -1;

	memset(leaf, 0, 512);
	leaf[0] = 0xDA;
	leaf[1] = 0xDA;
	leaf[2] = 0xDA;
	leaf[3] = 0xDA;
	leaf[4] = 0xDA;
	leaf[5] = 0xDA;

	//sceIdStorageWriteLeaf(0x0044, leaf);
	
	sceIdStorageReadLeaf(0x0042, leaf);
	sceIdStorageWriteLeaf(0x0043, leaf);

	sceIdStorageReadLeaf(0x0041, leaf);
	sceIdStorageWriteLeaf(0x0042, leaf);

	sceIdStorageReadLeaf(0x0006, leaf);	
	sceIdStorageWriteLeaf(0x0041, leaf);

	sceIdStorageReadLeaf(0x0005, leaf);
	sceIdStorageWriteLeaf(0x0006, leaf);

	sceIdStorageReadLeaf(0x0004, leaf);
	sceIdStorageWriteLeaf(0x0005, leaf);

	sceIdStorageReadLeaf(0x0046, leaf);
	//memset(leaf, 0, 512);
	sceIdStorageWriteLeaf(0x0004, leaf);

	sceIdStorageReadLeaf(0x0045, leaf);
	sceIdStorageWriteLeaf(0x0046, leaf);

	memset(leaf, 0, 512);
	leaf[0] = 0x09;

	sceIdStorageWriteLeaf(0x0045, leaf);

	memset(leaf, 0, 512);
	sceIdStorageWriteLeaf(0x0047, leaf);

	pspSdkSetK1(k1);
	return 0;
}


int pspTA082IsDowngraded()
{
	int key;
	int k1 = pspSdkSetK1(0);

	sceIdStorageLookup(0x04, 0, &key, 4);

	if (key == 0x4272796E)
	{
		pspSdkSetK1(k1);
		return 0;
	}

	pspSdkSetK1(k1);
	return 1;
}

int pspTA082IsTA082()
{
	int k1 = pspSdkSetK1(0);

	sceIdStorageReadLeaf(0x100, leaf);

	if (leaf[0x3F] == 2)
	{
		sceIdStorageReadLeaf(0x50, leaf);

		if (leaf[0x21] == 2)
		{		
			pspSdkSetK1(k1);
			return 1;
		}
	}

	pspSdkSetK1(k1);
	return 0;
}

int module_start(SceSize args, void *argp)
{
	return 0;
}

int module_stop(void)
{
	return 0;
}
