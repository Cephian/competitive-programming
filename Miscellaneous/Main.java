import java.util.*;
import java.math.*;
import java.io.*;

class FastReader { 
	BufferedReader br; 
	StringTokenizer st; 

	public FastReader() { 
		br = new BufferedReader(new InputStreamReader(System.in)); 
	} 

	String next() throws Exception{ 
		if (st == null || !st.hasMoreElements())
			st = new StringTokenizer(br.readLine()); 
		return st.nextToken(); 
	} 
	int nextInt() throws Exception { return Integer.parseInt(next()); } 
	long nextLong() throws Exception{ return Long.parseLong(next()); } 
	double nextDouble() throws Exception { return Double.parseDouble(next()); } 
	String nextLine() throws Exception { return br.readLine(); } 
} 


class FastWriter {
	private final BufferedWriter bw;
	public FastWriter() {
		bw = new BufferedWriter(new OutputStreamWriter(System.out));
	}
	public void print(Object object) throws Exception {
		bw.append("" + object);
	}
	public void close()throws IOException
	{
	    bw.close();
	}
}

public class Main {
	public static void main(String[] args) throws Exception {
		FastReader fr = new FastReader();
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

		int n = fr.nextInt();
		String s = fr.next(), t = fr.next();

		BigInteger two = new BigInteger("2");
		BigInteger three = two.add(BigInteger.ONE);
		// other BigInteger methods: add(), subtract(), mod(), pow(int), divide()
		int five = (two.add(three)).intValue();
		if(two.compareTo(three) < 0) {
			bw.append("saw " + s + "\n");
			bw.append("saw " + t + "\n");
		}
		bw.append(two + "\n");

		ArrayList<Integer> arr = new ArrayList<>();
		arr.add(5);
		arr.add(1);
		Collections.sort(arr);

		bw.close(); // flushes the buffer
	}
}

class Pair implements Comparable<Pair>{
	int a, b;
	@Override
	public int compareTo(Pair x) {
		if(a != x.a)
			return Integer.compare(x);
		return Integer.compare(b);
	}
}
