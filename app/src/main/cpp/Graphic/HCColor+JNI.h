//
//  HCColor+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCCOLOR_JNI_H
#define HOLLOWSHAPES_HCCOLOR_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCColorJNIClass "com/hollowcore/hollowjava/graphic/Color"
#define HCColorJNIReferenceFieldID "reference"
#define HCColorJNIReferenceFieldSignature "J"

void HCColorJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCColor self);
void HCColorJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCColor HCColorJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCColorJNINewJObject(JNIEnv* env, HCColor self);

#endif //HOLLOWSHAPES_HCCOLOR_JNI_H
