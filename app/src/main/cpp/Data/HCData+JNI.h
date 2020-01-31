//
//  HCData+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCDATA_JNI_H
#define HOLLOWSHAPES_HCDATA_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------

#define HCDataJNIClass "com/hollowcore/hollowjava/data/Data"
#define HCDataJNIReferenceFieldID "reference"
#define HCDataJNIReferenceFieldSignature "J"

void HCDataJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCDataRef self);
void HCDataJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCDataRef HCDataJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCDataJNINewJObject(JNIEnv* env, HCDataRef self);

#endif //HOLLOWSHAPES_HCDATA_JNI_H
