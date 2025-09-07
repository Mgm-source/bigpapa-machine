'use strict';

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let shape = [];

document.addEventListener("DOMContentLoaded", () => {

  shape.push(new Circle(500, 80 ,0, 1, 1, 0));
 shape.push(new Circle(100, 89, 1, 1, 1, 1));
  shape.push(new Circle(500, 200 ,0, 1, 1, 2));
 shape.push(new Circle(300, 100, 1, 1, 1, 3));
  window.requestAnimationFrame(draw);

})

function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  for (let i = 0; i < shape.length; i++) {

    for (let j = i + 1; j < shape.length; j++) {
        shape[i].coll(shape[j]);
      }

    shape[i].wallColl();
    shape[i].update();
    }

  window.requestAnimationFrame(draw);
}

class Shape {
  id = null;
  w = 40;
  h = 40;
  speed = 1;

  type = null;

  constructor(x, y, vx, vy, m, id) {
    this.x = x;
    this.y = y;
    this.vx = vx;
    this.vy = vy;
    this.m = m;
    this.id = id;

  }

  display() { }

  wallColl() {

    if (this.type == "rectangle") {

      if (this.y < 0) {
        this.y = Math.abs(this.vy);
      }

      if (this.y > canvas.height - this.h) {
        this.y = canvas.height - this.h;
      }

      if (this.x < 0) {
        this.x = 0;
      }

      if (this.x > canvas.width - this.w) {
        this.x = canvas.width - this.w
      }

    }

    if (this.type == "circle") {

      if (this.y < this.r) {
        this.vy = Math.abs(this.vy);
      }

      if (this.y > canvas.height-this.r) {
        this.vy = -Math.abs(this.vy);
      }

      if (this.x < this.r) {
        this.vx = Math.abs(this.vx);
      }

      if (this.x > canvas.width-this.r) {
        this.vx = -Math.abs(this.vx);
      }

    }

  }

coll(other) {
  // Rectangle vs Rectangle (AABB)
  if (this.type === 'rectangle' && other.type === 'rectangle') {
    const overlapX = this.x < other.x + other.w && this.x + this.w > other.x;
    const overlapY = this.y < other.y + other.h && this.y + this.h > other.y;

    if (overlapX && overlapY) {
      this.elastic(other);
    }
    return;
  }

  // Circle vs Circle
  if (this.type === 'circle' && other.type === 'circle') {
    const dx = other.x - this.x;
    const dy = other.y - this.y;
    const distSq = dx * dx + dy * dy;
    const minDist = this.r + other.r;
    const minDistSq = minDist * minDist;

    if (distSq < minDistSq) {
      const distance = Math.sqrt(distSq);
      if (distance === 0) return; 

      const midX = (this.x + other.x) / 2;
      const midY = (this.y + other.y) / 2;

      ctx.beginPath();
      ctx.strokeStyle = "green";
      ctx.moveTo(midX, midY);
      ctx.lineTo(this.x, this.y);
      ctx.stroke();

      ctx.beginPath();
      ctx.strokeStyle = "green";
      ctx.moveTo(midX, midY);
      ctx.lineTo(other.x, other.y);
      ctx.stroke();

      // Overlap resolution
      const overlap = 0.5 * (minDist - distance);
      const nx = dx / distance;
      const ny = dy / distance;

      this.x -= overlap * nx;
      this.y -= overlap * ny;
      other.x += overlap * nx;
      other.y += overlap * ny;

      // Elastic collision
      const tangentX = -ny;
      const tangentY = nx;

      const thisDotTangent = this.vx * tangentX + this.vy * tangentY;
      const otherDotTangent = other.vx * tangentX + other.vy * tangentY;

      const thisDotNormal = this.vx * nx + this.vy * ny;
      const otherDotNormal = other.vx * nx + other.vy * ny;

      const m1 = (thisDotNormal * (this.m - other.m) + 2 * other.m * otherDotNormal) / (this.m + other.m);
      const m2 = (otherDotNormal * (other.m - this.m) + 2 * this.m * thisDotNormal) / (this.m + other.m);

      this.vx = tangentX * thisDotTangent + nx * m1;
      this.vy = tangentY * thisDotTangent + ny * m1;
      other.vx = tangentX * otherDotTangent + nx * m2;
      other.vy = tangentY * otherDotTangent + ny * m2;
    }
    return;
  }

  // Circle vs Rectangle
  if (this.type === 'circle' && other.type === 'rectangle') {
    const closestX = Math.max(other.x, Math.min(this.x, other.x + other.w));
    const closestY = Math.max(other.y, Math.min(this.y, other.y + other.h));

    const dx = this.x - closestX;
    const dy = this.y - closestY;

    if (dx * dx + dy * dy < this.r * this.r) {
      this.elastic(other);
      // Optional: Add position correction
    }
    return;
  }

  // Rectangle vs Circle — delegate
  if (this.type === 'rectangle' && other.type === 'circle') {
    other.coll(this);
    return;
  }
}

  elastic(other) {

    const oldvx = this.vx;
    const oldvy = this.vy;

    if (this.m == other.m) {

      this.vx = other.vx
      this.vy = other.vy

      other.vx = oldvx;
      other.vy = oldvy;

    }

    else {

      this.vx = ((this.m - other.m) / (this.m + other.m)) * this.vx + ((2 * other.m) / (this.m + other.m)) * other.vx;
      this.vy = ((this.m - other.m) / (this.m + other.m)) * this.vy + ((2 * other.m) / (this.m + other.m)) * other.vy;

      other.vx = ((other.m - this.m) / (other.m + this.m)) * other.vx + ((2 * this.m) / (other.m + this.m)) * oldvx;
      other.vy = ((other.m - this.m) / (other.m + this.m)) * other.vy + ((2 * this.m) / (other.m + this.m)) * oldvy;

    }

  }

  move() {

    this.x += this.vx * this.speed;
    this.y += this.vy * this.speed;

  }

  update() {
    this.move();
    this.display();
  }

}

class Rectangle extends Shape {

  type = 'rectangle';

  display() {

    ctx.fillStyle = 'green';
    ctx.fillRect(this.x, this.y, this.w, this.h);

  }

}

class Circle extends Shape {

  type = 'circle';
  r = this.w / 2;

  display() {
    const angle = Math.atan2(this.vy, this.vx);

    ctx.beginPath();
    ctx.strokeStyle = "red";
    ctx.arc(this.x, this.y, this.r, 0, 2 * Math.PI);
    ctx.moveTo(this.x, this.y);
    ctx.lineTo(Math.cos(angle) * this.r + this.x, Math.sin(angle) * this.r + this.y);
    ctx.stroke();

  }

}

  // move(x,y){
  //   if(x != undefined && x > 0 || y != undefined && y > 0){
  //     this.x = x;
  //     this.y = y;
  //   }
  // }
