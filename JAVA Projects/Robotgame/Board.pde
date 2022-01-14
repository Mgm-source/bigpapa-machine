class board {
  int rows, cols;
  int dim = 50;
  boolean movable = true;
  ArrayList<cell> game = new ArrayList<cell>();
  ArrayList<cell> gameEdit = new ArrayList<cell>();
  ArrayList<cell> blockedCells = new ArrayList<cell>();
  JSONArray values = new JSONArray();

  board(int rows, int cols) {
    this.rows = rows;
    this.cols = cols;
  }

  void createBoard() {
    int count = 0;
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j< rows; j++) {
        game.add(new cell(j,i, true, count));
        count++;
      }
    }
  }

  void importBoard(String location) {

    JSONArray importData = loadJSONArray(location);

    for (int i=0; i<importData.size(); i++) {

      JSONObject data = importData.getJSONObject(i);
      game.add(new cell(data.getInt("X"), data.getInt("Y"), data.getBoolean("Walkable"), data.getInt("ID")));
    }
  }

  void drawBoard() {
    for (cell gameD : game ) {
      if (!gameD.isWalkable()) {
                  fill(0, 200, 0);
        rect(gameD.getX() * dim, gameD.getY() * dim, dim, dim);
      }
    }
  }

  void editBoard() {
    if (click) {
      gameEdit.add(new cell( (int) (mouseX/dim), (int) (mouseY/dim), false, (floor((mouseX/dim) % dim ) + (20 * floor((mouseY/dim) % dim ) ) )));
      println((int) (mouseX/dim), (int) (mouseY/dim), floor( (mouseX/dim) % dim ) + (20 * floor( (mouseY/dim) % dim ) ));
    }
  }

  void showEdit() {
    for (cell gameE : gameEdit ) {
      fill(200);
      rect(gameE.getX() * dim, gameE.getY() * dim, dim, dim);
    }
  }


  void generateJsonMap() {

    for (int i = 0; i < game.size(); i++) {

      JSONObject cell = new JSONObject();
      cell.setInt("ID", i);
      cell.setInt("X", game.get(i).getX());
      cell.setInt("Y", game.get(i).getY());
      cell.setBoolean("Walkable", game.get(i).isWalkable());

      values.setJSONObject(i, cell);
    }
  }
  
  int findCell(float x,float y){
    
    return floor((x/dim) % dim ) + (20 * floor((y/dim) % dim ) );
  }

  void updateBoard() {

    for (cell currentC : game ) {
      for (cell newCell : gameEdit ) {
        if (newCell.getID() == currentC.getID()) {
          println(newCell, currentC);
          currentC.setMovable(false);
        }
      }
    }
  }

  void saveJsonMap() {
    saveJSONArray(values, "data/mapData.json");
    println("Map saved...");
  }


  ArrayList<cell> getBoard() {
    return game;
  }
}
