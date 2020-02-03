//
//  HCCore+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/2/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCCore+JNI.h"
#include "HCObject+JNI.h"
#include "HCObject+JNI.h"
#include "../Container/HCList+JNI.h"
#include "../Container/HCMap+JNI.h"
#include "../Container/HCSet+JNI.h"
#include "../Data/HCData+JNI.h"
#include "../Data/HCNumber+JNI.h"
#include "../Data/HCString+JNI.h"
#include "../Geometry/HCPoint+JNI.h"
#include "../Geometry/HCRectangle+JNI.h"
#include "../Geometry/HCSize+JNI.h"
#include "../Graphic/HCColor+JNI.h"
#include "../Graphic/HCPath+JNI.h"
#include "../Graphic/HCRaster+JNI.h"

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if ((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // Core
    HCObjectJNIOnLoad(env);

    // Container
    HCListJNIOnLoad(env);
    HCMapJNIOnLoad(env);
    HCSetJNIOnLoad(env);

    // Data
    HCDataJNIOnLoad(env);
    HCNumberJNIOnLoad(env);
    HCStringJNIOnLoad(env);

    // Geometry
    HCPointJNIOnLoad(env);
    HCRectangleJNIOnLoad(env);
    HCSizeJNIOnLoad(env);

    // Graphic
    HCColorJNIOnLoad(env);
    HCPathJNIOnLoad(env);
    HCRasterJNIOnLoad(env);

    return JNI_VERSION_1_6;
}
