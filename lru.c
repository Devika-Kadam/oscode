
 #include <stdio.h>
#define MAX_FRAMES 10

int main() {
    int reference_string[100], frames[MAX_FRAMES], page_faults = 0;
    int num_pages, num_frames, i, j, k, lru, counter = 0, found, max;

    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the reference string: ");
    for(i = 0; i < num_pages; i++) {
        scanf("%d", &reference_string[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    for(i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for(i = 0; i < num_pages; i++) {
        found = 0;
        for(j = 0; j < num_frames; j++) {
            if(frames[j] == reference_string[i]) {
                found = 1;
                break;
            }
        }
        if(!found) {
            if(counter < num_frames) {
                frames[counter++] = reference_string[i];
            }
            else {
                max = -1;
                for(j = 0; j < num_frames; j++) {
                    found = 0;
                    for(k = i - 1; k >= 0; k--) {
                        if(frames[j] == reference_string[k]) {
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        lru = j;
                        break;
                    }
                    if(max < (i - k)) {
                        max = i - k;
                        lru = j;
                    }
                }
                frames[lru] = reference_string[i];
            }
            page_faults++;
        }

        printf("\n%d:\t", reference_string[i]);
        for(j = 0; j < num_frames; j++) {
            printf("%d\t", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d", page_faults);
    return 0;
}
