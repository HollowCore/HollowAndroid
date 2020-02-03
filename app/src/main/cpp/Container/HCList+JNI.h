//
//  HCList+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCLIST_JNI_H
#define HOLLOWSHAPES_HCLIST_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCListJNIClass "com/hollowcore/hollowjava/container/HollowList"

void HCListJNIOnLoad(JNIEnv* env);
void HCListJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCListRef self);
void HCListJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCListRef HCListJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCListJNINewJObject(JNIEnv* env, HCListRef self);

#endif //HOLLOWSHAPES_HCLIST_JNI_H
