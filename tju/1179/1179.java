import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	public static BigInteger solve (int n) {
		BigInteger result = new BigInteger("1");
		for (int i = n + 2; i <= 2 * n; i ++) {
			result = result.multiply (new BigInteger (String.valueOf(i)));
		}

		for (int i = 2; i <= n ; i++) {
			result = result.divide(new BigInteger (String.valueOf(i)));
		}

		return result;
	}

	public static void main (String[] args) {
		Scanner scanner = new Scanner (System.in);
		BigInteger[] x = new BigInteger[102];
		
		x[0] = new BigInteger ("0");
		for (int n = 1; n < 101; n++) {
			x[n] = solve (n);
		}

	
		int n = scanner.nextInt ();
		while (n != -1) {
			System.out.println (x[n].toString());
			n = scanner.nextInt ();
		}
	}
}
