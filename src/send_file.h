#ifndef SEND_FILE_H
#define SEND_FILE_H

#include <openssl/sha.h>

const int protocol_id = 0x0d355480;

const int port = 51337;

#define BLESSING_NO 0
#define BLESSING_YES 1

unsigned char *get_sha1(unsigned char* buffer, unsigned long bufsize) {
	unsigned char *outbuf = malloc(SHA_DIGEST_LENGTH);
	SHA1(buffer, bufsize, outbuf);
	return outbuf;
}

void print_sha1(const unsigned char *sha1) {
	char tmpbuf[64];
	int i = 0;
	int offset = 0;
	for (; i < SHA_DIGEST_LENGTH; ++i) {
		sprintf(tmpbuf + offset, "%02x", sha1[i]);
		offset += 2;
	}
	tmpbuf[offset+1] = '\0';
	fprintf(stderr, "%s", tmpbuf);
}

int compare_sha1(const unsigned char* sha1_a, const unsigned char* sha1_b) {
	int i = 0;
	for (; i < SHA_DIGEST_LENGTH; ++i) {
		if (sha1_a[i] != sha1_b[i]) {
			fprintf(stderr, "WARNING! sha1 mismatch!\n");
			return -1;
		}
	}
	printf("sha1 sums match! =)\n\n");
	printf("expected \t");
	print_sha1(sha1_a);
	printf(",\ngot \t\t");
	print_sha1(sha1_b);
	printf(".\n");
	return 1;
}

#endif