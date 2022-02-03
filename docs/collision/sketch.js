'use strict';

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let shape = [];

document.addEventListener("DOMContentLoaded", () => {

  shape.push(new Rectangle(500, 41, 1, 0, 3, 0));
  shape.push(new Rectangle(100 ,80, 1, 0, 3, 1));

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

      if (this.y < this.w) {
        this.vy = Math.abs(this.vy);
      }

      if (this.y > canvas.height - this.w) {
        this.vy = -this.vy;
      }

      if (this.x < this.w) {
        this.vx = Math.abs(this.vx);
      }

      if (this.x > canvas.width - this.w) {
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

        if (Math.abs(((other.x - this.x) ** 2) + ((other.y - this.y) ** 2)) < ((this.r + other.r) ** 2)) {

          const thisAngle = Math.atan2((this.y + other.y)/2 - this.y , (this.x + other.x)/2 - this.x);
          const otherAngle = Math.atan2((other.y + this.y)/2 - other.y, (other.x + this.x)/2 - other.x);

          // ctx.beginPath();
          // ctx.strokeStyle = "green";
          // ctx.moveTo((other.x + this.x)/2 , (other.y + this.y)/2);
          // ctx.lineTo( this.x, this.y);
          // ctx.stroke();

          // ctx.beginPath();
          // ctx.strokeStyle = "green";
          // ctx.moveTo((this.x + other.x)/2 , (this.y + other.y)/2);
          // ctx.lineTo( other.x, other.y);
          // ctx.stroke();

          // ctx.beginPath();
          // ctx.strokeStyle = "blue";
          // ctx.arc(Math.cos(otherAngle) *  this.r + this.x, Math.sin(otherAngle) *  this.r + this.y, this.r, 0, 2 * Math.PI);
          // ctx.stroke();

          // ctx.beginPath();
          // ctx.strokeStyle = "orange";
          // ctx.arc(Math.cos(thisAngle) * other.r + other.x, Math.sin(thisAngle) *  other.r + other.y, other.r, 0, 2 * Math.PI);
          // ctx.stroke();

          console.log( "{" + thisAngle/Math.PI * 180 +","+ thisContanct/Math.PI * 180 + "}", "{"+ otherAngle/Math.PI * 180 +","+ otherContanct/Math.PI * 180 + "}");
          this.elastic(other);

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
    const angle = Math.atan2(this.vy,this.vx);

    ctx.beginPath();
    ctx.strokeStyle = "red";
    ctx.arc(this.x, this.y, this.r, 0, 2 * Math.PI);
    ctx.moveTo(this.x , this.y );
    ctx.lineTo(Math.cos(angle) *  this.r + this.x, Math.sin(angle) *  this.r + this.y);
    ctx.stroke();

  }

}

  // move(x,y){
  //   if(x != undefined && x > 0 || y != undefined && y > 0){
  //     this.x = x;
  //     this.y = y;
  //   }
  // }
