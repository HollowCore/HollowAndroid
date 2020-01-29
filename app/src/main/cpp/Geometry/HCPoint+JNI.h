//
//  HCPoint+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCPOINT_JNI_H
#define HOLLOWSHAPES_HCPOINT_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCPointJNIClass "com/hollowcore/hollowjava/geometry/Point"
#define HCPointJNIReferenceFieldID "reference"
#define HCPointJNIReferenceFieldSignature "J"

void HCPointJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPoint self);
void HCPointJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCPoint HCPointJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCPointJNINewJObject(JNIEnv* env, HCPoint self);

#endif //HOLLOWSHAPES_HCPOINT_JNI_H
