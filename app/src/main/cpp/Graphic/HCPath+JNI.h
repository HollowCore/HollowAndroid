//
//  HCPath+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCPATH_JNI_H
#define HOLLOWSHAPES_HCPATH_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCPathJNIClass "com/hollowcore/hollowjava/graphic/Path"

void HCPathJNIOnLoad(JNIEnv* env);
void HCPathJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPathRef self);
void HCPathJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCPathRef HCPathJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCPathJNINewJObject(JNIEnv* env, HCPathRef self);

#endif //HOLLOWSHAPES_HCPATH_JNI_H
