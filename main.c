#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int search_windows(int* windows, int len, int id);

int search_windows(int *windows, int len, int id) {

for (int i = 0; i < len; i++) {
    if (windows[i] == id) return i; // returns index of ID to be switched to
}
return -1;

}


int main() {

char command[7]; // Open, close, switch windows
int id; // Window ID number
int current_window; // Window ID currently looking at
int open_windows = 1; // Number of windows opened in total
int * windows = NULL; // Ordered list of all windows
int * add_windows = NULL; // Reallocated windows

scanf("%s %d", command, &id);

// allocate first open window assuming valid inputs
current_window = id; // we are looking at the window we just opened
add_windows = realloc(windows, sizeof(int)); // realloc for first window
if( add_windows == NULL) { // will assert if 1 item left so above takes care of this
    free(windows);
    return 1;
}
windows = add_windows;
windows[0] = id; // add to total windows
printf("%d\n", id); // print first window

while (open_windows > 0) {// always take commands if window is open
    scanf("%s %d", command, &id); // get new command

    if (strcmp(command, "open") == 0) {
        // create new window with window id
        add_windows = (int*)realloc(windows, (open_windows + 1) * sizeof(int));
        if( add_windows == NULL) { // will assert if 1 item left so above takes care of this
                free(windows);
                return 1;
        }

        // currently looking at newly created window
        windows = add_windows;
        windows[open_windows] = id; // add new ID to right of last opened
        current_window = id;
        open_windows += 1; // we added a window
    } 
    else if (strcmp(command, "switch") == 0) {
        // no new windows are added to the ordered list
        // currently looking at different window in the ordered list
        if (id != windows[open_windows - 1]) {
        
        int stop = search_windows(windows, open_windows, id); // where id is found

        for (int i = stop; i < open_windows - 1; i++) {
            windows[i] = windows[i + 1]; // move all indexes to the left after found ID
        }
        windows[open_windows - 1] = id; // tack switched ID onto end
        }
        current_window = id;
    }
    else if (strcmp(command, "close") == 0) { // command is close
        // if close is different id from current looking, stay on current
        // and delete closed id... current stays same
        if (current_window != id) {
            int stop = search_windows(windows, open_windows, id);

            int to_close = windows[stop];
            for (int i = stop; i < open_windows - 1; i++) {
                windows[i] = windows[i + 1]; // move all indexes to the left after found ID
            }

            windows[open_windows - 1] = to_close; // tack closed ID onto end

            add_windows = (int *)realloc(windows, (open_windows - 1) * sizeof(int));
            if( add_windows == NULL) { // will assert if 1 item left so above takes care of this
                free(windows);
                return 1;
            }
            windows = add_windows;
            open_windows -= 1;
        }
        // if close is same id as current looking, delete id, current is
        // is now most previous opened or switched to in list
        else { // window to be closed should be last in array then
            if (open_windows == 1) { // only one item left
                windows = NULL;
                free(add_windows); // in case it holds previous memory alloc
                free(windows);
                return 0;
            }
            
            add_windows = (int *)realloc(windows, (open_windows - 1) * sizeof(int));
            if(add_windows == NULL) { // will assert if 1 item left so above takes care of this
                free(windows);
                return 1;
            } 
            windows = add_windows;
            current_window = windows[open_windows - 2];
            open_windows -= 1;
        }
    }
    
    // print current open window
    // for (int j=0;j<open_windows;j++) {
    //     printf("[%d ", windows[j]);
    // }
    // printf("] OW: %d\n", open_windows);
    if (open_windows > 0) printf("%d\n", current_window);
}
    free(windows); // free in case
    free(add_windows);
    return 0;
}