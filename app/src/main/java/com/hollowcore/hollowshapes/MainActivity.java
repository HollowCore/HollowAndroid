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

        TextView tv = findViewById(R.id.sample_text);
        Path path = new Path("M1,1L4,2 5,5 3,4Z");
        String pathDescription = "";
        pathDescription += "Count: " + path.getElementCount() + "\n";
        pathDescription += "CurrentPoint: " + path.getCurrentPoint() + "\n";
        pathDescription += "SVGPathData: " + path.asSVGPathData() + "\n";
        Point p = new Point(3,3);
        pathDescription += "Contains(3,3): " + path.containsPoint(new Point(3,3)) + "\n";
        tv.setText(pathDescription);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
