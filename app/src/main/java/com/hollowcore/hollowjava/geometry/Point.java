package com.hollowcore.hollowjava.geometry;

public class Point {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Special Values
    //----------------------------------------------------------------------------------------------------------------------------------
    public static final Point INVALID = new Point(Double.NaN, Double.NaN);
    public static final Point ZERO = new Point(0.0, 0.0);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Constructors
    //----------------------------------------------------------------------------------------------------------------------------------
    public Point(double x, double y) {
        initNative(x, y);
    }
    private native void initNative(double x, double y);
    private Point() { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public double getX() { return getXNative(); }
    private native double getXNative();

    public double getY() { return getYNative(); }
    private native double getYNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Point other) { return isEqualNative(other); }
    private native boolean isEqualNative(Point other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Queries
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isZero() { return isZeroNative(); }
    private native boolean isZeroNative();

    public boolean isInfinite() { return isInfiniteNative(); }
    private native boolean isInfiniteNative();

    public boolean isInvalid() { return isInvalidNative(); }
    private native boolean isInvalidNative();

    public boolean isSimilar(Point other, double axisDissimilarity) { return isSimilarNative(other, axisDissimilarity); }
    private native boolean isSimilarNative(Point other, double axisDissimilarity);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Point offset(double dx, double dy) { return offsetNative(dx, dy); }
    private native Point offsetNative(double dx, double dy);

    public Point scaled(double scalar) { return scaledNative(scalar); }
    private native Point scaledNative(double scalar);
}
