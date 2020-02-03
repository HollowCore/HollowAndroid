//
//  HCMap+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCMAP_JNI_H
#define HOLLOWSHAPES_HCMAP_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCMapJNIClass "com/hollowcore/hollowjava/container/HollowMap"

void HCMapJNIOnLoad(JNIEnv* env);
void HCMapJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCMapRef self);
void HCMapJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCMapRef HCMapJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCMapJNINewJObject(JNIEnv* env, HCMapRef self);

#endif //HOLLOWSHAPES_HCMAP_JNI_H
