type state = {svgRef: ref(option(Dom.element))};

type action =
  | DoNothing;

let setSvgRef = (theRef, {ReasonReact.state}) =>
  state.svgRef := Js.Nullable.toOption(theRef);

let component = ReasonReact.reducerComponent("GameView");

let wrapperStyle =
  Css.[display(flexBox), flexDirection(column), height(vh(100.))];

let svgStyle = Css.[width(pct(100.)), flexGrow(1)];

let make = _children => {
  ...component,
  initialState: () => {svgRef: ref(None)},
  reducer: (_action: action, _state) => ReasonReact.NoUpdate,
  render: self =>
    <GameState>
      ...(
           (~changeDirection, ~pauseGame, state) =>
             <div className=(Css.style(wrapperStyle))>
               <svg
                 ref=(self.handle(setSvgRef))
                 className=(Css.style(svgStyle))>
                 <Snake dead=state.collision coordinates=state.snake />
                 <Goodies goodies=state.goodies />
               </svg>
               <div>
                 <button onClick=(_evt => changeDirection(UP))>
                   (ReasonReact.string("UP"))
                 </button>
                 <button onClick=(_evt => changeDirection(DOWN))>
                   (ReasonReact.string("DOWN"))
                 </button>
                 <button onClick=(_evt => changeDirection(LEFT))>
                   (ReasonReact.string("LEFT"))
                 </button>
                 <button onClick=(_evt => changeDirection(RIGHT))>
                   (ReasonReact.string("RIGHT"))
                 </button>
                 <button onClick=(_evt => pauseGame())>
                   (ReasonReact.string("PAUSE"))
                 </button>
               </div>
             </div>
         )
    </GameState>,
};