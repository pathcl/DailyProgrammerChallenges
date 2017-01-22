import java.util.*;
import java.time.Year;

/**
 * This repository contains the challenges posted from the
 * DailyProgrammerChallenges GitHub repository that can be found at
 * https://github.com/FreddieV4/DailyProgrammerChallenges.
 * 
 * Challenge 011 : The program should take three arguments. The first will be a
 * day, the second will be month, and the third will be year. Then, your program
 * should compute the day of the week that date will fall on.
 * 
 * Solution provided by : Ismail A.
 * 
 * @author ieabbas
 */
public class solution {

	// Assume that the input is either a String or an int, not both
	@SuppressWarnings("resource")
	public static void main(String[] args) {
		
		Scanner kb = new Scanner(System.in);
		int day;
		int month;
		int year;

		System.out.println(
				"Welcome to \"Guess that day! The game where YOU give me a year, \nmonth, and date, and I tell YOU what day of the week it is! Ready?\n");
		System.out.println("What year are you looking for?");
		year = kb.nextInt();

		System.out.println("What month are you looking for?");
		month = kb.nextInt();

		System.out.println("What day are you looking for?");
		day = kb.nextInt();

		System.out.println("It was a " + Year.of(year).atMonth(month).atDay(day).getDayOfWeek() + "!");
	}

}
