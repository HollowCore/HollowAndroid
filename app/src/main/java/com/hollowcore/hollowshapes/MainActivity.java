package com.hollowcore.hollowshapes;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.hollowcore.hollowjava.container.HollowList;
import com.hollowcore.hollowjava.container.HollowMap;
import com.hollowcore.hollowjava.container.HollowSet;
import com.hollowcore.hollowjava.data.HollowNumber;
import com.hollowcore.hollowjava.data.HollowString;
import com.hollowcore.hollowjava.graphic.Path;
import com.hollowcore.hollowjava.geometry.Point;
import com.hollowcore.hollowjava.graphic.Raster;

import java.util.List;
import java.util.Map;
import java.util.Set;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String description = "";

        // Create sample list collection
        List<HollowNumber> list = new HollowList(8);
        list.add(new HollowNumber(0));
        list.add(new HollowNumber(1));
        list.add(new HollowNumber(2));
        list.add(new HollowNumber(3));
        list.add(new HollowNumber(4));
        description += "List Count: " + list.size() + "\n";
        description += "List Contains(2): " + list.contains(new HollowNumber(2)) + "\n";
        list.remove(new HollowNumber(2));
        description += "List Post-Delete Count: " + list.size() + "\n";
        description += "List Post-Delete Contains(2): " + list.contains(new HollowNumber(2)) + "\n";
        description += "List Contents: \n";
        for (HollowNumber o : list) {
            description += " " + o.asInteger() + "\n";
        }
        description += "\n";

        // Create sample set collection
        Set<HollowNumber> set = new HollowSet(8);
        set.add(new HollowNumber(0));
        set.add(new HollowNumber(1));
        set.add(new HollowNumber(2));
        set.add(new HollowNumber(3));
        set.add(new HollowNumber(4));
        description += "Set Count: " + set.size() + "\n";
        description += "Set Contains(2): " + set.contains(new HollowNumber(2)) + "\n";
        set.remove(new HollowNumber(2));
        description += "Set Post-Delete Count: " + set.size() + "\n";
        description += "Set Post-Delete Contains(2): " + set.contains(new HollowNumber(2)) + "\n";
        description += "Set Contents: \n";
        for (HollowNumber o : set) {
            description += " " + o.asInteger() + "\n";
        }
        description += "\n";

        // Create sample map collection
        Map<HollowNumber, HollowString> map = new HollowMap(8);
        map.put(new HollowNumber(0), new HollowString("0"));
        map.put(new HollowNumber(1), new HollowString("1"));
        map.put(new HollowNumber(2), new HollowString("2"));
        map.put(new HollowNumber(3), new HollowString("3"));
        map.put(new HollowNumber(4), new HollowString("4"));
        description += "Map Count: " + map.size() + "\n";
        description += "Map For(2): " + map.get(new HollowNumber(2)).asInteger() + "\n";
        map.remove(new HollowNumber(2));
        description += "Map Post-Delete Count: " + map.size() + "\n";
        description += "Map Post-Delete For(2): " + map.get(new HollowNumber(2)) + "\n";
        description += "Map Contents: \n";
        for (Map.Entry<HollowNumber, HollowString> e : map.entrySet()) {
            description += " " + e.getKey() + ": " + e.getValue() + "\n";
        }
        description += "\n";

        // Create sample paths
        String pathData = "M1,1L4,2 5,5 3,4Z";
        Path path = new Path(pathData);
        path.move(10.0, 10.0);
        path.addLine(40.0, 10.0);
        path.addQuadraticCurve(50.0, 25.0, 40.0, 40.0);
        path.addCubicCurve(30.0, 50.0, 20.0, 50.0, 10.0, 40.0);
        path.closeSubpath();

        String otherPathData = "M0,0L50,100";
        Path other = new Path(otherPathData);

        description += "Path Count: " + path.getElementCount() + "\n";
        description += "Path Elements: \n";
        for (int elementIndex = 0; elementIndex < path.getElementCount(); elementIndex++) {
            Path.Element element = path.getElement(elementIndex);
            description += " " + element.toString() + "\n";
        }
        description += "Path CurrentPoint: " + path.getCurrentPoint() + "\n";
        description += "Path SVGPathData: " + path.asSVGPathData() + "\n";
        description += "Path LineSegmentCount: " + path.asLineSegments().length / 2 + "\n";
        description += "Path Bounds: " + path.getBounds() + "\n";
        description += "Path Contains(3,3): " + path.contains(new Point(3,3)) + "\n";
        description += "Path Contains(30,30): " + path.contains(new Point(30.0,30.0)) + "\n";
        description += "Path Contains(100,100): " + path.contains(new Point(100.0,100.0)) + "\n";
        description += "Path Intersects(" + otherPathData + "): " + path.intersects(other) + "\n";
        description += "Path Intersections(" + otherPathData + "): \n";

        // Apply the path description to the sample label
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(description);

        // Add path intersections to the description
        path.intersections(other, new Path.IntersectionListener() {
            @Override
            public boolean intersection(Path path, Path otherPath, Point point) {
                TextView tv = findViewById(R.id.sample_text);
                String description = tv.getText().toString();
                description += " x: " + point.getX() + " y: " + point.getY() + "\n";
                tv.setText(description);
                return true;
            }
        });

        // Create sample raster by drawing a complex path into it
        String dinosaur = "m 134.51827,42.745763 c -16.01255,0 -29.04048,13.025256 -29.04048,29.035206 0,3.45164 2.79845,6.25017 6.24999,6.25017 3.45153,0 6.24999,-2.79853 6.24999,-6.25017 0,-9.115845 7.41881,-16.534865 16.5405,-16.534865 9.1217,0 16.54052,7.41902 16.54052,16.534865 0,3.45164 2.79845,6.25017 6.24999,6.25017 3.45153,0 6.24999,-2.79853 6.24999,-6.25017 0,-16.00995 -13.02794,-29.035206 -29.0405,-29.035206 z M 495.72086,350.60935 c -3.53088,-1.17497 -9.09728,-1.26652 -19.25962,-1.26652 -0.49745,-0.003 -1.01013,-0.003 -1.53808,0 -39.42867,0 -81.56424,-2.84431 -84.32913,-35.79504 -11.33422,-135.05921 -116.9829,-147.15671 -161.75824,-146.02447 -10.50414,0.14955 -20.07138,-4.68153 -26.00094,-13.18701 -5.93567,-8.51463 -7.15636,-18.9031 -3.44543,-28.30887 0.4028,-0.84231 9.96703,-20.87154 12.90587,-44.819331 C 216.36328,48.06512 205.71876,23.735847 181.51835,10.847922 152.49311,-4.6035481 121.14854,-3.5323515 90.881248,13.95775 86.559958,16.451099 81.701568,17.50704 76.922519,17.073678 61.660699,15.624052 33.441124,15.633208 15.637188,31.844586 5.2612254,41.28698 0,54.650994 0,71.564289 c 0,17.10862 5.7861249,31.311891 17.199686,42.210011 20.364358,19.45243 53.131048,22.86744 68.170092,23.36184 -7.434074,38.31281 -7.208249,70.08552 -7.192984,71.44359 0,32.52881 7.423389,82.77127 22.937366,123.33099 L 89.694108,437.47999 c -0.43945,6.22271 1.751715,12.41184 6.00586,16.97739 4.254145,4.56556 10.275252,7.18403 16.516092,7.18403 h 11.01111 l -0.9739,14.20022 c -0.4364,6.22576 1.75476,12.41489 6.00891,16.97739 4.25415,4.5625 10.2722,7.18098 16.51304,7.18098 h 46.24018 c 6.24084,0 12.2589,-2.61848 16.51305,-7.18403 4.25414,-4.56251 6.4453,-10.75164 6.01805,-16.72104 l -2.31323,-78.71002 c 7.28569,1.85857 15.16913,2.94808 23.24903,3.3513 l 0.8812,37.49759 c 0.9491,12.90623 11.83165,23.40761 24.26145,23.40761 h 9.24528 l 0.44705,13.77601 C 270.7852,491.26868 280.47146,500 296.58778,500 h 33.12985 c 8.62731,0 15.61887,-2.71004 20.21786,-7.84018 4.29382,-4.78529 6.12488,-11.31317 5.3009,-18.84511 l -5.1239,-49.2262 c 68.27996,23.81962 128.78099,-23.17567 149.24605,-64.79058 0.79655,-1.62052 0.8545,-3.50656 0.15565,-5.17286 -0.69579,-1.66326 -2.07824,-2.94808 -3.79333,-3.51572 z m -383.5048,98.53172 c -2.82593,0 -5.44433,-1.13833 -7.37304,-3.20748 -1.92566,-2.0661 -2.87781,-4.75782 -2.70081,-7.34273 l 9.08813,-83.98627 c 5.21583,9.92077 11.06757,18.67612 17.5781,25.66254 l -4.72373,68.87394 z m 147.40889,0 c -5.8197,0 -11.33422,-5.52383 -11.78283,-11.51154 l -0.85907,-36.83534 c 6.66847,-0.28345 13.34876,-1.02503 19.83793,-2.28926 l 1.64337,50.63614 z m 85.74819,-40.3728 c -2.03552,-0.90639 -4.40979,-0.66225 -6.21338,0.647 -1.80969,1.31229 -2.78014,3.4852 -2.54821,5.70694 l 6.19506,59.52004 c 0.4364,3.98876 -0.296,7.07417 -2.17895,9.17383 -2.72827,3.04574 -7.44018,3.68358 -10.91002,3.68358 h -33.12985 c -9.65881,0 -13.95262,-3.83617 -14.80101,-12.86046 l -2.71911,-84.11178 c -0.0613,-1.9013 -0.98572,-3.67136 -2.5116,-4.8097 -1.08947,-0.81179 -2.40173,-1.23905 -3.73534,-1.23905 -0.531,0 -1.06507,0.0671 -1.58692,0.2045 -21.36532,5.60929 -46.02655,4.95619 -64.3737,-1.69377 -1.94092,-0.70497 -4.10766,-0.40285 -5.79223,0.80874 -1.67846,1.21463 -2.64587,3.18001 -2.58483,5.24916 l 2.58178,87.67023 c 0.19835,2.8199 -0.75378,5.50857 -2.67944,7.57772 -1.92566,2.06607 -4.54406,3.2044 -7.36999,3.2044 h -46.24018 c -2.82592,0 -5.44433,-1.13833 -7.36999,-3.20443 -1.92871,-2.0661 -2.88085,-4.75782 -2.68249,-7.58993 l 6.74743,-98.35472 c 0.1251,-1.80669 -0.54019,-3.57675 -1.8219,-4.85548 -10.29509,-10.258 -19.01624,-26.00664 -26.14056,-44.22536 -0.04,-0.1453 -0.10415,-0.2724 -0.15415,-0.4135 -14.885312,-38.27199 -22.676822,-87.41654 -22.676822,-120.33751 -0.003,-0.35705 -0.2441,-36.12159 8.46252,-76.29297 0.40895,-1.8952 -0.08545,-3.87279 -1.33362,-5.35598 -1.251225,-1.48014 -3.091425,-2.24921 -5.056755,-2.21259 -0.4303,0.0245 -44.314526,1.70599 -66.943288,-19.94683 C 16.851762,96.143829 12.49996,85.303689 12.49996,71.564299 c 0,-13.24804 3.884883,-23.502225 11.550894,-30.475677 14.251689,-12.973377 38.510085,-12.811629 51.693665,-11.569527 7.406604,0.717182 14.813214,-0.933869 21.386694,-4.73646 26.342737,-15.2195321 53.497247,-16.2235841 78.512477,-2.899247 47.17707,25.116651 12.83568,97.982392 12.48473,98.714832 -0.0641,0.13425 -0.21055,0.48835 -0.2655,0.62563 -5.29784,13.37011 -3.53698,28.4218 4.71801,40.26294 8.33434,11.95711 21.85362,18.93972 36.55697,18.53077 51.29694,-1.15054 138.93111,14.59086 148.99885,134.57397 3.96728,47.30048 64.54155,47.19061 97.21363,47.25165 2.74048,-0.01 5.67626,-0.003 8.28857,0.0395 -22.85764,36.89981 -77.94791,73.78435 -138.26583,46.88543 z";
        Path dinosaurPath = new Path(dinosaur);
        Raster raster = new Raster(512, 512);
        raster.drawPath(dinosaurPath, Raster.ROTATING_COLOR);

        // Convert the raster to a bitmap
        int[] pixels = raster.asARGB8888();
        Bitmap b = Bitmap.createBitmap(pixels, raster.getWidth(), raster.getHeight(), Bitmap.Config.ARGB_8888);

        // Apply the raster to the sample image view
        ImageView iv = findViewById(R.id.image_view);
        iv.setImageBitmap(b);
    }
}
