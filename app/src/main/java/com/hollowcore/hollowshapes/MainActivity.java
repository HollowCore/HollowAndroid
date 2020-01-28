package com.hollowcore.hollowshapes;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.hollowcore.hollowjava.graphic.Path;
import com.hollowcore.hollowjava.geometry.Point;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String pathData = "M1,1L4,2 5,5 3,4Z";
        Path path = new Path(pathData);
        path.move(10.0, 10.0);
        path.addLine(40.0, 10.0);
        path.addQuadraticCurve(50.0, 25.0, 40.0, 40.0);
        path.addCubicCurve(30.0, 50.0, 20.0, 50.0, 10.0, 40.0);
        path.closeSubpath();

        String otherPathData = "M0,0L50,100";
        Path other = new Path(otherPathData);

        String pathDescription = "";
        pathDescription += "Count: " + path.getElementCount() + "\n";
        pathDescription += "Elements: \n";
        for (int elementIndex = 0; elementIndex < path.getElementCount(); elementIndex++) {
            Path.Element element = path.getElement(elementIndex);
            pathDescription += " " + element.toString() + "\n";
        }
        pathDescription += "CurrentPoint: " + path.getCurrentPoint() + "\n";
        pathDescription += "SVGPathData: " + path.asSVGPathData() + "\n";
        pathDescription += "Contains(3,3): " + path.contains(new Point(3,3)) + "\n";
        pathDescription += "Contains(30,30): " + path.contains(new Point(30.0,30.0)) + "\n";
        pathDescription += "Contains(100,100): " + path.contains(new Point(100.0,100.0)) + "\n";
        pathDescription += "Intersects(" + otherPathData + "): " + path.intersects(other) + "\n";
        pathDescription += "Intersections(" + otherPathData + "): \n";

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(pathDescription);

        path.intersections(other, new Path.IntersectionListener() {
            @Override
            public boolean intersection(Path path, Path otherPath, Point point) {
                TextView tv = findViewById(R.id.sample_text);
                String pathDescription = tv.getText().toString();
                pathDescription += " x: " + point.getX() + " y: " + point.getY() + "\n";
                tv.setText(pathDescription);
                return true;
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
