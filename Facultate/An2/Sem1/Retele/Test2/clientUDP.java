import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class clientUDP {

    public static void sendData(String data, DatagramSocket socket, InetAddress address, int port) throws IOException {

        byte[] buf = data.getBytes(StandardCharsets.US_ASCII);
        DatagramPacket packet = new DatagramPacket(buf, buf.length, address, port);
        socket.send(packet);
    }

    public static String getData(DatagramSocket socket) throws IOException {

        byte[] buf = new byte[512];
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        socket.receive(packet);
        String received = new String(packet.getData(), StandardCharsets.US_ASCII);
        return received.split("\0")[0];

    }


    public static void main(String[] args) throws Exception
    {
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        DatagramSocket clientSocket = new DatagramSocket();
        InetAddress IPAddress = InetAddress.getByName(args[0]);
        //InetAddress.getByName("localhost");
        //127.0.0.1

        System.out.println("Introduceti nr separate prin spatiu");
        String numbers = inFromUser.readLine();
        sendData(numbers, clientSocket, IPAddress, Integer.parseInt(args[1]));

        int nr = Integer.parseInt(getData(clientSocket));
        int newPort = Integer.parseInt(getData(clientSocket));

        System.out.println("Numbers of clients: " + nr);
        System.out.println("Port: "+newPort);


        clientSocket.close();
    }
}