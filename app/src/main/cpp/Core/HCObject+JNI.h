//
//  HCObject+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 2/1/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCOBJECT_JNI_H
#define HOLLOWSHAPES_HCOBJECT_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------

#define HCObjectJNIClass "com/hollowcore/hollowjava/core/HollowObject"
#define HCObjectJNIReferenceFieldID "reference"
#define HCObjectJNIReferenceFieldSignature "J"

void HCObjectJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCObjectRef self);
void HCObjectJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCObjectRef HCObjectJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCObjectJNINewJObject(JNIEnv* env, HCObjectRef self);

#endif //HOLLOWSHAPES_HCOBJECT_JNI_H
