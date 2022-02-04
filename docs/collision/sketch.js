'use strict';

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let shape = [];

document.addEventListener("DOMContentLoaded", () => {

  shape.push(new Circle(500, 280, 1, 1, 1, 0));
  shape.push(new Circle(100, 80, 1, 0, 1, 1));

  window.requestAnimationFrame(draw);

})

function draw() {

  ctx.clearRect(0, 0, canvas.width, canvas.height);

  for (let i = 0; i < shape.length; i++) {

    for (let j = 0; j < shape.length; j++) {
      if (shape[i].id != shape[j].id) {

        shape[i].coll(shape[j]);

      }
    }

    shape[i].wallColl();
  }

  for( let k = 0; k < shape.length; k++){
    
    shape[k].update();
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
        this.vy = Math.abs(this.vy);
      }

      if (this.y > canvas.height - this.h) {
        this.vy = -this.vy;
      }

      if (this.x < 0) {
        this.vx = Math.abs(this.vx);
      }

      if (this.x > canvas.width - this.w) {
        this.vx = -this.vx;
      }

    }

    if (this.type == "circle") {

      if (this.y <= this.w) {
        this.vy = Math.abs(this.vy);
      }

      if (this.y >= canvas.height - this.w) {
        this.vy = -this.vy;
      }

      if (this.x <= this.w) {
        this.vx = Math.abs(this.vx);
      }

      if (this.x >= canvas.width - this.w) {
        this.vx = -this.vx;
      }

    }

  }

  coll(other) {

    if (this.type == 'rectangle') {

      if (other.type == 'rectangle') {

        const distanceX = other.x - this.x;
        const distanceY = other.y - this.y;

        if (distanceX > -other.w && distanceX < other.w && distanceY > -other.h && distanceY < other.h) {

          this.elastic(other);

        }

      }

    }

    if (this.type == 'circle') {

      if (other.type == 'circle') {

        if ( (this.x - other.x)*(this.x - other.x) + (this.y - other.y)*(this.y - other.y) <= (this.r + other.r)*(this.r + other.r) ) {

          const thisAngle = Math.atan2((this.y + other.y) / 2 - this.y, (this.x + other.x) / 2 - this.x);
          const otherAngle = Math.atan2((this.y + other.y) / 2 - other.y, (this.x + other.x) / 2 - other.x);

          const distance = Math.sqrt( (this.x - other.x)*(this.x - other.x)+(this.y - other.y)*(this.y - other.y) );

          const overlap = 0.5 * (distance - this.r - other.r);

          ctx.beginPath();
          ctx.strokeStyle = "green";
          ctx.moveTo((other.x + this.x) / 2, (other.y + this.y) / 2);
          ctx.lineTo(this.x, this.y);
          ctx.stroke();

          ctx.beginPath();
          ctx.strokeStyle = "green";
          ctx.moveTo((this.x + other.x) / 2, (this.y + other.y) / 2);
          ctx.lineTo(other.x, other.y);
          ctx.stroke();

          this.x -= overlap * (this.x - other.x) / distance;
          this.y -= overlap * (this.y - other.y) / distance;

          other.x += overlap * (this.x - other.x) / distance;
          other.y += overlap * (this.y - other.y) / distance;

          const normalX = (other.x - this.x) / distance;
          const normalY = (other.y - this.y) / distance;

          const tangentalX = -normalY;
          const tangentalY = normalX;

          const thisDotTan = this.vx * tangentalX + this.vy * tangentalY;
          const otherDotTan = other.vx * tangentalX + other.vy * tangentalY;

          const thisDotNor = this.vx * normalX + this.vy * normalY;
          const otherDotNor = other.vx * normalX + other.vy * normalY;

          const m1 = (thisDotNor * (this.m - other.m) + 2 * other.m * otherDotNor) / (this.m + other.m);
          const m2 = (otherDotNor * (other.m - this.m) + 2 * this.m * thisDotNor) / (this.m + other.m);

          this.vx = tangentalX * thisDotTan + normalX * m1;
          this.vy = tangentalY * thisDotTan + normalY * m1;

          other.vx = tangentalX * otherDotTan + normalX * m2;
          other.vy = tangentalY * otherDotTan + normalY * m2;

          console.log(this.vx, other.vx);
          console.log(this, other);

          this.move();
          other.move();

        }
      }

      if (other.type == 'rectangle') {

        const distanceX = other.x - this.x;
        const distanceY = other.y - this.y;

        if ((distanceX < (this.r + other.w) / 4 && distanceX > -(this.r + other.w - this.r / 4) && distanceY <= (this.r + other.h) / 4 && distanceY > -(this.r + other.w - this.r / 4)) || distanceX > - (this.r + other.w) && distanceX < (this.r) && distanceY > -(this.r + other.h) && distanceY <= (this.r)) {

          this.elastic(other)

        }
      }

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

    else if(this.r && other.r){

    }

    else {

      this.vx = ((this.m - other.m) / (this.m + other.m)) * this.vx + ((2 * other.m) / (this.m + other.m)) * other.vx;
      this.vy = ((this.m - other.m) / (this.m + other.m)) * this.vy + ((2 * other.m) / (this.m + other.m)) * other.vy;

      other.vx = ((other.m - this.m) / (other.m + this.m)) * other.vx + ((2 * this.m) / (other.m + this.m)) * oldvx;
      other.vy = ((other.m - this.m) / (other.m + this.m)) * other.vy + ((2 * this.m) / (other.m + this.m)) * oldvy;

    }

    this.move();
    other.move();

  }

  move() {
    if(Math.abs(this.vx * this.vx + this.vy * this.vy) < 0.1){
      this.vx = 0;
      this.vy = 0;
    }
    
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
