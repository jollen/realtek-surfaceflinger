/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "SurfaceFlinger"

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#include <utils/Errors.h>
#include <utils/Log.h>

#include "LayerMokoid.h"
#include "SurfaceFlinger.h"

namespace android {
// ---------------------------------------------------------------------------

const uint32_t LayerMokoid::typeInfo = LayerBaseClient::typeInfo | 0x10;
const char* const LayerMokoid::typeID = "LayerMokoid";

// ---------------------------------------------------------------------------

LayerMokoid::LayerMokoid(SurfaceFlinger* flinger, DisplayID display,
        Client* client, int32_t i)
     : LayerBaseClient(flinger, display, client, i)
{
}

LayerMokoid::~LayerMokoid()
{
}

void LayerMokoid::onDraw(const Region& clip) const
{
    LOGI("LayerMokoid: onDraw");
}

// ---------------------------------------------------------------------------

}; // namespace android
