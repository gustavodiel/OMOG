class Hermite {

    constructor() {

    }

    interpolate(t, points, knots, derivative, result) {

        var n = points.length;    // number or points / tangents / knots
        var d = 2; // vector dimensionality
        var v = createVector(0, 0); // destination vector

        var t = t * (n - 1); // rescale t to [0, n-1]
        var i0 = t|0;        // truncate
        var i1 = i0 + 1;

        if(i0 > n-1) throw new Error('out of bounds');
        if(i0 === n-1) i1 = i0;

        var scale = i1 - i0;

        t = (t - i0) / scale;

        if(derivative) {
            var t2 = t * t;
            var h00 = 6 * t2 - 6 * t;
            var h10 = 3 * t2 - 4 * t + 1;
            var h01 = - 6 * t2 + 6 * t;
            var h11 = 3 * t2 - 2 * t;
        } else {
            var t2 = t * t;
            var it = 1 - t;
            var it2 = it * it;
            var tt = 2 * t;
            var h00 = (1 + tt) * it2;
            var h10 = t * it2;
            var h01 = t2 * (3 - tt);
            var h11 = t2 * (t - 1);
        }


        v.x = h00 * points[i0].pos.x +
            h10 * points[i0].real_tangent().x * scale +
            h01 * points[i1].pos.x +
            h11 * points[i1].real_tangent().x * scale;

        v.y = h00 * points[i0].pos.y +
            h10 * points[i0].real_tangent().y * scale +
            h01 * points[i1].pos.y +
            h11 * points[i1].real_tangent().y * scale;

        return v;
    }

}