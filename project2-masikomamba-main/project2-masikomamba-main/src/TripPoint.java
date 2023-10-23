

	import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

/**
 * 
 * @author masiko
 *
 */

	public class TripPoint {
		
		private double latitude;
		private double longitude;
		private int time;
		private static ArrayList<TripPoint> trip;
		/**
		 * 
		 * @param time TripPoint takes three parameters one of them being time, all read from the file and added as objects
		 * @param latitude TripPoint takes three parameters one of them being time, all read from the file and added as objects
		 * @param longitude TripPoint takes three parameters one of them being time, all read from the file and added as objects
		 */
		public TripPoint(int time, double latitude, double longitude) {
			this.time = time;
			this.latitude = latitude;
			this.longitude = longitude;
		}
		/**
		 * returns time variable from the object TripPoint
		 * @return time
		 */
		public int getTime() {
			return time;
		}
		/**
		 * returns latitude variable from object TripPoint 
		 * @return latitude
		 */
		public double getLat() {
			return latitude;
		}
		/**
		 * returns longitude variable from object TripPoint
		 * @return longitude
		 */
		public double getLon() {
			return longitude;
		}
		/**
		 * returns a copy of the ArrayList trip
		 * create a new TripPoint ArrayList and have the trip ArrayList added as an element 
		 * @return copy of trip ArrayList
		 */
		public static ArrayList<TripPoint> getTrip() {
			ArrayList<TripPoint> trip2 = new ArrayList<>(trip);
			
			return trip2;
		}
		/**
		 *  Read in the data from the file to the trip ArrayList.
		 *  use BufferedReader to read the data, skip the first line of data because it consists of headers.
		 *  initialize each line of data (Time,Latitude,Longitude) as a TripPoint object. 
		 *  fill the trip ArrayList with the TripPoint objects.
		 * @param filename name of file to be read 
		 * @throws IOException if the file cannot be found or there is no input 
		 */
		public static void readFile(String filename) throws IOException {
	        trip = new ArrayList<>();
	        BufferedReader br = new BufferedReader(new FileReader(filename));
	        String line;
	        br.readLine();
	        while ((line = br.readLine()) != null) {
	            String[] line2 = line.split(",");
	            int time = Integer.parseInt(line2[0]);
	            double lat = Double.parseDouble(line2[1]);
	            double lon = Double.parseDouble(line2[2]);
	            trip.add(new TripPoint(time, lat, lon));
	            System.out.println(trip.get(4));
	        }
	        //System.out.println(trip.size());
	        br.close();
	    }
			/**
			 * returns the total length of the trip took in hours
			 * get the last time variable in the file and divide it by 60. 
			 * time in the file is increasing by 5 for every line so the largest value is the last line
			 *  
			 * @return total time
			 */
		public static double totalTime(){
			double count = 0;
				//for(int i = 1; i< trip.size(); i++) {
					int first = trip.get(trip.size()-1).getTime();
					//int second = first.getTime();
					count =first;
				//}
				return count/60;
			}
		/**
		 * return the Haversine distance between two points in kilometers.
		 *  the Haversine formula is a formula used for calculating the distance between two points on a sphere, such as the Earth.
		 *  it takes in latitudes and longitudes to calculate the distance
		 *  radius of the earth is 6371
		 *  the formula takes in two points and subtracts them from each other.
		 *  The haversine of the central angle (which is d/r), r is the radius of the earth, d is the distance between two points
		 * @param a TripPoint object 
		 * @param b TripPoint object
		 * @return distance between two points
		 */
		public static double haversineDistance(TripPoint a, TripPoint b) {
	        double earthRadius = 6371; 

	        double latDiff = Math.toRadians(b.getLat() - a.getLat());
	        double lonDiff = Math.toRadians(b.getLon() - a.getLon());

	        double aLat = Math.toRadians(a.getLat());
	        double bLat = Math.toRadians(b.getLat());

	        double aHaversine = Math.pow(Math.sin(latDiff / 2), 2) +
	                            Math.pow(Math.sin(lonDiff / 2), 2) *
	                            Math.cos(aLat) * Math.cos(bLat);
	        double cHaversine = 2 * Math.atan2(Math.sqrt(aHaversine), Math.sqrt(1 - aHaversine));

	        return earthRadius * cHaversine;
	    }
		/**
		 * use the haversine distance method to calculate the distance between points
		 * initialize a distance variable.
		 * you will need to use a for loop to iterate through the ArrayList, as you do that you will need to get the points 
		 * after calculating the distances between two points, keep incrementing distance until you reach the end of the ArrayList 
		 * return the total distance of the trip in kilometers
		 * @return total distance traveled
		 */
		 public static double totalDistance() {
		        double distance = 0;
		        for (int i = 0; i < trip.size()-1; i++) {
		            distance += haversineDistance(trip.get(i), trip.get(i + 1));
		        }
		        return distance;
		    }
		 /**
		  * return the average speed between two points in kilometers per hour
		  * speed = distance/time
		  * calculate the distance using the haversineDistance method
		  * for the points inserted as parameters, get the time, remember these are different lines on the file hence have different times
		  * subtract the time from each other to get the time it took to move from one point to another and divide by 60 to calculate in km/hr
		  * use the speed formula
		  * @param a TripPoint object
		  * @param b TripPoint Object
		  * @return average speed between two points.
		  */
		 public static double avgSpeed(TripPoint a, TripPoint b) {
		        double distance = haversineDistance(a, b);
		        int time1 = a.getTime();
		        int time2 = b.getTime();
		        double time = Math.abs(time2 - time1) / 60.0;
		        double speed = distance / time;
		        return speed;
		    }
			 
		 }
		

		
	
/*
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class TripPoint {
    private int time;
    private double lat;
    private double lon;

    private static ArrayList<TripPoint> trip;

    public TripPoint(int time, double lat, double lon) {
        this.time = time;
        this.lat = lat;
        this.lon = lon;
    }

    public int getTime() {
        return time;
    }

    public double getLat() {
        return lat;
    }

    public double getLon() {
        return lon;
    }

    public static ArrayList<TripPoint> getTrip() {
        return new ArrayList<>(trip);
    }

    public static void readFile(String filename) throws IOException {
        trip = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line;
        reader.readLine();
        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(",");
            int time = Integer.parseInt(parts[0]);
            double lat = Double.parseDouble(parts[1]);
            double lon = Double.parseDouble(parts[2]);
            trip.add(new TripPoint(time, lat, lon));
        }
        reader.close();
    }

    public static double haversineDistance(TripPoint a, TripPoint b) {
        double earthRadius = 6371; // kilometers
        double latDiff = Math.toRadians(b.getLat() - a.getLat());
        double lonDiff = Math.toRadians(b.getLon() - a.getLon());
        double aLat = Math.toRadians(a.getLat());
        double bLat = Math.toRadians(b.getLat());

        double haversine = Math.pow(Math.sin(latDiff / 2), 2) +
                Math.pow(Math.sin(lonDiff / 2), 2) *
                        Math.cos(aLat) * Math.cos(bLat);
        double distance = 2 * earthRadius * Math.asin(Math.sqrt(haversine));
        return distance;
    }

    public static double totalDistance() {
        double distance = 0;
        for (int i = 0; i < trip.size() - 1; i++) {
            distance += haversineDistance(trip.get(i), trip.get(i + 1));
        }
        return distance;
    }

    public static double totalTime() {
        int firstTime = trip.get(0).getTime();
        int lastTime = trip.get(trip.size() - 1).getTime();
        return (lastTime - firstTime) / 60.0; // convert minutes to hours
    }

    public static double avgSpeed(TripPoint a, TripPoint b) {
        double distance = haversineDistance(a, b);
        int timeDiff = Math.abs(a.getTime() - b.getTime());
        double time = timeDiff / 3600.0; // convert seconds to hours
        return distance / time;
    }
}

*/
	
	
	
	
	
	
	
	/*public static void readFile(String filename) throws IOException {
		
		BufferedReader br = new BufferedReader(new FileReader(filename));
		br.readLine();
		
		String line;
		
		while((line= br.readLine()) != null ) {
			String[] line2 = line.split(",");
			//String word = line2[0];
			//String word1 = line2[1];
			//String word2= line2[2];
			
			//int time = Integer.parseInt(word);
			//double lat = Double.parseDouble(word1);
			//double lon = Double.parseDouble(word2);
			
		
			TripPoint trip1 = new TripPoint((Integer.parseInt(line2[0])), (Double.parseDouble(line2[1])), (Double.parseDouble(line2[2])));
			//TripPoint trip1 = new TripPoint(time, lat, lon);
			
			trip = new ArrayList<>();
			trip.add(trip1);
			
		}
		br.close();
	}*/