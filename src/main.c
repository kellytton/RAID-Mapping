#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  The purpose of this program is performing RAID mapping.
 *  
 *  'main.c' handles reading input for the queried sector along with various RAID
 *  configurations. The first line of input consists of 5 items: RAID level (T),
 *  number of hard disks (N), chunk size (C) in sectors, number of sectors per disk (S),
 *  and the number of queries (Q).
 *  
 *  For each query, the program outputs which hard disk
 *  and stripe that contain the queried sector, and which other disk has a copy (RAID
 *  levels 1, 01, and 10) or a parity for this sector (RAID levels 4 and 5).
 */

int main(int argc, char* argv[]) {
    // initializations
    int N, C, S, Q;
    char T[3];

    int disk = 0, stripe = 0, block = 0;
    int disk_copy, parity;
    int C_index, C_offset; // for RAID 0

    // read first line of input (5 items): T, N, C, S, Q
    scanf("%2s %d %d %d %d", T, &N, &C, &S, &Q);

    // loop through the queries
    for (int i = 0; i < Q; i++) {
        // scan the queried sector for calculations
        scanf("%d", &block);

        // RAID 0: Striping
        if (strcmp(T, "0") == 0) {
            disk = (block / C) % N;
            C_index = block / C;
            C_offset = block % C;
            stripe = (C_index / N) * C + C_offset;
            printf("%d %d\n", disk, stripe);
        // RAID 1: Mirroring
        } else if (strcmp(T, "1") == 0) {
            disk = 0, disk_copy = 1;
            stripe = block;
            printf("%d %d %d\n", disk, stripe, disk_copy);
        // RAID 01: Mirror of Stripes
        } else if (strcmp(T, "01") == 0) {
            disk = block % (N/2), disk_copy = disk + (N/2);
            stripe = block / (N/2);
            printf("%d %d %d\n", disk, stripe, disk_copy);
        // RAID 10: Stripe of Mirrors
        } else if (strcmp(T, "10") == 0) {
            disk = (block % (N/2)) * 2, disk_copy = disk + 1;
            stripe = block / (N/2);
            printf("%d %d %d\n", disk, stripe, disk_copy);
        // RAID 4: Saving Space with Parity
        } else if (strcmp(T, "4") == 0) {
            disk = block % (N - 1);
            stripe = block / (N - 1);
            parity = N - 1;
            printf("%d %d %d\n", disk, stripe, parity);
        // RAID 5: Rotating Parity
        } else if (strcmp(T, "5") == 0) {
            disk = block % N;
            stripe = block / (N - 1);
            parity = N - 1 - (stripe % N);
            printf("%d %d %d\n", disk, stripe, parity);
        }
    }

    return 0;
}