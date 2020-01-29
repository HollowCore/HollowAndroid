package com.hollowcore.hollowjava.geometry;

public class Size {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Special Values
    //----------------------------------------------------------------------------------------------------------------------------------
    public static final Size INVALID = new Size(Double.NaN, Double.NaN);
    public static final Size ZERO = new Size(0.0, 0.0);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Constructors
    //----------------------------------------------------------------------------------------------------------------------------------
    public Size(double width, double height) {
        initNative(width, height);
    }
    private native void initNative(double width, double height);
    private Size() { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Size other) { return isEqualNative(other); }
    private native boolean isEqualNative(Size other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public double getWidth() { return getWidthNative(); }
    private native double getWidthNative();

    public double getHeight() { return getHeightNative(); }
    private native double getHeightNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Queries
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isZero() { return isZeroNative(); }
    private native boolean isZeroNative();

    public boolean isInfinite() { return isInfiniteNative(); }
    private native boolean isInfiniteNative();

    public boolean isInvalid() { return isInvalidNative(); }
    private native boolean isInvalidNative();

    public boolean isSimilar(Size other, double dimensionDissimilarity) { return isSimilarNative(other, dimensionDissimilarity); }
    private native boolean isSimilarNative(Size other, double dimensionDissimilarity);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Size increased(double dx, double dy) { return increasedNative(dx, dy); }
    private native Size increasedNative(double dx, double dy);

    public Size decrease(double dx, double dy) { return decreasedNative(dx, dy); }
    private native Size decreasedNative(double dx, double dy);

    public Size scaled(double scalar) { return scaledNative(scalar); }
    private native Size scaledNative(double scalar);
}
