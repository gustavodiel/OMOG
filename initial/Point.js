class Point {
    constructor(x, y) {
        this.pos = createVector(x, y);
        this.tangent = new Tangent(x, y - 100);

        this.selected = false;

        this.radius = 25;
    }

    draw() {
        stroke(150);
        strokeWeight(3);
        line(this.pos.x, this.pos.y, this.tangent.pos.x, this.tangent.pos.y);

        noStroke();
        fill(255, 0, 0);
        if (this.selected) {
            fill(255, 255, 0);
        }
        ellipse(this.pos.x, this.pos.y, this.radius, this.radius);

        this.tangent.draw();
    }

    real_tangent() {
        let vec = createVector(this.tangent.pos.x - this.pos.x, this.tangent.pos.y - this.pos.y);
        vec.mult(5);
        return vec;
    }

    move(x, y) {
        let diff_x = x - this.pos.x;
        let diff_y = y - this.pos.y;

        this.pos.x = x;
        this.pos.y = y;

        this.tangent.pos.x += diff_x;
        this.tangent.pos.y += diff_y;
    }

    isInside(x, y) {
        return dist(x, y, this.pos.x, this.pos.y) < this.radius;
    }
}