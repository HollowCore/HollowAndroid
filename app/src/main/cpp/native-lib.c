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
// MARK: - Constructors
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_initNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    // TODO: implement initNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getXNative(JNIEnv *env, jobject thiz) {
    // TODO: implement getXNative()
}

JNIEXPORT jdouble JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_getYNative(JNIEnv *env, jobject thiz) {
    // TODO: implement getYNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isEqualNative(JNIEnv *env, jobject thiz, jobject other) {
    // TODO: implement isEqualNative()
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_hashNative(JNIEnv *env, jobject thiz) {
    // TODO: implement hashNative()
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_toStringNative(JNIEnv *env, jobject thiz) {
    // TODO: implement toStringNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Queries
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isZeroNative(JNIEnv *env, jobject thiz) {
    // TODO: implement isZeroNative()
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInfiniteNative(JNIEnv *env, jobject thiz) {
    // TODO: implement isInfiniteNative()
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isInvalidNative(JNIEnv *env, jobject thiz) {
    // TODO: implement isInvalidNative()
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_isSimilarNative(JNIEnv *env, jobject thiz, jobject other, jdouble axis_dissimilarity) {
    // TODO: implement isSimilarNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_offsetNative(JNIEnv *env, jobject thiz, jdouble dx, jdouble dy) {
    // TODO: implement offsetNative()
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_geometry_Point_scaledNative(JNIEnv *env, jobject thiz, jdouble scalar) {
    // TODO: implement scaledNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_initNative(JNIEnv *env, jobject thiz, jstring svg_path_data) {
    const char* svgPathData = (*env)->GetStringUTFChars(env, svg_path_data, NULL);
    HCPathRef self = HCPathCreate(svgPathData);
    (*env)->ReleaseStringUTFChars(env, svg_path_data, svgPathData);
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldId = (*env)->GetFieldID(env, clazz, "reference", "J");
    (*env)->SetLongField(env, thiz, fieldId, (jlong)self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_isEqualNative(JNIEnv *env, jobject thiz, jobject other) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldId = (*env)->GetFieldID(env, clazz, "reference", "J");
    HCPathRef self = (*env)->GetLongField(env, thiz, fieldId);
    HCPathRef otherInstance = (HCPathRef)(*env)->GetLongField(env, other, fieldId);
    return (jboolean)HCPathIsEqual(self, otherInstance);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_hashNative(JNIEnv *env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldId = (*env)->GetFieldID(env, clazz, "reference", "J");
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldId);
    return self == NULL ? 0 : HCPathHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_toStringNative(JNIEnv *env, jobject thiz) {
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldId = (*env)->GetFieldID(env, clazz, "reference", "J");
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldId);
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
    jclass clazz = (*env)->GetObjectClass(env, thiz);
    jfieldID fieldId = (*env)->GetFieldID(env, clazz, "reference", "J");
    HCPathRef self = (HCPathRef)(*env)->GetLongField(env, thiz, fieldId);
    HCInteger elementCount = HCPathElementCount(self);
    return (jint)elementCount;
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getElementNative(JNIEnv *env, jobject thiz, jint element_index) {
    // TODO: implement getElementNative()
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getCurrentPointNative(JNIEnv *env, jobject thiz) {
    // TODO: implement getCurrentPointNative()
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_getBoundsNative(JNIEnv *env, jobject thiz) {
    // TODO: implement getBoundsNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Manipulation
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_moveNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    // TODO: implement moveNative()
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addLineNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    // TODO: implement addLineNative()
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addQuadraticCurveNative(JNIEnv *env, jobject thiz, jdouble cx, jdouble cy, jdouble x, jdouble y) {
    // TODO: implement addQuadraticCurveNative()
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_addCubicCurveNative(JNIEnv *env, jobject thiz, jdouble cx0, jdouble cy0, jdouble cx1, jdouble cy1, jdouble x, jdouble y) {
    // TODO: implement addCubicCurveNative()
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_closeSubpathNative(JNIEnv *env, jobject thiz) {
    // TODO: implement closeSubpathNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Conversion
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_asSVGPathDataNative(JNIEnv *env, jobject thiz) {
    // TODO: implement asSVGPathDataNative()
}

JNIEXPORT jobjectArray JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_asLineSegmentsNative(JNIEnv *env, jobject thiz, jdouble flatness_threshold) {
    // TODO: implement asLineSegmentsNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Intersection
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_containsPointNative(JNIEnv *env, jobject thiz, jobject point) {
    // TODO: implement containsPointNative()
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_containsPointNonZeroNative(JNIEnv *env, jobject thiz, jobject point) {
    // TODO: implement containsPointNonZeroNative()
}

JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_intersectsPathNative(JNIEnv *env, jobject thiz, jobject other) {
    // TODO: implement intersectsPathNative()
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Path_intersectionsNative(JNIEnv *env, jobject thiz, jobject other, jobject intersection_listener) {
    // TODO: implement intersectionsNative()
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Path Evaluation
//----------------------------------------------------------------------------------------------------------------------------------
//    void HCPathEvaluateLine(HCReal t, HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateQuadraticCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx, HCReal cy, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateCubicCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx0, HCReal cy0, HCReal cx1, HCReal cy1, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathLineLineIntersection(HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal x2, HCReal y2, HCReal x3, HCReal y3, HCReal* t, HCReal* u);
