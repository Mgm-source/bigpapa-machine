class cell {
  int x, y, id;
  boolean movable;

  cell(int x, int y, boolean movable, int ID) {

    this.x = x;
    this.y = y;
    this.movable = movable;
    this.id = ID;
  }

  int getX() {
    return x;
  }
  int getY() {
    return y;
  }
  int getID() {
    return id;
  }
  boolean isWalkable() {
    return movable;
  }
  void setMovable(boolean value) {
    movable = value;
  }

  void setID(int value) {
    id = value;
  }

  public String toString() {
    return "ID:"+id+", coordinates:"+x+","+y+", is Walkable:"+movable;
  }
}
