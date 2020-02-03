package com.hollowcore.hollowjava.graphic;

import androidx.annotation.NonNull;

import com.hollowcore.hollowjava.core.HollowObject;
import com.hollowcore.hollowjava.geometry.Point;
import com.hollowcore.hollowjava.geometry.Rectangle;

public class Path {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Definitions
    //----------------------------------------------------------------------------------------------------------------------------------
    public enum Command {
        MOVE,
        ADD_LINE,
        ADD_QUADRATIC_CURVE,
        ADD_CUBIC_CURVE,
        CLOSE_SUBPATH,
    }

    public class Element {
        public Command command;
        public Point[] points;

        @NonNull
        @Override
        public String toString() {
            switch (command) {
                case MOVE: return "M " + points[0].getX() + " " + points[0].getY() + " ";
                case ADD_LINE: return "L " + points[0].getX() + " " + points[0].getY() + " ";
                case ADD_QUADRATIC_CURVE: return "Q " + points[0].getX() + " " + points[0].getY() + " " + points[1].getX() + " " + points[1].getY() + " ";
                case ADD_CUBIC_CURVE: return "C " + points[0].getX() + " " + points[0].getY() + " " + points[1].getX() + " " + points[1].getY() + " " + points[2].getX() + " " + points[2].getY() + " ";
                case CLOSE_SUBPATH: return "Z ";
                default: return "";
            }
        }
    }

    public interface IntersectionListener {
        boolean intersection(Path path, Path otherPath, Point point);
    }

    public static final double COARSE_FLATNESS = 1.01;
    public static final double NORMAL_FLATNESS = 1.001;
    public static final double FINE_FLATNESS = 1.0001;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public Path() { this(""); }
    public Path(String svgPathData) { initNative(svgPathData); }
    private native void initNative(String svgPathData);
    private Path(HollowObject unused) { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Path other) { return isEqualNative(other); }
    private native boolean isEqualNative(Path other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public int getElementCount() { return getElementCountNative(); }
    private native int getElementCountNative();

    public Element getElement(int elementIndex) { return getElementNative(elementIndex); }
    private native Element getElementNative(int elementIndex);

    public Point getCurrentPoint() { return getCurrentPointNative(); }
    private native Point getCurrentPointNative();

    public Rectangle getBounds() { return getBoundsNative(); }
    private native Rectangle getBoundsNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Manipulation
    //----------------------------------------------------------------------------------------------------------------------------------
    public void move(double x, double y) { moveNative(x, y); }
    private native void moveNative(double x, double y);

    public void addLine(double x, double y) { addLineNative(x, y); }
    private native void addLineNative(double x, double y);

    public void addQuadraticCurve(double cx, double cy, double x, double y) { addQuadraticCurveNative(cx, cy, x, y); }
    private native void addQuadraticCurveNative(double cx, double cy, double x, double y);

    public void addCubicCurve(double cx0, double cy0, double cx1, double cy1, double x, double y) { addCubicCurveNative(cx0, cy0, cx1, cy1, x, y); }
    private native void addCubicCurveNative(double cx0, double cy0, double cx1, double cy1, double x, double y);

    public void closeSubpath() { closeSubpathNative(); }
    private native void closeSubpathNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Conversion
    //----------------------------------------------------------------------------------------------------------------------------------
    public String asSVGPathData() { return asSVGPathDataNative(); }
    private native String asSVGPathDataNative();

    public Point[] asLineSegments() { return asLineSegments(NORMAL_FLATNESS); }
    public Point[] asLineSegments(double flatnessThreshold) { return asLineSegmentsNative(flatnessThreshold); }
    private native Point[] asLineSegmentsNative(double flatnessThreshold);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Intersection
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean contains(Point point) { return containsNative(point); }
    private native boolean containsNative(Point point);

//    public boolean containsNonZero(Point point) { return containsNonZeroNative(point); }
//    private native boolean containsNonZeroNative(Point point);

    public boolean intersects(Path other) { return intersectsNative(other); }
    private native boolean intersectsNative(Path other);

    public void intersections(Path other, IntersectionListener intersectionListener) { intersectionsNative(other, intersectionListener); }
    private native void intersectionsNative(Path other, IntersectionListener intersectionListener);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Evaluation
    //----------------------------------------------------------------------------------------------------------------------------------
//    void HCPathEvaluateLine(HCReal t, HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateQuadraticCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx, HCReal cy, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateCubicCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx0, HCReal cy0, HCReal cx1, HCReal cy1, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathLineLineIntersection(HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal x2, HCReal y2, HCReal x3, HCReal y3, HCReal* t, HCReal* u);
}
