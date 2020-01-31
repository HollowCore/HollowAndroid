//
//  HCNumber+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCNUMBER_JNI_H
#define HOLLOWSHAPES_HCNUMBER_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------

#define HCNumberJNIClass "com/hollowcore/hollowjava/data/Number"
#define HCNumberJNIReferenceFieldID "reference"
#define HCNumberJNIReferenceFieldSignature "J"

void HCNumberJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCNumberRef self);
void HCNumberJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCNumberRef HCNumberJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCNumberJNINewJObject(JNIEnv* env, HCNumberRef self);

#endif //HOLLOWSHAPES_HCNUMBER_JNI_H
