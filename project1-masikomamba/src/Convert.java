import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Convert {
	public static void convertFile(String filename) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader(filename));
		br.readLine();
		br.readLine();
		br.readLine();
		String line = br.readLine();
		int time = 0;
		FileWriter file = new FileWriter("triplog.csv");
		PrintWriter write = new PrintWriter(file);
		write.println("Time,Latitude,Longitude");
		while(line!=null) {
			line = line.replaceAll(("[a-z</>=?]*"), "");
			line = line.replaceAll("\"", "");
			line = line.trim();
			//line = line.replaceAll("\\s", "");
			if(line.isBlank()) {
				line = br.readLine();
				continue;
			}
			Scanner scnr = new Scanner(line);
			String latitude = scnr.next();
			latitude = latitude.replaceAll("\\s", "");
			String longitude = scnr.next();
			longitude = longitude.replaceAll("\\s", "");
			scnr.close();
			
			write.println(time + "," + latitude + "," + longitude);
			
			line = br.readLine();
			time+=5;

		}
		br.close();
		write.close();
	}
}
	