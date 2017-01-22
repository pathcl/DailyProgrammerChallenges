import java.util.*;
import java.io.*;

/**
 * This repository contains the challenges posted from the
 * DailyProgrammerChallenges GitHub repository that can be found at
 * https://github.com/FreddieV4/DailyProgrammerChallenges.
 * 
 * Challenge 002 : Hello, coders! An important part of programming is being able
 * to apply your programs, so your challenge for today is to create a calculator
 * application that has use in your life. It might be an interest calculator, or
 * it might be something that you can use in the classroom. For example, if you
 * were in physics class, you might want to make a F = M * A calc. Extra credit
 * : allow the calculator to have multiple functions!
 * 
 * Solution provided by : Ismail A.
 */
public class Solution2 {

	@SuppressWarnings("resource")
	public static void main(String[] args) throws Exception {
		// Variables needed for calculation
		Scanner kb = new Scanner(System.in);
		int choice;

		do {
			System.out.println(
					"Enter the the numbers you wish to perform operations upon, separated by a space and when finished press enter:");
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			String[] input = reader.readLine().split(" ");
			int[] intArray = new int[input.length];

			// Parsing and assigning int values
			for (int i = 0; i < input.length; i++) {
				intArray[i] = Integer.parseInt(input[i]);
			}

			System.out.println(
					"Select the operation you wish to perform. Type and enter \"5\" to stop: \n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division");

			choice = kb.nextInt();
			switch (choice) {
			case 1:
				System.out.println("\nThe answer is " + addNum(intArray) + "\n");
				break;
			case 2:
				System.out.println("\nThe answer is " + subtractNum(intArray) + "\n");
				break;
			case 3:
				System.out.println("\nThe answer is " + multiplyNum(intArray) + "\n");
				break;
			case 4:
				System.out.println("\nThe answer is " + divideNum(intArray) + "\n");
				break;
			case 5:
				break;
			default:
				System.out.println("\n" + choice + " isn't an operation" + "\n");
			}
		} while (true);
	}

	public static int addNum(int[] array) {
		int output = 0;
		for (int i = 0; i < array.length; i++) {
			output += array[i];
		}
		return output;
	}

	public static int subtractNum(int[] array) {
		int output = array[0];
		for (int i = 1; i < array.length; i++) {
			output -= array[i];
		}
		return output;
	}

	public static int multiplyNum(int[] array) {
		int output = 1;
		for (int i = 0; i < array.length; i++) {
			output *= array[i];
		}
		return output;
	}

	public static int divideNum(int[] array) {
		int output = array[0];
		for (int i = 1; i < array.length; i++) {
			output /= array[i];
		}
		return output;
	}

}
