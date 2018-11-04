let component = ReasonReact.statelessComponent("SnakePart");

let aliveStyle = Css.[SVG.fill(rgb(0, 0, 255))];

let deadStyle = Css.[SVG.fill(rgb(255, 0, 0))];

let make = (~coordinate, ~dead, _children) => {
  ...component,
  render: _self => {
    let (x, y) = coordinate;
    <rect
      x=(string_of_int(x) ++ "%")
      y=(string_of_int(y) ++ "%")
      width="1%"
      height="1%"
      className=(Css.style(dead ? deadStyle : aliveStyle))
    />;
  },
};