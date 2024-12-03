#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/****************************************
 *              Struct's                *
 ****************************************/
typedef struct Request {
    int track;
    bool handled;
} Request;

typedef struct Disk {
    int *tracks;
    int num_tracks;
} Disk;

/****************************************
 *        Variables Globales            *
 ****************************************/
Disk disco;
Request *requests;
int num_requests;
int current_track;
int direction; //-1,1

/****************************************
 *              Funciones               *
 ****************************************/
void scan() {
    while (true) {
        int next_request = findNextRequest();
        if (next_request == -1) break;
        handleRequest(next_request);
    }
} 
int findNextRequest() {
    int next_index = -1;
    int min_distance = __INT_MAX__;
    for (int i = 0; i < num_requests; i++) {
        if (!requests[i].handled) {
            int distance = requests[i].track - current_track;
            if ((direction == 1 && distance >= 0) || (direction == -1 && distance <= 0)) {
                distance = abs(distance);
                if (distance < min_distance) {
                    min_distance = distance;
                    next_index = i;
                }
            }
        }
    }
    
    return next_index;
}

void initRequests(int *req_tracks, int num_req) {
    requests = (Request *)malloc(num_req * sizeof(Request));
    num_requests = num_req;
    for (int i = 0; i < num_req; i++) {
        requests[i].track = req_tracks[i];
        requests[i].handled = false;
    }
}

void initDisk(int *tracks, int num_tracks) {
    disco.tracks = tracks;
    disco.num_tracks = num_tracks;
}


void handleRequest(int index) {
    
}

int main() {
   
    return 0;
}
