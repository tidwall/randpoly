# randpoly

Make random convex polygons.

<p>
<img src="/assets/example1.png" border="0" width="200" height="200">
<img src="/assets/example2.png" border="0" width="200" height="200">
<img src="/assets/example3.png" border="0" width="200" height="200">
<img src="/assets/example4.png" border="0" width="200" height="200">
</p>

## Build and run

```sh
$ make
$ ./randpoly
```
```
{"type":"Polygon","coordinates":[[[-111.956805,33.432941],[-111.956316,33.433117],[-111.955871,33.433695],[-111.956744,33.433502],[-111.956909,33.433615],[-111.956952,33.434114],[-111.957080,33.434359],[-111.957437,33.434594],[-111.957885,33.434459],[-111.957807,33.433480],[-111.958368,33.434296],[-111.958350,33.433575],[-111.958703,33.433555],[-111.959073,33.433351],[-111.958877,33.432942],[-111.958161,33.432816],[-111.958656,33.432545],[-111.958766,33.432174],[-111.958605,33.431827],[-111.958419,33.431610],[-111.958020,33.431445],[-111.957722,33.431762],[-111.957369,33.431109],[-111.957065,33.431775],[-111.957085,33.432191],[-111.957083,33.432466],[-111.956878,33.432419],[-111.956069,33.432184],[-111.956313,33.432670],[-111.956805,33.432941]]]}
```

## For WKT

```sh
$ ./randpoly -w
```
```
POLYGON((-111.956599 33.432953,-111.956111 33.433294,-111.955862 33.433724,-111.955998 33.434161,-111.956369 33.434526,-111.956798 33.434259,-111.957133 33.434224,-111.957451 33.433534,-111.957820 33.434591,-111.958177 33.434338,-111.958275 33.433871,-111.958716 33.433934,-111.959102 33.433679,-111.959306 33.433375,-111.959211 33.433126,-111.958337 33.432795,-111.958638 33.432447,-111.958278 33.432450,-111.958878 33.431466,-111.957996 33.432107,-111.957784 33.431938,-111.957820 33.431099,-111.957413 33.431875,-111.957262 33.432157,-111.956740 33.431423,-111.956281 33.431420,-111.956002 33.431698,-111.956130 33.432420,-111.956616 33.432674,-111.956599 33.432953))
```

## Usage

```
Usage: randpoly [options...]
  -h, --help                This page
  -n, --npoints <number>    Number of points for the polygon
  -x, --xpos <number>       Center X position, default -111.9575
  -y, --ypos <number>       Center Y position, default 33.4329
  -r, --radius <number>     Radius from center, default 0.002
  -s, --spread <number>     Segment width randomness (0-1), default 0.7
  -c, --concavity <number>  Radius randomness (0-1), default 0.7
  -w, --wkt                 Use WKT output, instead of GeoJSON
```

## Code

```C
double *make_polygon(int n, double x, double y, double r, double c, double s) {
    s = s < 0.0 ? 0.0 : s > 1.0 ? 1.0 : s;
    c = c < 0.0 ? 0.0 : c > 1.0 ? 1.0 : c;
    n = n < 3 ? 3 : n;
    srand(time(NULL));
    double *points = malloc(sizeof(double)*n*2);
    if (!points) return NULL;
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
```
