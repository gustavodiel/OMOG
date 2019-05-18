
let points = [];

let selectedPoint = null;

const hermite = new Hermite();

function setup() {
	createCanvas(windowWidth, windowHeight);
	fill(255);
	noStroke();
}

function draw() {
	background(0);

	fill(255);

	if (points.length > 0) {
		let last = points[0].pos;
		for(var t=0; t<1; t+=0.001) {
			var pt = hermite.interpolate(t, points);

			// ellipse(pt.x, pt.y, 5, 5);
			stroke(255);
			strokeWeight(3);
			line(last.x, last.y, pt.x, pt.y);

			last = pt;

			// var tangent = hermite.interpolate(t, points, null, true);
			//
			// stroke(255, 50);
			// strokeWeight(2);
			// line(pt.x, pt.y, pt.x - tangent.x, pt.y - tangent.y);
		}
	}


	for (let pt of points) {
		pt.draw();
	}

}

function pointInPosition(x, y) {
	for (let point of points) {
		if (point.isInside(x, y)) {
			return point;
		} else {
			if (point.tangent.isInside(x, y)) {
				return point.tangent;
			}
		}
	}

	return null;
}

function mousePressed() {
	if (selectedPoint) {
		selectedPoint.selected = false;
	}

	selectedPoint = pointInPosition(mouseX, mouseY);

	if (selectedPoint) {
		selectedPoint.selected = true;
	} else {
		points.push(new Point(mouseX, mouseY));
	}
}

function mouseReleased() {
	if (selectedPoint) {
		selectedPoint.selected = false;
		selectedPoint = null;
	}
}

function mouseDragged() {
	if (selectedPoint) {
		selectedPoint.move(mouseX, mouseY);
	}
}


