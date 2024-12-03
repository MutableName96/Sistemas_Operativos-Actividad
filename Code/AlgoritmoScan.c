#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

/****************************************
 *              Struct's                *
 ****************************************/
typedef struct Request {
    int track;
    bool handled;
} Request;

typedef struct Disk {
    int *tracks;
    int numTracks;
} Disk;

/****************************************
 *        Variables Globales            *
 ****************************************/
Disk disco;
Request *requests;
int numRequests;
int currentTrack;
int direction; // -1 left 1 rigth

/****************************************
 *              Funciones               *
 ****************************************/
void scan();
int findNextRequest();
void initRequests(int *reqTracks, int numReq);
void initDisk(int *tracks, int numTracks);
void handleRequest(int index);

void scan() {
    printf("Iniciando planificación SCAN (Elevator)...\n");
    while (true) {
        int nextRequest = findNextRequest();
        if (nextRequest == -1) {
            if (direction == 1 && currentTrack == disco.numTracks - 1) {
                direction = -1;
            } else if (direction == -1 && currentTrack == 0) {
                direction = 1;
            } else {
                break;
            }
        } else {
            handleRequest(nextRequest);
        }
    }
    printf("Planificación completada.\n");
}

int findNextRequest() {
    int nextIndex = -1;
    int minDistance = __INT_MAX__;
    for (int i = 0; i < numRequests; i++) {
        if (!requests[i].handled) {
            int distance = requests[i].track - currentTrack;
            if ((direction == 1 && distance >= 0) || (direction == -1 && distance <= 0)) {
                distance = abs(distance);
                if (distance < minDistance) {
                    minDistance = distance;
                    nextIndex = i;
                }
            }
        }
    }
    return nextIndex;
}

void initRequests(int *reqTracks, int numReq) {
    requests = (Request *)malloc(numReq * sizeof(Request));
    numRequests = numReq;
    for (int i = 0; i < numReq; i++) {
        requests[i].track = reqTracks[i];
        requests[i].handled = false;
    }
}

void initDisk(int *tracks, int numTracks) {
    disco.tracks = tracks;
    disco.numTracks = numTracks;
}

void handleRequest(int index) {
    printf("Moviendo cabezal de %d a %d\n", currentTrack, requests[index].track);
    currentTrack = requests[index].track;
    requests[index].handled = true;
    printf("Solicitud en pista %d atendida.\n", currentTrack);
}

int main() {
	srand(time(0));
	
    int trackArray[] = {34, 62, 95, 123, 180, 499,1,12,5,2};
    int numTracks = 500;
    int numReq = sizeof(trackArray) / sizeof(trackArray[0]);

    initDisk(NULL, numTracks);
    initRequests(trackArray, numReq);

    currentTrack = rand()%100+1;
    direction = 1;
    scan();

    free(requests);
    return 0;
}
