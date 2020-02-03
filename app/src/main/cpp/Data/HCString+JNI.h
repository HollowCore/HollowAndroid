//
//  HCString+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCSTRING_JNI_H
#define HOLLOWSHAPES_HCSTRING_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCStringJNIClass "com/hollowcore/hollowjava/data/HollowString"

void HCStringJNIOnLoad(JNIEnv* env);
void HCStringJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCStringRef self);
void HCStringJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCStringRef HCStringJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCStringJNINewJObject(JNIEnv* env, HCStringRef self);

#endif //HOLLOWSHAPES_HCSTRING_JNI_H
