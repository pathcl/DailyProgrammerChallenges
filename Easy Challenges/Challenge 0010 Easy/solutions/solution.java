import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/**
 * This repository contains the challenges posted from the
 * DailyProgrammerChallenges GitHub repository that can be found at
 * https://github.com/FreddieV4/DailyProgrammerChallenges.
 * 
 * Challenge 010 : The exercise today asks you to validate a telephone number,
 * as if written on an input form. Telephone numbers can be written as ten
 * digits, or with dashes, spaces, or dots between the three segments, or with
 * the area code parenthesized; both the area code and any white space between
 * segments are optional. Thus, all of the following are valid telephone
 * numbers: 1234567890, 123-456-7890, 123.456.7890, (123)456-7890, (123)
 * 456-7890 (note the white space following the area code), and 456-7890.
 * 
 * The following are not valid telephone numbers: 123-45-6789, 123:4567890, and
 * 123/456-7890.
 * 
 * source: programmingpraxis.com
 * 
 * Solution provided by : Ismail A.
 * 
 * @author ieabbas
 */
public class solution {

	@SuppressWarnings({ "resource" })
	public static void main(String[] args) {
		Scanner kb = new Scanner(System.in);
		String input;

		do {
			System.out.println("Please enter a phone number to be validated.");
			input = kb.nextLine();

			// Check for the invalid conditions first, then everything else
			// should
			// be valid right?
			if (validLength(input) == false || validSymbolNum(input) == false || validIntNum(input) == false) {
				System.out.println("This is not a valid number");
			} else {
				System.out.println("This is a valid number.");
			}
			System.out.println("The symbol used in this number is " + whichSymbol(input) + "\n");
		} while (true);

	}

	/*
	 * This method will check if there is a minimum number of 8 characters
	 * (shortest combination of just numbers), or maximum number of 14
	 * characters (numbers+symbols+whitespace) in the entered phone number. It
	 * will return true if it is valid, and false if otherwise.
	 */
	public static boolean validLength(String input) {
		if (input.length() > 15 || input.length() < 8) {
			return false;
		} else {
			return true;
		}
	}

	/*
	 * This method will check if the entered phone number has an incorrect
	 * amount of symbols. This method also handles the issue of if there are an
	 * appropriate number of integers in the given phone number. If there are
	 * too little, then the number will have more symbols to satisfy the
	 * character length requirement of the validLength() method. If there are
	 * too many, the final else if statement will catch it. It will return true
	 * if the expression satisfies these parameters, and false if otherwise.
	 */
	public static boolean validSymbolNum(String input) {
		int[] symbolNum = { 0, 0 };
		char[] symbols = { '-', '.' };
		int invalidSymbolNum = 0;

		// Check each character of the input against each position of the
		// symbols array
		for (int i = 0; i < input.length(); i++) {
			for (int j = 0; j < symbols.length; j++) {
				if (input.charAt(i) == symbols[j]) {
					symbolNum[j]++;
				}
				// Make sure that if there are non hyphen or period symbols, it
				// is indicated (using ASCII values)
				else if ((input.charAt(i) < 48 || input.charAt(i) > 57) && input.charAt(i) != 46
						&& input.charAt(i) != 45 && input.charAt(i) != 40 && input.charAt(i) != 41) {
					invalidSymbolNum++;
				}
			}
		}

		// A phone number can have a max of 2 hyphens, or 3 periods
		if (symbolNum[0] > 2 || symbolNum[1] > 3) {
			return false;
		}
		// If there are more than one of each, the number is invalid, you can't
		// have both periods and hyphens
		else if (symbolNum[0] > 0 && symbolNum[1] > 0) {
			return false;
		}
		// If there are no symbols at all, there must be a maximum of 10
		// characters (i.e. 1234567890)
		else if (symbolNum[0] == 0 && symbolNum[1] == 0 && input.length() != 10) {
			return false;
		}
		// If there are invalid symbols, anything other than a hyphen or period,
		// the number is invalid
		else if (invalidSymbolNum > 0) {
			return false;
		} else {
			return true;
		}

	}

	/*
	 * This method will check if there is an appropriate number of integer
	 * values within the input
	 */
	@SuppressWarnings("unused")
	public static boolean validIntNum(String input) {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		return true;
	}

	/*
	 * This method will return what symbol is being used in the phone number,
	 * exlusive of parenthesis. An auxiliary method to validIntNum().
	 */
	public static char whichSymbol(String input) {
		int[] symbolNum = { 0, 0, 0 };
		char[] symbols = { '-', '.' };

		// Check each character of the input against each position of the
		// symbols array
		for (int i = 0; i < input.length(); i++) {
			for (int j = 0; j < symbols.length; j++) {
				if (input.charAt(i) == symbols[j]) {
					symbolNum[j]++;
				}
			}
		}

		// It will return an E if neither symbol was used inside of the input
		if (symbolNum[0] >= 1) {
			return '-';
		} else if (symbolNum[1] >= 1) {
			return '.';
		} else {
			return 'E';
		}
	}
}
