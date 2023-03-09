import java.net.*;
import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class clientJ {

  public static void sendInt(int nr, DataOutputStream sockOut) throws IOException {
    sockOut.writeShort(nr);
    sockOut.flush();
  }

  public static int getInt(DataInputStream sockIn) throws IOException {
    int nr = sockIn.readShort();
    return nr;
  }

  public static void sendString(String str, DataOutputStream sockOut) throws IOException {
    byte[] strBytes = str.getBytes(StandardCharsets.US_ASCII);
    sockOut.writeShort(strBytes.length);
    sockOut.write(strBytes);
    sockOut.flush();
  }

  public static String getString(DataInputStream sockIn) throws IOException {
    int strLen = sockIn.readShort();
    byte[] strBytes = new byte[strLen];
    sockIn.read(strBytes, 0, strLen);
    String str = new String(strBytes, Charset.forName("ASCII"));
    return str;
  }

  public static void sendArray(int[] arr, DataOutputStream sockOut) throws IOException {
    sockOut.writeShort(arr.length);
    for (int i = 0; i < arr.length; i++) {
      sockOut.writeShort(arr[i]);
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
    for (int i = 0; i < arr.length; i++) {
      char c = (char)arr[i];
      str += c;
    }
    return str;
  }


  public static void main(String args[]) throws Exception {
    Socket c = new Socket("127.0.0.1", 1234);
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    DataInputStream socketIn = new DataInputStream(c.getInputStream());
    DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());

    String word = reader.readLine();
    sendString(word, socketOut);
    String start = getString(socketIn);
    System.out.println(start);

    int guess, tries;

    while (true){
      guess = Integer.parseInt(reader.readLine());
      sendInt(guess, socketOut);

      String response = getString(socketIn);
      System.out.println(response);

      if(response.equals("You win!")){
        tries = getInt(socketIn);
        System.out.println("You guessed the number in " + tries + " tries.");
        break;

      } else if (response.equals("Wrong\nDo you want to continue?(y/n)")){
        String answer = reader.readLine();
        sendString(answer, socketOut);
        if (answer.equals("n")){
          tries = getInt(socketIn);
          System.out.println("You tried to guessed the number in " + tries + " tries.");
          break;
        }
      } else if (response.equals("You lost!")){
        break;
      }
    }



    reader.close();
    c.close();
  }
 
}
