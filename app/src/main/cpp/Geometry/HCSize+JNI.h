//
//  HCSize+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//

#ifndef HOLLOWSHAPES_HCSIZE_JNI_H
#define HOLLOWSHAPES_HCSIZE_JNI_H

#include <jni.h>
#include "../HollowCore/Source/HollowCore.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCSizeJNIClass "com/hollowcore/hollowjava/geometry/Size"
#define HCSizeJNIReferenceFieldID "reference"
#define HCSizeJNIReferenceFieldSignature "J"

void HCSizeJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCSize self);
void HCSizeJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz);
HCSize HCSizeJNIFromJObject(JNIEnv* env, jobject thiz);
jobject HCSizeJNINewJObject(JNIEnv* env, HCSize self);

#endif //HOLLOWSHAPES_HCSIZE_JNI_H
