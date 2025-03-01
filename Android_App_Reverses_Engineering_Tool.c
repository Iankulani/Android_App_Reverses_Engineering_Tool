#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read file contents
void read_file(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Error opening file: %s\n", file_path);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    printf("File read successfully: %s\n", file_path);

    // Basic binary analysis (looking for common patterns)
    printf("Searching for suspicious strings or patterns...\n");

    // Example pattern: searching for a string that may indicate malicious behavior
    for (long i = 0; i < file_size - 4; i++) {
        if (memcmp(buffer + i, "exec", 4) == 0) {
            printf("Suspicious pattern 'exec' found at offset %ld\n", i);
        }
    }

    free(buffer);
}

// Function to extract basic APK metadata
void analyze_apk(const char *apk_path) {
    // For simplicity, let's assume we just check if the file is a ZIP archive (APK is a ZIP)
    FILE *apk_file = fopen(apk_path, "rb");
    if (apk_file == NULL) {
        printf("Error opening APK file: %s\n", apk_path);
        return;
    }

    // Checking for the APK magic number (ZIP format)
    unsigned char buffer[4];
    fread(buffer, 1, 4, apk_file);
    fclose(apk_file);

    if (buffer[0] == 0x50 && buffer[1] == 0x4B && buffer[2] == 0x03 && buffer[3] == 0x04) {
        printf("Valid APK file detected.\n");
    } else {
        printf("This does not appear to be a valid APK file.\n");
        return;
    }

    // You can extend this to parse APK's "AndroidManifest.xml" or other files
}

// Main function
int main() {
    char file_path[256];
    printf("===================== ANDROID REVERSE ENGEERING TOOL ====================\n\n");

    // Prompt user for input
    printf("Enter the path to the APK or binary file to analyze:");
    scanf("%s", file_path);

    // Checking file type
    if (strstr(file_path, ".apk") != NULL) {
        printf("Analyzing APK file...\n");
        analyze_apk(file_path);
    } else {
        printf("Analyzing binary file...\n");
        read_file(file_path);
    }

    return 0;
}
