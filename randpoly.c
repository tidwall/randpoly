#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <math.h>

double *make_polygon(int n, double x, double y, double r, double c, double s) {
    s = s < 0.0 ? 0.0 : s > 1.0 ? 1.0 : s;
    c = c < 0.0 ? 0.0 : c > 1.0 ? 1.0 : c;
    n = n < 3 ? 3 : n;
    double *points = malloc(sizeof(double)*n*2);
    if (!points) return NULL;
    srand(time(NULL));
    double p = 360.0/(double)(n-1);
    double sx;
    double sy;
    for (int i = 0; i < n; i++) {
        double j = (double)i;
        double th = p*j + p*0.5 - p*(s*((double)rand()/(double)RAND_MAX));
        double radians = (M_PI / 180.0) * th;
        double e = r - r*(c*((double)rand()/(double)RAND_MAX));
        double px = x + cos(radians)*e;
        double py = y + sin(radians)*e;
        if (i == n-1) {
            px = sx;
            py = sy;
        }
        points[i*2+0] = px; 
        points[i*2+1] = py;
        if (i == 0) {
            sx = px;
            sy = py;
        } 
    }
    return points;
}

static void usage(FILE *f) {
    fprintf(f, "Usage: randpoly [options...]\n");
    fprintf(f, "  -h, --help                This page\n");
    fprintf(f, "  -n, --npoints <number>    Number of points for the polygon\n");
    fprintf(f, "  -x, --xpos <number>       Center X position, default -111.9575\n");
    fprintf(f, "  -y, --ypos <number>       Center Y position, default 33.4329\n");
    fprintf(f, "  -r, --radius <number>     Radius from center, default 0.002\n");
    fprintf(f, "  -s, --spread <number>     Segment width Randomness (0-1), default 0.7\n");
    fprintf(f, "  -c, --concavity <number>  Radius Randomness (0-1), default 0.7\n");
    fprintf(f, "  -w, --wkt                 Use WKT output, instead of GeoJSON\n");
    fprintf(f, "\n");
    fprintf(f, "Checkout https://github.com/tidwall/randpoly for more info.\n");
    exit(f==stdout?0:1);
}

int main(int argc, char *argv[]) {
    int n = 30;
    double s = 0.7;
    double c = 0.7;
    double x = -111.9575;
    double y = 33.4329;
    double r = 0.002;
    bool w = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            usage(stdout);
        } else if (strcmp(argv[i], "--npoints") == 0 || strcmp(argv[i], "-n") == 0) {
            if (i++ == argc) {
                fprintf(stderr, "randpoly: %s requires an argument\n", argv[i-1]);
                exit(1);
            }
            n = atoi(argv[i]);
        } else if (strcmp(argv[i], "--spread") == 0 || strcmp(argv[i], "-s") == 0) {
            if (i++ == argc) {
                fprintf(stderr, "randpoly: %s requires an argument\n", argv[i-1]);
                exit(1);
            }
            s = atof(argv[i]);
        } else if (strcmp(argv[i], "--radius") == 0 || strcmp(argv[i], "-r") == 0) {
            if (i++ == argc) {
                fprintf(stderr, "randpoly: %s requires an argument\n", argv[i-1]);
                exit(1);
            }
            r = atof(argv[i]);
        } else if (strcmp(argv[i], "--concavity") == 0 || strcmp(argv[i], "-c") == 0) {
            if (i++ == argc) {
                fprintf(stderr, "randpoly: %s requires an argument\n", argv[i-1]);
                exit(1);
            }
            c = atof(argv[i]);
        } else if (strcmp(argv[i], "--xpos") == 0 || strcmp(argv[i], "-x") == 0) {
            if (i++ == argc) {
                fprintf(stderr, "randpoly: %s requires an argument\n", argv[i-1]);
                exit(1);
            }
            x = atof(argv[i]);
        } else if (strcmp(argv[i], "--ypos") == 0 || strcmp(argv[i], "-y") == 0) {
            if (i++ == argc) {
                fprintf(stderr, "randpoly: %s requires an argument\n", argv[i-1]);
                exit(1);
            }
            y = atof(argv[i]);
        } else if (strcmp(argv[i], "--wkt") == 0 || strcmp(argv[i], "-w") == 0) {
            w = true;
        } else {
            fprintf(stderr, "randpoly: bad option: %s\n", argv[i]);
            exit(1);
        }
    }
    double *points = make_polygon(n, x, y, r, c, s);
    assert(points);
    if (w) printf("POLYGON((");
    else printf("{\"type\":\"Polygon\",\"coordinates\":[[");
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(",");
        if (w) printf("%f %f", points[i*2+0], points[i*2+1]);
        else printf("[%f,%f]", points[i*2+0], points[i*2+1]);
    }
    if (w) printf("))\n");
    else printf("]]}\n");
}