import java.util.*;

@SuppressWarnings("unused")
public class IPv4_Addressing {
    public static void main(String[] args) {
        int i, interesting_octet, cidr_mask, subnet_mask = 0, dec_mask = 128, resx;
        int[] ip_address = new int[4], network_address = new int[4], 
            broadcast_address = new int[4], first_host = new int[4], 
            last_host = new int[4];

        try {
            String ip = args[0]; // IP should be in the form of xxx.xxx.xxx.xxx/yy
            String[] temp = ip.split("[./]");
            cidr_mask = Integer.parseInt(temp[4]);

            for (i = 0; i < 4; i++) {
                ip_address[i] = Integer.parseInt(temp[i]);
            }
            resx = cidr_mask % 8;

            if (cidr_mask < 9)
                interesting_octet = 0;
            else if (cidr_mask < 17)
                interesting_octet = 1;
            else if (cidr_mask < 25)
                interesting_octet = 2;
            else
                interesting_octet = 3;

            if (resx == 0) subnet_mask = 255;

            for (i = 0; i < resx; i++) {
                subnet_mask += dec_mask;
                dec_mask /= 2;
            }

            // calculating our network address
            for (i = 0; i < 4; i++) {
                if (i > interesting_octet) {
                    network_address[i] = 0;
                } else if (i < interesting_octet) {
                    network_address[i] = ip_address[i];
                } else { // the interesting octet's calculation
                    network_address[i] = ip_address[i] & subnet_mask;
                }
            }

            // calculating our broadcast address
            for (i = 0; i < 4; i++) {
                if (i > interesting_octet) {
                    broadcast_address[i] = 255;
                } else if (i < interesting_octet) {
                    broadcast_address[i] = ip_address[i];
                } else {
                    broadcast_address[i] = network_address[i] + ((256 - subnet_mask) - 1);
                }
            }

            first_host = network_address.clone();
            first_host[3] += 1;
            last_host = broadcast_address.clone();
            last_host[3] -= 1;

            System.out.printf("\nNetwork Address: %s\n", convertToString(network_address));
            System.out.printf("Broadcast Address: %s\n", convertToString(broadcast_address));
            System.out.printf("First Valid Host: %s\n", convertToString(first_host));
            System.out.printf("Last Valid Host: %s\n\n", convertToString(last_host));
        } catch (NumberFormatException e) {
            System.err.printf("Please enter integer values only...\nERROR {%s}\n", e);
        } catch (Exception e) {
            System.err.printf("Program error has occurred...\nERROR {%s}\n", e);
            System.err.printf("Program arguments: IPv4 address w/ CIDR notation => [xxx.xxx.xxx.xxx/yy]\n");
        }
    }

    public static String convertToString(int[] arr) {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < 4; i++)
            sb.append(String.format("%d%s", arr[i], (i != 3) ? "." : ""));

        return sb.toString();
    }
}
