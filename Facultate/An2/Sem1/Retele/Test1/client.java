import java.net.*;
import java.io.*;
import java.nio.charset.Charset;
import java.util.Random;

public class client {

  public static void sendInt(int nr, DataOutputStream sockOut) throws IOException {
    sockOut.writeShort(nr);
    sockOut.flush();
  }

  public static int getInt(DataInputStream sockIn) throws IOException {
    return sockIn.readShort();
  }

  public static void sendString(String str, DataOutputStream sockOut) throws IOException {
    byte[] strBytes = str.getBytes(Charset.forName("ASCII"));
    sockOut.writeShort(strBytes.length);
    sockOut.write(strBytes);
    sockOut.flush();
  }

  public static String getString(DataInputStream sockIn) throws IOException {
    int strLen = sockIn.readShort();
    byte[] strBytes = new byte[strLen];
    sockIn.read(strBytes, 0, strLen);
    return new String(strBytes, Charset.forName("ASCII"));
  }

  public static void sendArray(int[] arr, DataOutputStream sockOut) throws IOException {
    sockOut.writeShort(arr.length);
    for (int j : arr) {
      sockOut.writeShort(j);
    }
    sockOut.flush();
  }

  public static int[] getArray(DataInputStream sockIn) throws IOException {
      int arrLen = sockIn.readShort();
      int[] arr = new int[arrLen];
      for (int i = 0; i < arrLen; i++) {
        arr[i] = sockIn.readShort();
      }
      return arr;
  }

  public static String getStringNumber(DataInputStream sockIn) throws IOException {
    String str = new String();
    int[] arr = getArray(sockIn);
    for (int j : arr) {
      char c = (char) j;
      str += c;
    }
    return str;
  }


  public static void main(String[] args) throws Exception {
    Socket c = new Socket("127.0.0.1", 1234);
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    DataInputStream socketIn = new DataInputStream(c.getInputStream());
    DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

    Random r = new Random();
    int id = getInt(socketIn);
    System.out.println(id);

    while(true) {
      String letter = getString(socketIn);

      System.out.println("Cuvant cu litera " + letter + " :");
      String word = reader.readLine();

      sendString(word, socketOut);

      String randomLetter = String.valueOf((char) (r.nextInt(26) + 'a'));

      sendString(randomLetter, socketOut);

      String uselessWord = getString(socketIn);

      int status = getInt(socketIn);

      if(status == -1)
        break;

    }

    reader.close();
    c.close();
  }
 
}
