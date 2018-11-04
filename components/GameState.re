type direction =
  | UP
  | DOWN
  | LEFT
  | RIGHT;

type action =
  | ChangeDirection(direction)
  | Pause
  | Tick;

type state = {
  timerId: ref(option(Js.Global.intervalId)),
  snake: list((int, int)),
  goodies: list((int, int)),
  currentDirection: direction,
  collision: bool,
  paused: bool,
};

let rec moveTail = (tail, coordinate) =>
  switch (tail) {
  | [] => []
  | [next, ...rest] => [coordinate, ...moveTail(rest, next)]
  };

let detectIntersectingGoodie = (snake, goodies) => {
  let (headX, headY) = List.hd(snake);
  switch (
    List.find(
      ((goodieX, goodieY)) => goodieX === headX && goodieY === headY,
      goodies,
    )
  ) {
  | exception Not_found => None
  | goodie => Some(goodie)
  };
};

let generateGoodies = () => [
  /* let randomCoord = () => (Random.int(100), Random.int(100)); */
  (10, 10),
  (20, 20),
  (30, 30),
  (40, 40),
  (50, 50),
];

let removeGoodie = ((x1, y1), goodies) =>
  List.filter(((x, y)) => x !== x1 || y !== y1, goodies);

let moveSnake = (snake, currentDirection, increment) =>
  switch (snake, increment) {
  | ([(x, y), ...tail], true) => [
      switch (currentDirection) {
      | UP => (x, y - 1)
      | DOWN => (x, y + 1)
      | LEFT => (x - 1, y)
      | RIGHT => (x + 1, y)
      },
      (x, y),
      ...tail,
    ]
  | ([(x, y), ...tail], false) =>
    switch (currentDirection) {
    | UP => [(x, y - 1), ...moveTail(tail, (x, y))]
    | DOWN => [(x, y + 1), ...moveTail(tail, (x, y))]
    | LEFT => [(x - 1, y), ...moveTail(tail, (x, y))]
    | RIGHT => [(x + 1, y), ...moveTail(tail, (x, y))]
    }
  | ([], _) => []
  };

let detectCollision = snake =>
  switch (snake) {
  | [] => false
  | [(x, y), ..._tail] => x >= 99 || y >= 99 || x <= 0 || y <= 0
  };

let component = ReasonReact.reducerComponent("GameState");

let make = children => {
  ...component,
  initialState: () => {
    timerId: ref(None),
    snake: [(5, 5), (4, 5)],
    currentDirection: RIGHT,
    collision: false,
    goodies: generateGoodies(),
    paused: false,
  },
  didMount: self =>
    self.state.timerId :=
      Some(Js.Global.setInterval(() => self.send(Tick), 100)),
  reducer: (action, state) =>
    switch (action) {
    | Pause => ReasonReact.Update({...state, paused: ! state.paused})
    | Tick =>
      state.paused ?
        ReasonReact.NoUpdate :
        {
          let collision = detectCollision(state.snake);
          let intersecter =
            detectIntersectingGoodie(state.snake, state.goodies);
          ReasonReact.Update({
            ...state,
            snake:
              collision ?
                state.snake :
                moveSnake(
                  state.snake,
                  state.currentDirection,
                  switch (intersecter) {
                  | Some(_) => true
                  | None => false
                  },
                ),
            collision,
            goodies:
              switch (intersecter) {
              | Some(goodie) => removeGoodie(goodie, state.goodies)
              | None => state.goodies
              },
          });
        }
    | ChangeDirection(dir) =>
      switch (state.currentDirection, dir) {
      | (UP, DOWN)
      | (LEFT, RIGHT)
      | (RIGHT, LEFT)
      | (DOWN, UP) => ReasonReact.NoUpdate
      | (_current, newDir) =>
        ReasonReact.Update({...state, currentDirection: newDir})
      }
    },
  render: self =>
    children(
      ~changeDirection=dir => self.send(ChangeDirection(dir)),
      ~pauseGame=() => self.send(Pause),
      self.state,
    ),
};