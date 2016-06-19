import java.util.*;

/**
 * This package conatins the challenges posted from the
 * DailyProgrammerChallenges GitHub repository that can be found at
 * https://github.com/FreddieV4/DailyProgrammerChallenges.
 * 
 * Challenge 001 : create a program that will ask the users name, age, and
 * reddit username. have it tell them the information back, in the format:
 * "your name is (blank), you are (blank) years old, and your username is (blank)"
 * for extra credit, have the program log this information in a file to be
 * accessed later.
 * 
 * Solution provided by : Ismail A.
 */
public class Solution2 {

	@SuppressWarnings({ "resource" })
	public static void main(String[] args) {
		String name;
		String age;
		String userName;

		// Simple scanner to receive input
		Scanner kb = new Scanner(System.in);

		// Cases for invalid input should be written usually to optimize the
		// user experience

		System.out.println("What is your name?");
		name = kb.nextLine();

		System.out.println("How old are you?");
		age = kb.nextLine();

		System.out.println("What is your Reddit username?");
		userName = kb.nextLine();

		System.out.println(
				"Your name is " + name + ", you are " + age + ", and your Reddit user name is \"" + userName + "\".");
	}

}
