class Tangent {
    constructor(x, y) {
        this.pos = createVector(x, y);

        this.selected = false;

        this.radius = 15;
    }

    draw() {
        noStroke();
        fill(0, 255, 0);
        if (this.selected) {
            fill(0, 255, 255);
        }
        ellipse(this.pos.x, this.pos.y, this.radius, this.radius);
    }

    isInside(x, y) {
        return dist(x, y, this.pos.x, this.pos.y) < this.radius;
    }

    move(x, y) {
        this.pos.x = x;
        this.pos.y = y;
    }
}