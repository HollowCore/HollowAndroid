#include <jni.h>
#include "HollowCore/Source/HollowCore.h"

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowshapes_MainActivity_stringFromJNI(JNIEnv* env, jobject this) {
    HCStringRef hello = HCStringCreateWithCString("Hello from HollowCore");
    jstring helloJava = (*env)->NewStringUTF(env, HCStringAsCString(hello));
    HCRelease(hello);
    return helloJava;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
#define HCPointJNIClass "com/hollowcore/hollowjava/geometry/Point"
#define HCPointJNIReferenceFieldID "reference"
#define HCPointJNIReferenceFieldSignature "J"

void HCPointJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPoint self) {
    HCDataRef value = HCDataCreateWithBytes(sizeof(self), (HCByte*)&self);
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJNIReferenceFieldID, HCPointJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)value);
}

void HCPointJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJNIReferenceFieldID, HCPointJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(value);
}

HCPoint HCPointJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPointJNIReferenceFieldID, HCPointJNIReferenceFieldSignature);
    HCDataRef value = (HCDataRef)(*env)->GetLongField(env, thiz, fieldID);
    HCPoint self = *((HCPoint*)HCDataBytes(value));
    return self;
}

jobject HCPointJNINewJObject(JNIEnv* env, HCPoint self) {
    jclass clazz = (*env)->FindClass(env, HCPointJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCPointJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_initNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPoint self = HCPointMake(x, y);
    HCPointJNIInstallReferenceInJObject(env, thiz, self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getXNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCReal x = self.x;
    return (jdouble)x;
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getYNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCReal y = self.y;
    return (jdouble)y;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isEqualNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint other = HCPointJNIFromJObject(env, other_instance);
    HCBoolean isEqual = HCPointIsEqual(self, other);
    return (jboolean)isEqual;
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_hashNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCInteger hashValue = HCPointHashValue(self);
    return (jlong)hashValue;
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_toStringNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCPointPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Point toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isZeroNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCBoolean isZero = HCPointIsZero(self);
    return (jboolean)isZero;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInfiniteNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCBoolean isInfinite = HCPointIsInfinite(self);
    return (jboolean)isInfinite;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInvalidNative(JNIEnv *env, jobject thiz) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCBoolean isInvalid = HCPointIsInvalid(self);
    return (jboolean)isInvalid;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isSimilarNative(JNIEnv *env, jobject thiz, jobject other_instance, jdouble axis_dissimilarity) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint other = HCPointJNIFromJObject(env, other_instance);
    HCBoolean isSimilar = HCPointIsSimilar(self, other, axis_dissimilarity);
    return (jboolean)isSimilar;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_offsetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint offset = HCPointOffset(self, dx, dy);
    return HCPointJNINewJObject(env, offset);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_scaledNative(JNIEnv *env, jobject thiz, jdouble scalar) {
    HCPoint self = HCPointJNIFromJObject(env, thiz);
    HCPoint scaled = HCPointScale(self, scalar);
    return HCPointJNINewJObject(env, scaled);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------

#define HCPathJNIClass "com/hollowcore/hollowjava/graphic/Path"
#define HCPathJNIReferenceFieldID "reference"
#define HCPathJNIReferenceFieldSignature "J"
#define HCPathJNICommandEnum "com/hollowcore/hollowjava/graphic/Path$Command"
#define HCPathJNIElementClass "com/hollowcore/hollowjava/graphic/Path$Element"
#define HCPathJNIElementCommandFieldID "command"
#define HCPathJNIElementCommandFieldSignature "L" HCPathJNICommandEnum ";"
#define HCPathJNIElementPointsFieldID "points"
#define HCPathJNIElementPointsFieldSignature "[L" HCPointJNIClass ";"
#define HCPathJNIIntersectionListenerClass "com/hollowcore/hollowjava/graphic/Path$IntersectionListener"
#define HCPathJNIIntersectionListenerIntersectionMethodID "intersection"
#define HCPathJNIIntersectionListenerIntersectionMethodSignature "(L" HCPathJNIClass ";L" HCPathJNIClass ";L" HCPointJNIClass ";)Z"

void HCPathJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCPathRef self) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPathJNIReferenceFieldID, HCPathJNIReferenceFieldSignature);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)self);
}

void HCPathJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPathJNIReferenceFieldID, HCPathJNIReferenceFieldSignature);
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldID);
    (*env)->SetLongField(env, thiz, fieldID, (jlong)NULL);
    HCRelease(self);
}

HCPathRef HCPathJNIFromJObject(JNIEnv* env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldID = (*env)->GetFieldID(env, clazz, HCPathJNIReferenceFieldID, HCPathJNIReferenceFieldSignature);
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldID);
    return self;
}

jobject HCPathJNINewJObject(JNIEnv* env, HCPathRef self) {
    jclass clazz = (*env)->FindClass(env, HCPathJNIClass);
    jmethodID constructor = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, clazz, constructor);
    HCPathJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_initNative(JNIEnv *env, jobject thiz, jstring svg_path_data) {
    const char* svgPathData = (*env)->GetStringUTFChars(env, svg_path_data, NULL);
    HCPathRef self = HCPathCreate(svgPathData);
    (*env)->ReleaseStringUTFChars(env, svg_path_data, svgPathData);
    HCPathJNIInstallReferenceInJObject(env, thiz, self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathRef other = HCPathJNIFromJObject(env, otherInstance);
    return (jboolean)HCPathIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_hashNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCPathHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_toStringNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCPathPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Path toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getElementCountNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCInteger elementCount = HCPathElementCount(self);
    return (jint)elementCount;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getElementNative(JNIEnv *env, jobject thiz, jint element_index) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCInteger elementIndex = (HCInteger)element_index;
    HCPathElement element = HCPathElementAt(self, elementIndex);

    jclass elementClazz = (*env)->FindClass(env, HCPathJNIElementClass);
    jmethodID elementConstructor = (*env)->GetMethodID(env, elementClazz, "<init>", "()V");
    jfieldID elementCommandFieldID = (*env)->GetFieldID(env, elementClazz, HCPathJNIElementCommandFieldID, HCPathJNIElementCommandFieldSignature);
    jfieldID elementPointsFieldID = (*env)->GetFieldID(env, elementClazz, HCPathJNIElementPointsFieldID, HCPathJNIElementPointsFieldSignature);
    jclass commandEnumClazz = (*env)->FindClass(env, HCPathJNICommandEnum);
    jfieldID moveFieldID = (*env)->GetStaticFieldID(env, commandEnumClazz , "MOVE", "L" HCPathJNICommandEnum ";");
    jfieldID addLineFieldID = (*env)->GetStaticFieldID(env, commandEnumClazz , "ADD_LINE", "L" HCPathJNICommandEnum ";");
    jfieldID addQuadraticCurveFieldID = (*env)->GetStaticFieldID(env, commandEnumClazz , "ADD_QUADRATIC_CURVE", "L" HCPathJNICommandEnum ";");
    jfieldID addCubicCurveFieldID = (*env)->GetStaticFieldID(env, commandEnumClazz , "ADD_CUBIC_CURVE", "L" HCPathJNICommandEnum ";");
    jfieldID closeSubpathFieldID = (*env)->GetStaticFieldID(env, commandEnumClazz , "CLOSE_SUBPATH", "L" HCPathJNICommandEnum ";");
    jclass pointClazz = (*env)->FindClass(env, HCPointJNIClass);

    jobject commandField = NULL;
    jobjectArray pointArray = NULL;
    switch (element.command) {
        case HCPathCommandMove:
            commandField = (*env)->GetStaticObjectField(env, commandEnumClazz, moveFieldID);
            pointArray = (*env)->NewObjectArray(env, 1, pointClazz, NULL);
            (*env)->SetObjectArrayElement(env, pointArray, 0, HCPointJNINewJObject(env, element.points[0]));
            break;
        case HCPathCommandAddLine:
            commandField = (*env)->GetStaticObjectField(env, commandEnumClazz, addLineFieldID);
            pointArray = (*env)->NewObjectArray(env, 1, pointClazz, NULL);
            (*env)->SetObjectArrayElement(env, pointArray, 0, HCPointJNINewJObject(env, element.points[0]));
            break;
        case HCPathCommandAddQuadraticCurve:
            commandField = (*env)->GetStaticObjectField(env, commandEnumClazz, addQuadraticCurveFieldID);
            pointArray = (*env)->NewObjectArray(env, 2, pointClazz, NULL);
            (*env)->SetObjectArrayElement(env, pointArray, 0, HCPointJNINewJObject(env, element.points[0]));
            (*env)->SetObjectArrayElement(env, pointArray, 1, HCPointJNINewJObject(env, element.points[1]));
            break;
        case HCPathCommandAddCubicCurve:
            commandField = (*env)->GetStaticObjectField(env, commandEnumClazz, addCubicCurveFieldID);
            pointArray = (*env)->NewObjectArray(env, 3, pointClazz, NULL);
            (*env)->SetObjectArrayElement(env, pointArray, 0, HCPointJNINewJObject(env, element.points[0]));
            (*env)->SetObjectArrayElement(env, pointArray, 1, HCPointJNINewJObject(env, element.points[1]));
            (*env)->SetObjectArrayElement(env, pointArray, 2, HCPointJNINewJObject(env, element.points[2]));
            break;
        case HCPathCommandCloseSubpath:
            commandField = (*env)->GetStaticObjectField(env, commandEnumClazz, closeSubpathFieldID);
            pointArray = (*env)->NewObjectArray(env, 0, pointClazz, NULL);
            break;
    }

    jobject elementObject = (*env)->NewObject(env, elementClazz, elementConstructor);
    (*env)->SetObjectField(env, elementObject, elementCommandFieldID, commandField);
    (*env)->SetObjectField(env, elementObject, elementPointsFieldID, pointArray);

    return elementObject;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getCurrentPointNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPoint currentPoint = HCPathCurrentPoint(self);
    return HCPointJNINewJObject(env, currentPoint);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getBoundsNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCRectangle bounds = HCPathBounds(self);
    // TODO: Package into Rectangle
    return NULL;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Manipulation
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_moveNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathMoveToPoint(self, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addLineNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathAddLine(self, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addQuadraticCurveNative(JNIEnv *env, jobject thiz, jdouble cx, jdouble cy, jdouble x, jdouble y) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathAddQuadraticCurve(self, cx, cy, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addCubicCurveNative(JNIEnv *env, jobject thiz, jdouble cx0, jdouble cy0, jdouble cx1, jdouble cy1, jdouble x, jdouble y) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathAddCubicCurve(self, cx0, cy0, cx1, cy1, x, y);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_closeSubpathNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathCloseSubpath(self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Conversion
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_asSVGPathDataNative(JNIEnv *env, jobject thiz) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCStringRef svgPathData = HCPathPrintData(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Path HCPathPrintData");
//    HCRelease(memoryStream);
    return stringValue;
}

JNIEXPORT jobjectArray JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_asLineSegmentsNative(JNIEnv *env, jobject thiz, jdouble flatness_threshold) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCDataRef lineSegmentData = HCPathAsLineSegmentDataRetained(self, HCPathFlatnessNormal);
    HCInteger pointCount = HCDataSize(lineSegmentData) / sizeof(HCPoint);
    jclass pointClazz = (*env)->FindClass(env, HCPointJNIClass);
    jobjectArray pointArray = (*env)->NewObjectArray(env, pointCount, pointClazz, NULL);
    for (HCInteger pointIndex = 0; pointIndex < pointCount; pointIndex++) {
        HCPoint point = ((HCPoint*)HCDataBytes(lineSegmentData))[pointIndex];
        (*env)->SetObjectArrayElement(env, pointArray, pointIndex, HCPointJNINewJObject(env, point));
    }
    HCRelease(lineSegmentData);
    return pointArray;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Intersection
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_containsNative(JNIEnv *env, jobject thiz, jobject point_instance) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPoint point = HCPointJNIFromJObject(env, point_instance);
    HCBoolean containsPoint = HCPathContainsPoint(self, point);
    return (jboolean)containsPoint;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_containsNonZeroNative(JNIEnv *env, jobject thiz, jobject point_instance) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPoint point = HCPointJNIFromJObject(env, point_instance);
    HCBoolean containsPoint = HCPathContainsPointNonZero(self, point);
    return (jboolean)containsPoint;
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_intersectsNative(JNIEnv *env, jobject thiz, jobject other_instance) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathRef other = HCPathJNIFromJObject(env, other_instance);
    HCBoolean intersectsPath = HCPathIntersectsPath(self, other);
    return (jboolean)intersectsPath;
}

typedef struct HCPathIntersectionJavaContext {
    JNIEnv* env;
    jobject thiz;
    jobject other_instance;
    jobject intersection_listener;
} HCPathIntersectionJavaContext;
void HCPathIntersectionJava(void* context, HCBoolean* continueSearching, HCPathRef path, HCPathRef otherPath, HCPoint point) {
    JNIEnv* env = ((HCPathIntersectionJavaContext*)context)->env;
    jobject thiz = ((HCPathIntersectionJavaContext*)context)->thiz;
    jobject other_instance = ((HCPathIntersectionJavaContext*)context)->other_instance;
    jobject intersection_listener = ((HCPathIntersectionJavaContext*)context)->intersection_listener;
    jclass intersection_listener_clazz = (*env)->GetObjectClass(env, intersection_listener);
    jmethodID intersectionMethodID = (*env)->GetMethodID(env, intersection_listener_clazz, HCPathJNIIntersectionListenerIntersectionMethodID, HCPathJNIIntersectionListenerIntersectionMethodSignature);
    jobject point_instance = HCPointJNINewJObject(env, point);
    *continueSearching = (*env)->CallBooleanMethod(env, intersection_listener, intersectionMethodID, thiz, other_instance, point_instance);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_intersectionsNative(JNIEnv *env, jobject thiz, jobject other_instance, jobject intersection_listener) {
    HCPathRef self = HCPathJNIFromJObject(env, thiz);
    HCPathRef other = HCPathJNIFromJObject(env, other_instance);
    HCPathIntersectionJavaContext context = { .env = env, .thiz = thiz, .other_instance = other_instance, .intersection_listener = intersection_listener };
    HCPathIntersections(self, other, HCPathIntersectionJava, &context);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Evaluation
//----------------------------------------------------------------------------------------------------------------------------------
//    void HCPathEvaluateLine(HCReal t, HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateQuadraticCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx, HCReal cy, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateCubicCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx0, HCReal cy0, HCReal cx1, HCReal cy1, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathLineLineIntersection(HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal x2, HCReal y2, HCReal x3, HCReal y3, HCReal* t, HCReal* u);
