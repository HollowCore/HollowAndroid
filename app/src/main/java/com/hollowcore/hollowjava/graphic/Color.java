package com.hollowcore.hollowjava.graphic;

import com.hollowcore.hollowjava.core.HollowObject;

public class Color {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Special Values
    //----------------------------------------------------------------------------------------------------------------------------------
    public static final Color INVALID = new Color(Double.NaN, Double.NaN, Double.NaN, Double.NaN);
    public static final Color ZERO = new Color(0.0, 0.0, 0.0, 0.0);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Constructors
    //----------------------------------------------------------------------------------------------------------------------------------
    public Color(double alpha, double red, double green, double blue) { initNative(alpha, red, green, blue); }
    private native void initNative(double alpha, double red, double green, double blue);
    private Color(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Color other) { return isEqualNative(other); }
    private native boolean isEqualNative(Color other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public double getAlpha() { return getAlphaNative(); }
    private native double getAlphaNative();

    public double getRed() { return getRedNative(); }
    private native double getRedNative();

    public double getGreen() { return getGreenNative(); }
    private native double getGreenNative();

    public double getBlue() { return getBlueNative(); }
    private native double getBlueNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Queries
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isClamped() { return isClampedNative(); }
    private native boolean isClampedNative();

    public boolean isInvalid() { return isInvalidNative(); }
    private native boolean isInvalidNative();

    public boolean isSimilar(Color other, double channelDissimilarity) { return isSimilarNative(other, channelDissimilarity); }
    private native boolean isSimilarNative(Color other, double channelDissimilarity);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Color aggregated(Color other) { return aggregatedNative(other); }
    private native Color aggregatedNative(Color other);

    public Color scaled(Color other) { return scaledByColorNative(other); }
    private native Color scaledByColorNative(Color other);

    public Color scaled(double scalar) { return scaledByDoubleNative(scalar); }
    private native Color scaledByDoubleNative(double scalar);

    public Color clamped() { return clampedNative(); }
    private native Color clampedNative();

    public Color interpolated(Color other, double t) { return interpolatedNative(other, t); }
    private native Color interpolatedNative(Color other, double t);
}
