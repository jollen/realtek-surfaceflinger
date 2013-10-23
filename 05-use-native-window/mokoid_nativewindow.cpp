#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <utils/Log.h>

#include "MokoidSurface.h"

using namespace android;

#define RGBA8888(r, g, b, a)	\
	((((r) & 0xff) <<  0) |	\
	 (((g) & 0xff) <<  8) |	\
	 (((b) & 0xff) << 16) |	\
	 (((a) & 0xff) << 24))

static void draw(char *buf, int w, int h, int stride)
{
	int x, y;

	for (y = 0; y < h; y++) {
		char *row = buf + stride * y;

		for (x = 0; x < w; x++) {
			int r, g, b, a;

			r = 0xff;
			g = 0x00;
			b = 0x00;
			a = 0xff;

			((uint32_t *) row)[x] = RGBA8888(r, g, b, a);
		}
	}
}

sp<MokoidSurface> surface;

static void demo(int x, int y, int w, int h)
{
    char *buf;
    int stride;

    LOGI("MokoidSurface: we use sp<> template.");
    surface = new MokoidSurface();

    if (!surface->clientInit(x, y, w, h, &stride)) {
	LOGI("failed to initialize a surface\n");
	return;
    } 

    surface->lockScreen();
    buf = surface->getBuffer();
    draw(buf, w, h, stride);
    surface->unlockScreen();
}

int main(int argc, char **argv)
{
    //sp<ProcessState> proc(ProcessState::self());
    LOGI("MokoidSurface is started.");

    ProcessState::self()->startThreadPool();

    demo(10, 10, 160, 240);
    sleep(5);

    demo(20, 20, 160, 240);
    sleep(5);

    IPCThreadState::self()->joinThreadPool();

    return 0;
}
