package Networking;

import java.net.*;
import java.io.*;
import java.util.*;

public class Server {
    private Socket socket = null; // accept connections from clients
    private ServerSocket server = null; // listen to incoming client connections
    private DataInputStream dis = null; // allows us to read client data that they might send

    public Server(int port, int seed) throws IOException {
        server = new ServerSocket(port); // create a new ServerSocket to then listen to client connection(s)
        System.out.printf("Server is running on port [%d].\n", port);

        System.out.printf("Waiting for client to connect...\n");
    }

    public static void main(String[] args) {
        final int port; // port
        final int seed; // seed

        try{
            handleArgs(args);
            port = Integer.parseInt(args[0]);
            seed = Integer.parseInt(args[1]);

            Server server = new Server(port, seed);
        } catch (NumberFormatException e) {
            System.err.printf("Invalid argument - ERROR: {%s}\n", e);
        } catch (IOException e) {
            System.err.printf("Error while creating new server socket - ERROR: {%s}\n", e);
        } catch (Exception e) {
            System.err.println(e);
        } finally {
            
        }
    }

    public static void handleArgs(String[] args) {
        final int port = Integer.parseInt(args[0]); // port
        final int seed = Integer.parseInt(args[1]); // seed

        if (args.length < 2) {
            throw new IllegalArgumentException("Usable format: java Server [port] [seed]");
        }

        if (port > 65535 || port <= 1024) {
            throw new IllegalArgumentException("Port number argument is out of range, must be between 65535 and 1024.");
        }
    }
}
