
let points = [];

function setup() {
	createCanvas(windowWidth, windowHeight);
	fill(255);
}

function draw() {
	background(0);
	// var points = [
	// 	[ 0, 		height/2],
	// 	[ middleX,  middleY],
	// 	[ width, 	height/2]
	// ];
	//
	// var tangents = [
	// 	[1, -1000],
	// 	[0, 0],
	// 	[1, -1000]
	// ];
	//
	// fill(255, 0, 0);
	// for (let i = 0; i < points.length; i++) {
	// 	let point = points[i];
	// 	ellipse(normalizeX(point[0]), normalizeY(point[1]), 10, 10);
	// }
	//
	// fill(255);
	// for(var t=0; t<1; t+=0.01) {
	// 	var point = interpolate(t, points, tangents);
	// 	ellipse(normalizeX(point[0]), normalizeY(point[1]), 5, 5);
	// 	// var tangent = interpolate(t, points, tangents, null, true);
	//
	// 	// stroke(0, 255, 0);
	// 	// line(point[0], point[1], tangent[0], tangent[1]);
	// }
}

function keyPressed() {
	points.append(new Point());
}

function mouseDragged() {
	middleX = mouseX;
	middleY = mouseY;
}

function normalizeX(x) {
	return x; //map(x, -1, 1, 0, width);
}

function normalizeY(y) {
	return y; //map(y, -1, 1, 0, height);
}

