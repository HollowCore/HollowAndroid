//
//  HCSet+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCSET_JNI_H
#define HOLLOWSHAPES_HCSET_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCSetJNIClass "com/hollowcore/hollowjava/container/HollowSet"

void HCSetJNIOnLoad(JNIEnv* env);
void HCSetJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCSetRef self);
void HCSetJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCSetRef HCSetJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCSetJNINewJObject(JNIEnv* env, HCSetRef self);

#endif //HOLLOWSHAPES_HCSET_JNI_H
