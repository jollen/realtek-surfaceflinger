/*
**
** Copyright 2013, Moko365 Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef MOKOID_SURFACE_H
#define MOKOID_SURFACE_H

#include <utils/threads.h>
#include <utils/MemoryBase.h>
#include <utils/MemoryHeapBase.h>
#include <utils/threads.h>

#include <ui/SurfaceComposerClient.h>
#include <ui/Region.h>
#include <ui/Rect.h>

namespace android {

class MokoidSurface {

public:
    MokoidSurface();
    ~MokoidSurface();
    
    int clientInit(int x, int y, int w, int h, int *stride);

    void lockScreen(void);
    void unlockScreen(void);

    char *getBuffer(void);

private:
    sp<SurfaceComposerClient> surfaceflinger_client;
    sp<Surface> surfaceflinger_surface;

    char *drawBuffer;

    int getFormat(int depth);
};

}; // namespace android

#endif
