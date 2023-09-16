import org.openstreetmap.gui.jmapviewer.*;
import org.openstreetmap.gui.jmapviewer.interfaces.MapMarker;
import org.openstreetmap.gui.jmapviewer.interfaces.MapPolygon;
import org.openstreetmap.gui.jmapviewer.interfaces.TileLoader;
import org.openstreetmap.gui.jmapviewer.tilesources.OsmTileSource;

import java.awt.AlphaComposite;
import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.*;

public class Driver {
	
	public static int animationSec;
	public static ArrayList<TripPoint> trip;
	public static BufferedImage arrow;

    public static void main(String[] args) throws FileNotFoundException, IOException {
    	TripPoint.readFile("triplog.csv");
    	TripPoint.h2StopDetection();
    	arrow = ImageIO.read(new File("arrow.png"));
    	
    	arrow = ImageIO.read(new File("arrow.png"));

    	BufferedImage newArrow = new BufferedImage(arrow.getWidth(), arrow.getHeight(), BufferedImage.TYPE_INT_ARGB);
    	Graphics2D g = newArrow.createGraphics();
    	g.setComposite(AlphaComposite.Clear);
    	g.fillRect(0, 0, arrow.getWidth(), arrow.getHeight());
    	g.setComposite(AlphaComposite.Src);
    	g.drawImage(arrow, 0, 0, null);
    	g.dispose();

    	// set up frame
        JFrame frame = new JFrame("Map Viewer");
        frame.setLayout(new BorderLayout());
        
        // set up top panel for input selections
        JPanel topPanel = new JPanel();
        frame.add(topPanel, BorderLayout.NORTH);
        // play button
        JButton play = new JButton("Play");
        // checkbox to enable/disable stops
        JCheckBox includeStops = new JCheckBox("Include Stops");
        // dropbox to pick animation time
        String[] timeList = {"Animation Time", "15", "30", "60", "90"};
        JComboBox<String> animationTime = new JComboBox<String>(timeList);
        animationSec = 0;
        // add all to top panel
        topPanel.add(animationTime);
        topPanel.add(includeStops);
        topPanel.add(play);
        
        // set up mapViewer
        JMapViewer mapViewer = new JMapViewer();
        frame.add(mapViewer);
        frame.setSize(800, 600);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mapViewer.setTileSource(new OsmTileSource.TransportMap());
        
        // add listeners
        play.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>() {
                    @Override
                    protected Void doInBackground() throws Exception {
                    	mapViewer.removeAllMapMarkers(); // remove all markers from the map
                    	mapViewer.removeAllMapPolygons();
                    	if (includeStops.isSelected()) {
                    		trip = TripPoint.getTrip();
                    	}
                    	else {
                    		trip = TripPoint.getMovingTrip();
                    	}
                        plotTrip(animationSec, trip, mapViewer);
                        return null;
                    }
                };
                worker.execute();
            }
        });
        animationTime.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.SELECTED) {
                    Object selectedItem = animationTime.getSelectedItem();
                    if (selectedItem instanceof String) {
                        String selectedString = (String) selectedItem;
                        if (!selectedString.equals("Animation Time")) {
                            animationSec = Integer.parseInt(selectedString);
                            System.out.println("Updated to " + animationSec);
                        }
                    }
                }
            }
        });

        // set the map center and zoom level
        mapViewer.setDisplayPosition(new Coordinate(34.82, -107.99), 6);
        
    }
    
    
    // plot the given trip ArrayList with animation time in seconds
    public static void plotTrip(int seconds, ArrayList<TripPoint> trip, JMapViewer map) throws IOException {
        // amount of time between each point in milliseconds
        long delayTime = (seconds * 1000) / trip.size();

        Coordinate c1;
        Coordinate c2 = null;
        MapMarker marker;
        MapMarker prevMarker = null;
        MapPolygonImpl line;

        for (int i = 0; i < trip.size(); ++i) {
            c1 = new Coordinate(trip.get(i).getLat(), trip.get(i).getLon());

            // Calculate angle between previous and current coordinates
            double angle = 0.0;
            if (i > 0) {v
                c2 = new Coordinate(trip.get(i - 1).getLat(), trip.get(i - 1).getLon());
                double dLat = Math.toRadians(c1.getLat() - c2.getLat());
                double dLon = Math.toRadians(c1.getLon() - c2.getLon());
                double lat1 = Math.toRadians(c2.getLat());
                double lat2 = Math.toRadians(c1.getLat());
                double y = Math.sin(dLon) * Math.cos(lat2);
                double x = Math.cos(lat1) * Math.sin(lat2) - Math.sin(lat1) * Math.cos(lat2) * Math.cos(dLon);
                angle = Math.toDegrees(Math.atan2(y, x));
            }

            // Rotate the arrow image
            BufferedImage rotatedArrow = new BufferedImage(arrow.getWidth(), arrow.getHeight(), BufferedImage.TYPE_INT_ARGB);
            AffineTransform transform = new AffineTransform();
            transform.rotate(Math.toRadians(angle), arrow.getWidth() / 2, arrow.getHeight() / 2);
            Graphics2D g = rotatedArrow.createGraphics();
            g.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
            g.drawImage(arrow, transform, null);
            g.dispose();


            marker = new IconMarker(c1, rotatedArrow);

            map.addMapMarker(marker);
            if (i != 0) {
                line = new MapPolygonImpl(c1, c2, c2);
                line.setColor(Color.RED);
                line.setStroke(new BasicStroke(3));
                map.addMapPolygon(line);
                map.removeMapMarker(prevMarker);
            }
            try {
                Thread.sleep(delayTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            prevMarker = marker;
        }

    }
}
