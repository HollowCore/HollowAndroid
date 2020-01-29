//
//  HCRaster+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCRASTER_JNI_H
#define HOLLOWSHAPES_HCRASTER_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------

#define HCRasterJNIClass "com/hollowcore/hollowjava/graphic/Raster"
#define HCRasterJNIReferenceFieldID "reference"
#define HCRasterJNIReferenceFieldSignature "J"

void HCRasterJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCRasterRef self);
void HCRasterJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCRasterRef HCRasterJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCRasterJNINewJObject(JNIEnv* env, HCRasterRef self);

#endif //HOLLOWSHAPES_HCRASTER_JNI_H
