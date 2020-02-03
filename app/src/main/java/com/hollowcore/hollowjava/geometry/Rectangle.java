package com.hollowcore.hollowjava.geometry;

import com.hollowcore.hollowjava.core.HollowObject;

public class Rectangle {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Definitions
    //----------------------------------------------------------------------------------------------------------------------------------
    public enum Edge {
        MIN_X,
        MIN_Y,
        MAX_X,
        MAX_Y,
    }

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Special Values
    //----------------------------------------------------------------------------------------------------------------------------------
    public static final Rectangle INVALID = new Rectangle(Double.NaN, Double.NaN, Double.NaN, Double.NaN);
    public static final Rectangle ZERO = new Rectangle(0.0, 0.0, 0.0, 0.0);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Constructors
    //----------------------------------------------------------------------------------------------------------------------------------
    public Rectangle(Point origin, Size size) { initNative(origin, size); }
    private native void initNative(Point origin, Size size);

    public Rectangle(double x, double y, double width, double height) { initComponentsNative(x, y, width, height); }
    private native void initComponentsNative(double x, double y, double width, double height);

    private Rectangle(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Rectangle other) { return isEqualNative(other); }
    private native boolean isEqualNative(Rectangle other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public Point getOrigin() { return getOriginNative(); }
    private native Point getOriginNative();

    public Size getSize() { return getSizeNative(); }
    private native Size getSizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Calculated Properties
    //----------------------------------------------------------------------------------------------------------------------------------
    public double getWidth() { return getWidthNative(); }
    private native double getWidthNative();

    public double getHeight() { return getHeightNative(); }
    private native double getHeightNative();

    public double getMinX() { return getMinXNative(); }
    private native double getMinXNative();

    public double getMidX() { return getMidXNative(); }
    private native double getMidXNative();

    public double getMaxX() { return getMaxXNative(); }
    private native double getMaxXNative();

    public double getMinY() { return getMinYNative(); }
    private native double getMinYNative();

    public double getMidY() { return getMidYNative(); }
    private native double getMidYNative();

    public double getMaxY() { return getMaxYNative(); }
    private native double getMaxYNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Queries
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isZero() { return isZeroNative(); }
    private native boolean isZeroNative();

    public boolean isInfinite() { return isInfiniteNative(); }
    private native boolean isInfiniteNative();

    public boolean isInvalid() { return isInvalidNative(); }
    private native boolean isInvalidNative();

    public boolean isSimilar(Rectangle other, double axisDissimilarity) { return isSimilarNative(other, axisDissimilarity); }
    private native boolean isSimilarNative(Rectangle other, double axisDissimilarity);

    public boolean contains(Point point) { return containsPointNative(point); }
    public native boolean containsPointNative(Point point);

    public boolean contains(Rectangle rectangle) { return containsRectangleNative(rectangle); }
    public native boolean containsRectangleNative(Rectangle rectangle);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Rectangle standardized() { return standardizedNative(); }
    private native Rectangle standardizedNative();

    public Rectangle integral() { return integralNative(); }
    private native Rectangle integralNative();

    public Rectangle outset(double dx, double dy) { return outsetNative(dx, dy); }
    private native Rectangle outsetNative(double dx, double dy);

    public Rectangle inset(double dx, double dy) { return insetNative(dx, dy); }
    private native Rectangle insetNative(double dx, double dy);

    public Rectangle offset(double dx, double dy) { return offsetNative(dx, dy); }
    private native Rectangle offsetNative(double dx, double dy);

    public Rectangle union(Rectangle other) { return unionNative(other); }
    private native Rectangle unionNative(Rectangle other);

    public Rectangle intersection(Rectangle other) { return intersectionNative(other); }
    private native Rectangle intersectionNative(Rectangle other);

    public Rectangle[] divided(double amount, Edge edge) { return dividedNative(amount, edge); }
    private native Rectangle[] dividedNative(double amount, Edge edge);
}
