//
//  HCRaster+JNI.h
//  HollowJava
//
//  Created by Matt Stoker on 1/28/20.
//  Copyright © 2020 HollowCore. All rights reserved.
//
//

#include "HCRaster+JNI.h"
#include "../Core/HCObject+JNI.h"
#include "HCColor+JNI.h"
#include "HCPath+JNI.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - JNI Convenience
//----------------------------------------------------------------------------------------------------------------------------------
jclass HCRasterJNIClazz = NULL;

void HCRasterJNIOnLoad(JNIEnv* env) {
    HCRasterJNIClazz = (*env)->NewGlobalRef(env, (*env)->FindClass(env, HCRasterJNIClass));
    HCObjectJNIAssociateTypeToClass(env, HCRasterType, HCRasterJNIClazz);
}

void HCRasterJNIInstallReferenceInJObject(JNIEnv* env, jobject thiz, HCRasterRef self) {
    HCObjectJNIInstallReferenceInJObject(env, thiz, self);
}

void HCRasterJNIReleaseReferenceInJObject(JNIEnv* env, jobject thiz) {
    HCObjectJNIReleaseReferenceInJObject(env, thiz);
}

HCRasterRef HCRasterJNIFromJObject(JNIEnv* env, jobject thiz) {
    return HCObjectJNIFromJObject(env, thiz);
}

jobject HCRasterJNINewJObject(JNIEnv* env, HCRasterRef self) {
    jmethodID constructor = (*env)->GetMethodID(env, HCRasterJNIClazz, "<init>", "()V");
    jobject thiz = (*env)->NewObject(env, HCRasterJNIClazz, constructor);
    HCRasterJNIInstallReferenceInJObject(env, thiz, self);
    return thiz;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Construction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_initNative(JNIEnv *env, jobject thiz, jint width, jint height) {
    HCRasterRef self = HCRasterCreate(width, height);
    HCRasterJNIInstallReferenceInJObject(env, thiz, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_finalizeNative(JNIEnv *env, jobject thiz) {
    HCRasterJNIReleaseReferenceInJObject(env, thiz);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Object Polymorphic Functions
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jboolean JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_isEqualNative(JNIEnv *env, jobject thiz, jobject otherInstance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCRasterRef other = HCRasterJNIFromJObject(env, otherInstance);
    return (jboolean)HCRasterIsEqual(self, other);
}

JNIEXPORT jlong JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_hashNative(JNIEnv *env, jobject thiz) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    return self == NULL ? 0 : HCRasterHashValue(self);
}

JNIEXPORT jstring JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_toStringNative(JNIEnv *env, jobject thiz) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    // TODO: memoryStream
//    HCRasterPrint(self, memoryStream);
    jstring stringValue = (*env)->NewStringUTF(env, "TODO: Implement Raster toStringNative");
//    HCRelease(memoryStream);
    return stringValue;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Attributes
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_getWidthNative(JNIEnv *env, jobject thiz) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCInteger width = HCRasterWidth(self);
    return (jint)width;
}

JNIEXPORT jint JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_getHeightNative(JNIEnv *env, jobject thiz) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCInteger height = HCRasterHeight(self);
    return (jint)height;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Pixel Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_getPixelNative(JNIEnv *env, jobject thiz, jint x_index, jint y_index) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor pixel = HCRasterPixelAt(self, x_index, y_index);
    return HCColorJNINewJObject(env, pixel);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_setPixelNative(JNIEnv *env, jobject thiz, jint x_index, jint y_index, jobject pixel_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor pixel = HCColorJNIFromJObject(env, pixel_instance);
    HCRasterSetPixelAt(self, x_index, y_index, pixel);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_getPixelsNative(JNIEnv *env, jobject thiz, jint start_xindex, jint start_yindex, jint end_xindex, jint end_yindex) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCInteger width = end_xindex - start_xindex;
    HCInteger height = end_yindex - start_yindex;
    HCColor pixels[width * height];
    HCRasterPixelsAt(self, start_xindex, start_yindex, end_xindex, end_yindex, pixels);
    HCRasterRef pixelSource = HCRasterCreate(width, height);
    HCRasterSetPixelsAt(pixelSource, 0, 0, width, height, pixels);
    return HCRasterJNINewJObject(env, pixelSource);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_setPixelsNative(JNIEnv *env, jobject thiz, jint x, jint y, jobject pixels_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCRasterRef pixelSource = HCRasterJNIFromJObject(env, pixels_instance);
    HCInteger startXIndex = x;
    HCInteger startYIndex = y;
    HCInteger endXIndex = startXIndex + HCRasterWidth(pixelSource);
    HCInteger endYIndex = startYIndex + HCRasterHeight(pixelSource);
    HCInteger width = HCRasterWidth(pixelSource);
    HCInteger height = HCRasterHeight(pixelSource);
    HCColor pixels[width * height];
    HCRasterPixelsAt(pixelSource, 0, 0, width, height, pixels);
    HCRasterSetPixelsAt(self, startXIndex, startYIndex, endXIndex, endYIndex, pixels);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_clearNative(JNIEnv *env, jobject thiz) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCRasterClear(self);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Lookup Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_getPixelNearestNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor pixelNearest = HCRasterPixelNearest(self, x, y);
    return HCColorJNINewJObject(env, pixelNearest);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_getPixelFilteredNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor pixelFiltered = HCRasterPixelFiltered(self, x, y);
    return HCColorJNINewJObject(env, pixelFiltered);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Curve Drawing Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawPointNative(JNIEnv *env, jobject thiz, jdouble x, jdouble y, jobject color_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor color = HCColorJNIFromJObject(env, color_instance);
    HCRasterDrawPoint(self, x, y, color);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawLineNative(JNIEnv *env, jobject thiz, jdouble x0, jdouble y0, jdouble x1, jdouble y1, jobject c0_instance, jobject c1_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor c0 = HCColorJNIFromJObject(env, c0_instance);
    HCColor c1 = HCColorJNIFromJObject(env, c1_instance);
    HCRasterDrawLine(self, x0, y0, x1, y1, c0, c1);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawQuadraticCurveNative(JNIEnv *env, jobject thiz, jdouble x0, jdouble y0, jdouble cx, jdouble cy, jdouble x1, jdouble y1, jobject c0_instance, jobject c1_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor c0 = HCColorJNIFromJObject(env, c0_instance);
    HCColor c1 = HCColorJNIFromJObject(env, c1_instance);
    HCRasterDrawQuadraticCurve(self, x0, y0, cx, cy, x1, y1, c0, c1);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawCubicCurveNative(JNIEnv *env, jobject thiz, jdouble x0, jdouble y0, jdouble cx0, jdouble cy0, jdouble cx1, jdouble cy1, jdouble x1, jdouble y1, jobject c0_instance, jobject c1_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor c0 = HCColorJNIFromJObject(env, c0_instance);
    HCColor c1 = HCColorJNIFromJObject(env, c1_instance);
    HCRasterDrawCubicCurve(self, x0, y0, cx0, cy0, cx1, cy1, x1, y1, c0, c1);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawArcNative(JNIEnv *env, jobject thiz, jdouble x0, jdouble y0, jdouble x1, jdouble y1, jdouble xr, jdouble yr, jdouble theta, jboolean large_arc, jboolean sweep, jobject c0_instance, jobject c1_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor c0 = HCColorJNIFromJObject(env, c0_instance);
    HCColor c1 = HCColorJNIFromJObject(env, c1_instance);
    HCRasterDrawArc(self, x0, y0, x1, y1, xr, yr, theta, large_arc, sweep, c0, c1);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawPathDataNative(JNIEnv *env, jobject thiz, jstring path_data, jobject color_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor color = HCColorJNIFromJObject(env, color_instance);
    const char* svgPathData = (*env)->GetStringUTFChars(env, path_data, NULL);
    HCRasterDrawPathData(self, svgPathData, color);
    (*env)->ReleaseStringUTFChars(env, path_data, svgPathData);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawPathNative(JNIEnv *env, jobject thiz, jobject path_instance, jobject color_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCPathRef path = HCPathJNIFromJObject(env, path_instance);
    HCColor color = HCColorJNIFromJObject(env, color_instance);
    HCRasterDrawPath(self, path, color);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Shape Drawing Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawTriangleNative(JNIEnv *env, jobject thiz, jdouble ax, jdouble ay, jdouble bx, jdouble by, jdouble cx, jdouble cy, jobject ca_instance, jobject cb_instance, jobject cc_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor ca = HCColorJNIFromJObject(env, ca_instance);
    HCColor cb = HCColorJNIFromJObject(env, cb_instance);
    HCColor cc = HCColorJNIFromJObject(env, cc_instance);
    HCRasterDrawTriangle(self, ax, ay, bx, by, cx, cy, ca, cb, cc);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_fillTriangleNative(JNIEnv *env, jobject thiz, jdouble ax, jdouble ay, jdouble bx, jdouble by, jdouble cx, jdouble cy, jobject ca_instance, jobject cb_instance, jobject cc_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor ca = HCColorJNIFromJObject(env, ca_instance);
    HCColor cb = HCColorJNIFromJObject(env, cb_instance);
    HCColor cc = HCColorJNIFromJObject(env, cc_instance);
    HCRasterFillTriangle(self, ax, ay, bx, by, cx, cy, ca, cb, cc);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_fillTexturedTriangleNative(JNIEnv *env, jobject thiz, jdouble ax, jdouble ay, jdouble bx, jdouble by, jdouble cx, jdouble cy, jobject texture_instance, jdouble tax, jdouble tay, jdouble tbx, jdouble tby, jdouble tcx, jdouble tcy) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCRasterRef texture = HCRasterJNIFromJObject(env, texture_instance);
    HCRasterFillTexturedTriangle(self, ax, ay, bx, by, cx, cy, texture, tax, tay, tbx, tby, tcx, tcy);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_drawQuadNative(JNIEnv *env, jobject thiz, jdouble ax, jdouble ay, jdouble bx, jdouble by, jdouble cx, jdouble cy, jdouble dx, jdouble dy, jobject ca_instance, jobject cb_instance, jobject cc_instance, jobject cd_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor ca = HCColorJNIFromJObject(env, ca_instance);
    HCColor cb = HCColorJNIFromJObject(env, cb_instance);
    HCColor cc = HCColorJNIFromJObject(env, cc_instance);
    HCColor cd = HCColorJNIFromJObject(env, cd_instance);
    HCRasterDrawQuad(self, ax, ay, bx, by, cx, cy, dx, dy, ca, cb, cc, cd);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_fillQuadNative(JNIEnv *env, jobject thiz, jdouble ax, jdouble ay, jdouble bx, jdouble by, jdouble cx, jdouble cy, jdouble dx, jdouble dy, jobject ca_instance, jobject cb_instance, jobject cc_instance, jobject cd_instance) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCColor ca = HCColorJNIFromJObject(env, ca_instance);
    HCColor cb = HCColorJNIFromJObject(env, cb_instance);
    HCColor cc = HCColorJNIFromJObject(env, cc_instance);
    HCColor cd = HCColorJNIFromJObject(env, cd_instance);
    HCRasterFillQuad(self, ax, ay, bx, by, cx, cy, dx, dy, ca, cb, cc, cd);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_fillTexturedQuadNative(JNIEnv *env, jobject thiz, jdouble ax, jdouble ay, jdouble bx, jdouble by, jdouble cx, jdouble cy, jdouble dx, jdouble dy, jobject texture_instance, jdouble tax, jdouble tay, jdouble tbx, jdouble tby, jdouble tcx, jdouble tcy, jdouble tdx, jdouble tdy) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCRasterRef texture = HCRasterJNIFromJObject(env, texture_instance);
    HCRasterFillTexturedQuad(self, ax, ay, bx, by, cx, cy, dx, dy, texture, tax, tay, tbx, tby, tcx, tcy, tdx, tdy);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Data Extraction
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jintArray JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_asARGB8888Native(JNIEnv *env, jobject thiz) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    HCInteger width = HCRasterWidth(self);
    HCInteger height = HCRasterHeight(self);
    jsize pixelCount = (jsize)(width * height);
    uint32_t pixels[pixelCount];
    HCRasterExtractARGB8888(self, pixels);
    jintArray pixelArray = (*env)->NewIntArray(env, pixelCount);
    (*env)->SetIntArrayRegion(env, pixelArray, 0, pixelCount, (jint*)pixels);
    return pixelArray;
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - File Operations
//----------------------------------------------------------------------------------------------------------------------------------
JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_loadPPMNative(JNIEnv *env, jclass clazz, jstring path_string) {
    const char* path = (*env)->GetStringUTFChars(env, path_string, NULL);
    HCRasterRef self = HCRasterCreateByLoadingPPM(path);
    (*env)->ReleaseStringUTFChars(env, path_string, path);
    return HCRasterJNINewJObject(env, self);

}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_savePPMNative(JNIEnv *env, jobject thiz, jstring path_string, jboolean binary) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    const char* path = (*env)->GetStringUTFChars(env, path_string, NULL);
    HCRasterSavePPMWithOptions(self, path, binary);
    (*env)->ReleaseStringUTFChars(env, path_string, path);
}

JNIEXPORT jobject JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_loadBMPNative(JNIEnv *env, jclass clazz, jstring path_string) {
    const char* path = (*env)->GetStringUTFChars(env, path_string, NULL);
    HCRasterRef self = HCRasterCreateByLoadingBMP(path);
    (*env)->ReleaseStringUTFChars(env, path_string, path);
    return HCRasterJNINewJObject(env, self);
}

JNIEXPORT void JNICALL
Java_com_hollowcore_hollowjava_graphic_Raster_saveBMPNative(JNIEnv *env, jobject thiz, jstring path_string, jboolean reverse) {
    HCRasterRef self = HCRasterJNIFromJObject(env, thiz);
    const char* path = (*env)->GetStringUTFChars(env, path_string, NULL);
    HCRasterSaveBMPWithOptions(self, path, reverse);
    (*env)->ReleaseStringUTFChars(env, path_string, path);
}
