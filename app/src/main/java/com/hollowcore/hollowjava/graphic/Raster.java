package com.hollowcore.hollowjava.graphic;

public class Raster {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Definitions
    //----------------------------------------------------------------------------------------------------------------------------------
    public static final int SIZE_MAX = 0x2FFFFFFF;
    public static final Color ROTATING_COLOR = new Color(-1000000.0, 0.0, 0.0, 0.0);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public Raster(int width, int height) { initNative(width, height); }
    private native void initNative(int width, int height);
    private Raster() { reference = 0xDEADBEEF; }

    @Override
    protected void finalize() throws Throwable {
        finalizeNative();
        super.finalize();
    }
    private native void finalizeNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Raster other) { return isEqualNative(other); }
    private native boolean isEqualNative(Raster other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public int getWidth() { return getWidthNative(); }
    private native int getWidthNative();

    public int getHeight()  { return getHeightNative(); }
    private native int getHeightNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Pixel Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Color getPixel(int xIndex, int yIndex) { return getPixelNative(xIndex, yIndex); }
    private native Color getPixelNative(int xIndex, int yIndex);

    public void setPixel(int xIndex, int yIndex, Color pixel) { setPixelNative(xIndex, yIndex, pixel); }
    private native void setPixelNative(int xIndex, int yIndex, Color pixel);

    public Raster getPixels(int startXIndex, int startYIndex, int endXIndex, int endYIndex) { return getPixelsNative(startXIndex, startYIndex, endXIndex, endYIndex); }
    private native Raster getPixelsNative(int startXIndex, int startYIndex, int endXIndex, int endYIndex);

    public void setPixels(int x, int y, Raster pixels) { setPixelsNative(x, y, pixels); }
    private native void setPixelsNative(int x, int y, Raster pixels);

    public void clear() { clearNative(); }
    private native void clearNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Lookup Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Color getPixelNearest(double x, double y) { return getPixelNearestNative(x, y); }
    private native Color getPixelNearestNative(double x, double y);

    public Color getPixelFiltered(double x, double y) { return getPixelFilteredNative(x, y); }
    private native Color getPixelFilteredNative(double x, double y);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Curve Drawing Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public void drawPoint(double x, double y, Color color) { drawPointNative(x, y, color); }
    private native void drawPointNative(double x, double y, Color color);

    public void drawLine(double x0, double y0, double x1, double y1, Color c0, Color c1) { drawLineNative(x0, y0, x1, y1, c0, c1); }
    private native void drawLineNative(double x0, double y0, double x1, double y1, Color c0, Color c1);

    public void drawQuadraticCurve(double x0, double y0, double cx, double cy, double x1, double y1, Color c0, Color c1) { drawQuadraticCurveNative(x0, y0, cx, cy, x1, y1, c0, c1); }
    private native void drawQuadraticCurveNative(double x0, double y0, double cx, double cy, double x1, double y1, Color c0, Color c1);

    public void drawCubicCurve(double x0, double y0, double cx0, double cy0, double cx1, double cy1, double x1, double y1, Color c0, Color c1) { drawCubicCurveNative(x0, y0, cx0, cy0, cx1, cy1, x1, y1, c0, c1); }
    private native void drawCubicCurveNative(double x0, double y0, double cx0, double cy0, double cx1, double cy1, double x1, double y1, Color c0, Color c1);

    public void drawArc(double x0, double y0, double x1, double y1, double xr, double yr, double theta, boolean largeArc, boolean sweep, Color c0, Color c1) { drawArcNative(x0, y0, x1, y1, xr, yr, theta, largeArc, sweep, c0 ,c1); }
    private native void drawArcNative(double x0, double y0, double x1, double y1, double xr, double yr, double theta, boolean largeArc, boolean sweep, Color c0, Color c1);

    public void drawPathData(String pathData, Color color) { drawPathDataNative(pathData, color); }
    private native void drawPathDataNative(String pathData, Color color);

    public void drawPath(Path path, Color color) { drawPathNative(path, color); }
    private native void drawPathNative(Path path, Color color);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Shape Drawing Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public void drawTriangle(double ax, double ay, double bx, double by, double cx, double cy, Color ca, Color cb, Color cc) { drawTriangleNative(ax, ay, bx, by, cx, cy, ca, cb, cc); }
    private native void drawTriangleNative(double ax, double ay, double bx, double by, double cx, double cy, Color ca, Color cb, Color cc);

    public void fillTriangle(double ax, double ay, double bx, double by, double cx, double cy, Color ca, Color cb, Color cc) { fillTriangleNative(ax, ay ,bx, by, cx, cy, ca, cb, cc); }
    private native void fillTriangleNative(double ax, double ay, double bx, double by, double cx, double cy, Color ca, Color cb, Color cc);

    public void fillTexturedTriangle(double ax, double ay, double bx, double by, double cx, double cy, Raster texture, double tax, double tay, double tbx, double tby, double tcx, double tcy) { fillTexturedTriangleNative(ax, ay, bx, by, cx, cy, texture, tax, tay, tbx, tby, tcx, tcy); }
    private native void fillTexturedTriangleNative(double ax, double ay, double bx, double by, double cx, double cy, Raster texture, double tax, double tay, double tbx, double tby, double tcx, double tcy);

    public void drawQuad(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, Color ca, Color cb, Color cc, Color cd) { drawQuadNative(ax, ay, bx, by, cx ,cy, dx, dy, ca, cb, cc, cd); }
    private native void drawQuadNative(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, Color ca, Color cb, Color cc, Color cd);

    public void fillQuad(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, Color ca, Color cb, Color cc, Color cd) { fillQuad(ax, ay, bx, by, cx, cy, dx, dy, ca, cb, cc, cd); }
    private native void fillQuadNative(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, Color ca, Color cb, Color cc, Color cd);

    public void fillTexturedQuad(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, Raster texture, double tax, double tay, double tbx, double tby, double tcx, double tcy, double tdx, double tdy) { fillTexturedQuadNative(ax, ay, bx, by, cx, cy, dx, dy, texture, tax, tay, tbx, tby, tcx, tcy, tdx, tdy); }
    private native void fillTexturedQuadNative(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, Raster texture, double tax, double tay, double tbx, double tby, double tcx, double tcy, double tdx, double tdy);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Data Extraction
    //----------------------------------------------------------------------------------------------------------------------------------
    public int[] asARGB8888() { return asARGB8888Native(); }
    private native int[] asARGB8888Native();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - File Operations
    //----------------------------------------------------------------------------------------------------------------------------------
    public Raster loadPPM(String path) { return loadPPMNative(path); }
    private native Raster loadPPMNative(String path);

    public void savePPM(String path) { savePPM(path, false); }
    public void savePPM(String path, boolean binary) { savePPMNative(path, binary); }
    private native void savePPMNative(String path, boolean binary);

    public Raster loadBMP(String path) { return loadBMPNative(path); }
    private native Raster loadBMPNative(String path);

    public void saveBMP(String path) { saveBMP(path, false); }
    public void saveBMP(String path, boolean reverse) { saveBMPNative(path, reverse); }
    private native void saveBMPNative(String path, boolean reverse);
}
